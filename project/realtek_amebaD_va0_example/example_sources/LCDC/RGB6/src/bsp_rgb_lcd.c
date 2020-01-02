#include "bsp_rgb_lcd.h"
#include "stdlib.h"
#include "bsp_lcdc_font.h" 
#include "section_config.h"

_Rgb_Dev_Info RgbLcdDev;

u16 RgbLcdPointColor = RED;
u16 RgbLcdBackColor = WHITE;

PSRAM_BSS_SECTION
__attribute__ ((aligned (64)))
u16 RgbFrameBuffer[RGB_LCD_HEIGHT][RGB_LCD_WIDTH];

void RgbLcdDisplaySwitch(u32 State)
{
	if(State == RGB_LCD_CLOSE) {
		LCDC_Cmd(LCDC, DISABLE);
	} else {
		LCDC_Cmd(LCDC, ENABLE);
	}
}

void RgbLcdInit(void)
{
	LCDC_RGBInitTypeDef LCDC_RGBInitStruct;

	RgbLcdDev.pWidth = RGB_LCD_WIDTH;
	RgbLcdDev.pHeight = RGB_LCD_HEIGHT;
	RgbLcdDev.Hsw = 123;
	RgbLcdDev.Hfp = 6;
	RgbLcdDev.Hbp = 6;
	RgbLcdDev.Vsw = 10;
	RgbLcdDev.Vfp = 2;
	RgbLcdDev.Vbp = 2;
	RgbLcdDev.PixSize = 2;

	RgbLcdDev.Height = RgbLcdDev.pHeight;
	RgbLcdDev.Width = RgbLcdDev.pWidth;

	RgbLcdDev.LcdFrameBuf = (u16 *)&RgbFrameBuffer[0][0];

	/*load the RGB HV I/F default parameters*/
	LCDC_RGBStructInit(&LCDC_RGBInitStruct);

	/*configure image size, RGB timing parameters*/
	LCDC_RGBInitStruct.LCDC_RGBImgWidth = RgbLcdDev.pWidth;
	LCDC_RGBInitStruct.LCDC_RGBImgHeight = RgbLcdDev.pHeight;

	LCDC_RGBInitStruct.LCDC_RGBHSW = RgbLcdDev.Hsw;
	LCDC_RGBInitStruct.LCDC_RGBHFP = RgbLcdDev.Hfp;
	LCDC_RGBInitStruct.LCDC_RGBHBP = RgbLcdDev.Hbp;
	LCDC_RGBInitStruct.LCDC_RGBVSW = RgbLcdDev.Vsw;
	LCDC_RGBInitStruct.LCDC_RGBVFP = RgbLcdDev.Vfp;
	LCDC_RGBInitStruct.LCDC_RGBVBP = RgbLcdDev.Vbp;
	LCDC_RGBInitStruct.LCDC_RGBSyncMode = LCDC_RGB_DE_MODE;
	LCDC_RGBInitStruct.LCDC_RGBDclkActvEdge=LCDC_RGB_DCLK_FALLING_EDGE_FETCH;

	LCDC_RGBInitStruct.LCDC_RGBIfMode=LCDC_RGB_IF_6_BIT;

	LCDC_RGBInitStruct.LCDC_RGBRefreshFreq = 50;
	LCDC_RGBInit(LCDC, &LCDC_RGBInitStruct);

	/*configure DMA burst size*/
	LCDC_DMAModeConfig(LCDC,2);

	/*configure base address*/
	LCDC_DMAImageBaseAddrConfig(LCDC, (u32)RgbLcdDev.LcdFrameBuf);

	//RgbLcdDisplayDir(VERTICAL_SCREEN);
	RgbLcdDisplaySwitch(RGB_LCD_OPEN);
}

void RgbLcdClear(void)
{
	u32 i;
	u16 * ImgBuf = RgbLcdDev.LcdFrameBuf;

	for(i=0; i<RgbLcdDev.Height*RgbLcdDev.Width; i++) {
		*(ImgBuf+i) = RgbLcdBackColor;
	}
}

void RgbLcdDrawPoint(u16 x, u16 y)
{
	u16 * ImgBuf = RgbLcdDev.LcdFrameBuf;

	if((x >= RgbLcdDev.Width) || (y >= RgbLcdDev.Height)) {
		return;
	}
	
	if(RgbLcdDev.Dir == HORIZONTAL_SCREEN) {
		*(ImgBuf + (RgbLcdDev.pWidth*y+x)) = RgbLcdPointColor;
	} else {
		*(ImgBuf + RgbLcdDev.pWidth*(RgbLcdDev.pHeight-x-1)+y) = RgbLcdPointColor;
	}
}

void RgbLcdDrawPointColor(u16 x, u16 y, u16 color)
{
	u16 * ImgBuf = RgbLcdDev.LcdFrameBuf;


	if((x >= RgbLcdDev.Width) || (y >= RgbLcdDev.Height)) {
		return;
	}
	
	if(RgbLcdDev.Dir == HORIZONTAL_SCREEN) {
		*(ImgBuf + (RgbLcdDev.pWidth*y+x)) = color;
	} else {
		*(ImgBuf + RgbLcdDev.pWidth*(RgbLcdDev.pHeight-x-1)+y) = color;
	}
}

u16 RgbLcdReadPoint(u16 x, u16 y)
{
	u16 color;
	u16 * ImgBuf = RgbLcdDev.LcdFrameBuf;

	if((x >= RgbLcdDev.Width) || (y >= RgbLcdDev.Height)) {
		return 0;
	}
	
	if(RgbLcdDev.Dir == HORIZONTAL_SCREEN) {
		color = *(ImgBuf + (RgbLcdDev.pWidth*y+x));
	} else {
		color = *(ImgBuf + RgbLcdDev.pWidth*(RgbLcdDev.pHeight-x-1)+y);
	}

	return color;
}

void RgbLcdDisplayDir(u8 dir)
{
	RgbLcdDev.Dir = dir;
	if(dir == HORIZONTAL_SCREEN) {
		RgbLcdDev.Height = RgbLcdDev.pHeight;
		RgbLcdDev.Width = RgbLcdDev.pWidth;
	} else {
		RgbLcdDev.Height = RgbLcdDev.pWidth;
		RgbLcdDev.Width = RgbLcdDev.pHeight;		
	}
}

void RgbLcdDrawCircle(u16 x0, u16 y0, u16 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);            
	while(a<=b)
	{
		RgbLcdDrawPoint(x0+a,y0-b);   
 		RgbLcdDrawPoint(x0+b,y0-a);     
		RgbLcdDrawPoint(x0+b,y0+a);             //4               
		RgbLcdDrawPoint(x0+a,y0+b);        
		RgbLcdDrawPoint(x0-a,y0+b);  
 		RgbLcdDrawPoint(x0-b,y0+a);             
		RgbLcdDrawPoint(x0-a,y0-b);   
  		RgbLcdDrawPoint(x0-b,y0-a);                
		a++;
		     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}	
}

void RgbLcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ ) 
	{  
		RgbLcdDrawPoint(uRow,uCol); 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  	
}

void RgbLcdDrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	RgbLcdDrawLine(x1,y1,x2,y1);
	RgbLcdDrawLine(x1,y1,x1,y2);
	RgbLcdDrawLine(x1,y2,x2,y2);
	RgbLcdDrawLine(x2,y1,x2,y2);	
}

void RgbLcdSetColor(u16 color)
{
	RgbLcdPointColor = color;
}

void RgbLcdSetBkColor(u16 color)
{
	RgbLcdBackColor = color;
}

void RgbLcdFill(u16 sx,u16 sy,u16 ex,u16 ey)
{
	u16 i;
	for(i=sy;i<=ey;i++)
	{
		RgbLcdDrawLine(sx, i, ex, i);
	}	
}

void RgbLcdColorFill(u16 sx,u16 sy,u16 ex,u16 ey, u16 color)
{
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 
	height=ey-sy+1;
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++) {
			//DBG_8195A("%s: %d, %d\n", __func__, i, j);
			RgbLcdDrawPointColor(sx+j, sy+i, color);
		}
	}	  	
}

void RgbLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
   	u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		
 	num=num-' ';
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 
		else if(size==16)temp=asc2_1608[num][t];
		else if(size==24)temp=asc2_2412[num][t];	
		else return;							
		for(t1=0;t1<8;t1++)
		{			    
			if(!(temp&0x80)){RgbLcdDrawPointColor(x, y, RgbLcdPointColor);}
			else {if(mode==0)RgbLcdDrawPointColor(x, y, RgbLcdBackColor);}
			temp<<=1;
			y++;
			if(y>=RgbLcdDev.Height)return;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=RgbLcdDev.Width)return;
				break;
			}
		}  	 
	}  	  	
}

u32 RgbLcdPow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

void RgbLcdShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/RgbLcdPow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				RgbLcdShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	RgbLcdShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}	
}

void RgbLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/RgbLcdPow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)RgbLcdShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else RgbLcdShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	RgbLcdShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}	
}

void RgbLcdShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{
	u8 x0=x;
	width+=x;
	height+=y;
	while((*p<='~')&&(*p>=' '))
	{       
	if(x>=width){x=x0;y+=size;}
	if(y>=height)break;
	RgbLcdShowChar(x,y,*p,size,1);
	x+=size/2;
	p++;
	}  	
}

void RgbLcdShowBitmap(u16 x, u16 y, u16 width, u16 height, u16* bitmap)
{	
	u16 *src = bitmap, *dst;
	u32 word_per_line_src = width, word_per_line_dst;
	u32 dx, dy;

	if((x >= RgbLcdDev.Width) || (y >= RgbLcdDev.Height)) {
		return;
	}

	if(RgbLcdDev.Dir == HORIZONTAL_SCREEN) {
		dst = RgbLcdDev.LcdFrameBuf + (RgbLcdDev.pWidth*y+x);
		word_per_line_dst = RgbLcdDev.pWidth;

		for(dy = 0; dy < height; dy++) {
			_memcpy(dst, src, word_per_line_src * 2);
			src += word_per_line_src;
			dst += word_per_line_dst;
		}
	} else {
		for(dy = 0; dy < height; dy++) {
			for(dx = 0; dx < width; dx++) {
				dst = RgbLcdDev.LcdFrameBuf + RgbLcdDev.pWidth*(RgbLcdDev.pHeight-(x + dx)-1) + (y + dy);
				*dst = *(src + dy * word_per_line_src + dx);
			}
		}
	}
}

