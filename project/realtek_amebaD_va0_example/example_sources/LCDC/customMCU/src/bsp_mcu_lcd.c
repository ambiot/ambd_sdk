#include "bsp_mcu_lcd.h"
#include "stdlib.h"
#include "bsp_lcdc_font.h" 

u16 POINT_COLOR=0x0000;
u16 BACK_COLOR=0xFFFF;

_lcd_dev lcddev={.McuLcdBitMode=MCULCDBitMode};
	 					    

void LCD_WR_REG(u16 data)
{ 
	LCDC_MCUIOWriteCmd(LCDC, data);
}

void LCD_WR_DATAX(u16 data)
{
	LCDC_MCUIOWriteData(LCDC, data);
}

u16 LCD_RD_DATA(void)
{						   
	return LCDC_MCUIOReadData(LCDC);
}

void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	
}   

u16 LCD_ReadReg(u16 LCD_Reg)
{										   
 	LCD_WR_REG(LCD_Reg);
	return LCD_RD_DATA(); 
} 

void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
} 

void LCD_WriteRAM(u16 RGB_Code)
{					
	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF) {
		LCD_WR_DATA(RGB_Code);
	} else {
		LCD_WR_DATA(RGB_Code>>8);
		LCD_WR_DATA(RGB_Code);
	}
}

u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}

void opt_delay(u8 i)
{
	while(i--);
}

u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r,g,b;

	/*check the parameters*/
	if(x>=lcddev.width||y>=lcddev.height)return 0;	
	
	LCD_SetCursor(x,y);
	
	LCD_WR_REG(0X2E);

	/*dummy READ*/
	r = LCD_RD_DATA();		   
	opt_delay(2);	

	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF) {
		/*read actual red color data*/
		r = LCD_RD_DATA();	
		opt_delay(2);
		b=LCD_RD_DATA(); 	  
		g=r&0XFF;
		g<<=8;
		return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
	} else {
		r = LCD_RD_DATA();
		opt_delay(2);	
		g = LCD_RD_DATA();
		opt_delay(2);
		b = LCD_RD_DATA();
		return (((r&0xf8)<<8)|((g&0xfc)<<3)|((b&0xf8)>>3));
	}
	
}		 

void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0X29);
}

void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0X28);
} 

void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
	LCD_SetWindow(Xpos, Ypos, Xpos + 1, Ypos + 1);
}

void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
	if((lcddev.dir==1&&lcddev.id!=0X6804&&lcddev.id!=0X1963)||(lcddev.dir==0&&lcddev.id==0X1963))
	{			   
		switch(dir)
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	} 
	if(lcddev.id==0x9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)
	{
		switch(dir)
		{
			case L2R_U2D:
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U:
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D:
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U:
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R:
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L:
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R:
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L:
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
 		LCD_WriteReg(dirreg,regval);
		if(lcddev.id!=0X1963)
		{
			if(regval&0X20)
			{
				if(lcddev.width<lcddev.height)
				{
					temp=lcddev.width;
					lcddev.width=lcddev.height;
					lcddev.height=temp;
				}
			}else  
			{
				if(lcddev.width>lcddev.height)
				{
					temp=lcddev.width;
					lcddev.width=lcddev.height;
					lcddev.height=temp;
				}
			}  
		}
	
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);  

	}
}     

void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);	
	LCD_WriteRAM_Prepare();
	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF){
		LCD_WR_DATA(POINT_COLOR); 
	} else {
		LCD_WR_DATA(POINT_COLOR>>8);
		LCD_WR_DATA(POINT_COLOR);
	}
}	 

void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	   
	LCD_SetCursor(x, y);
	LCD_WR_REG(lcddev.wramcmd);

	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF){
		LCD_WR_DATA(color);	
	} else {
		LCD_WR_DATA(color>>8);
		LCD_WR_DATA(color);		
	}
}

void LCD_SSD_BackLightSet(u8 pwm)
{	
	LCD_WR_REG(0xBE);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(pwm*2.55);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
}

void LCD_Display_Dir(u8 dir)
{
	if(dir==0)	
	{
		lcddev.dir=0;

		lcddev.width=LCD_WIDTH;
		lcddev.height=LCD_HEIGHT;

		lcddev.wramcmd=0X2C;
 		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 
	}else 
	{	  				
		lcddev.dir=1;

		lcddev.width=LCD_HEIGHT;
		lcddev.height=LCD_WIDTH;

		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 
	}
	//LCD_Scan_Dir(DFT_SCAN_DIR);
}	 

void LCD_SetWindow(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
	LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(xStar&0XFF);
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(xEnd&0XFF);

	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(yStar&0XFF);
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(yEnd&0XFF);
}

void BSP_LCD_Init(void)
{ 
	LCDC_MCUInitTypeDef LCDC_MCUInitStruct;

	/*enable LCDC peripheral clock*/

	/*configure LCDC IF's GPIO attribute*/

	/*configure pinmux*/
	
	/*arrange default parameters*/
	LCDC_MCUStructInit(&LCDC_MCUInitStruct);

	/*select MCU IO bit mode*/
	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF) {
		LCDC_MCUInitStruct.LCDC_MCUIfMode = LCDC_MCU_IF_16_BIT;
	} else {
		LCDC_MCUInitStruct.LCDC_MCUIfMode = LCDC_MCU_IF_8_BIT;
	}
	LCDC_MCUInitStruct.LCDC_MCUImgHeight = LCD_HEIGHT; 
	LCDC_MCUInitStruct.LCDC_MCUImgWidth = LCD_WIDTH;
	LCDC_MCUInitStruct.LCDC_MCURdAcvWidth = 4;
	LCDC_MCUInitStruct.LCDC_MCURdInacvWidth = 4;
	LCDC_MCUInitStruct.LCDC_MCUWrPulWidth = 6;

	LCDC_MCUInit(LCDC, &LCDC_MCUInitStruct);

	/*enable LCDC*/
	LCDC_Cmd(LCDC, ENABLE);		

	LCD_INITIALIZE();

	LCD_Display_Dir(0);
	LCD_Clear(WHITE);
}

void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 

	LCD_SetWindow(0, 0, lcddev.width - 1, lcddev.height - 1);
	LCD_WriteRAM_Prepare();    	  
	//for(index=0;index<totalpoint;index++)LCD_WR_DATA(color);	
	for(index=0;index<totalpoint;index++)LCD_WriteRAM(color);
}

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	u16 i,j;
	u16 xlen=0;
	u16 temp;

	xlen=ex-sx+1;

	LCD_SetWindow(sx, sy, ex, ey);
	LCD_WriteRAM_Prepare(); 
	
	for(i=sy;i<=ey;i++)
	{
		for(j=0;j<xlen;j++)LCD_WriteRAM(color);
	}
}

void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			
	height=ey-sy+1;			

	LCD_SetWindow(sx, sy, ex, ey);
	LCD_WriteRAM_Prepare(); 

 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)LCD_WriteRAM(color[i*width+j]);
	}	  
}

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
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
		LCD_DrawPoint(uRow,uCol);
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

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);
 		LCD_DrawPoint(x0+b,y0-a);
		LCD_DrawPoint(x0+b,y0+a);
		LCD_DrawPoint(x0+a,y0+b);
		LCD_DrawPoint(x0-a,y0+b);
 		LCD_DrawPoint(x0-b,y0+a);
		LCD_DrawPoint(x0-a,y0-b);
  		LCD_DrawPoint(x0-b,y0-a);       
		a++; 
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
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
			if(!(temp&0x80))LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;
				break;
			}
		}  	 
	}  	    	   	 	  
}   

u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
	  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

void ILI9488_Init(void)
{
	DiagPrintf("ILI9488 Init\n");

	GPIO_InitTypeDef GPIO_InitStruct_Timer;
	GPIO_InitStruct_Timer.GPIO_Pin = _PA_16;
	GPIO_InitStruct_Timer.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct_Timer.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(&GPIO_InitStruct_Timer);

	/* Reset */
	GPIO_WriteBit(_PA_16, 1);
	DelayMs(1);

	GPIO_WriteBit(_PA_16, 0);
	DelayMs(10);

	GPIO_WriteBit(_PA_16, 1);
	DelayMs(120);

	//************* Start Initial Sequence(ILI9488) **********//
	LCD_WR_REG(0xE0); // PGAMCTRL(Positive Gamma Control)
	LCD_WR_DATAX(0x00); 
	LCD_WR_DATAX(0x07); 
	LCD_WR_DATAX(0x0f); 
	LCD_WR_DATAX(0x0D); 
	LCD_WR_DATAX(0x1B); 
	LCD_WR_DATAX(0x0A); 
	LCD_WR_DATAX(0x3c); 
	LCD_WR_DATAX(0x78); 
	LCD_WR_DATAX(0x4A); 
	LCD_WR_DATAX(0x07); 
	LCD_WR_DATAX(0x0E); 
	LCD_WR_DATAX(0x09); 
	LCD_WR_DATAX(0x1B); 
	LCD_WR_DATAX(0x1e); 
	LCD_WR_DATAX(0x0f);  

	LCD_WR_REG(0xE1); // NGAMCTRL(Negative Gamma Control)
	LCD_WR_DATAX(0x00); 
	LCD_WR_DATAX(0x22); 
	LCD_WR_DATAX(0x24); 
	LCD_WR_DATAX(0x06); 
	LCD_WR_DATAX(0x12); 
	LCD_WR_DATAX(0x07); 
	LCD_WR_DATAX(0x36); 
	LCD_WR_DATAX(0x47); 
	LCD_WR_DATAX(0x47); 
	LCD_WR_DATAX(0x06); 
	LCD_WR_DATAX(0x0a); 
	LCD_WR_DATAX(0x07); 
	LCD_WR_DATAX(0x30); 
	LCD_WR_DATAX(0x37); 
	LCD_WR_DATAX(0x0f); 

	LCD_WR_REG(0xC0); // Power Control 1
	LCD_WR_DATAX(0x10); 
	LCD_WR_DATAX(0x10); 

	LCD_WR_REG(0xC1); // Power Control 2
	LCD_WR_DATAX(0x41); 

	LCD_WR_REG(0xC5); // VCOM Control
	LCD_WR_DATAX(0x00); 
	LCD_WR_DATAX(0x22); 
	LCD_WR_DATAX(0x80); 

	LCD_WR_REG(0x36); // Memory Access Control
	LCD_WR_DATAX(0x48); 

	LCD_WR_REG(0x3A); // Interface Pixel Format, 16bpp
	LCD_WR_DATAX(0x55);
		
	LCD_WR_REG(0XB0);  //Interface Mode Control  
	LCD_WR_DATAX(0x00); 
	LCD_WR_REG(0xB1);	//Frame rate 70HZ  
	LCD_WR_DATAX(0xB0); 
	LCD_WR_DATAX(0x11); 
	LCD_WR_REG(0xB4);  //  Display Inversion Control
	LCD_WR_DATAX(0x02);   
	LCD_WR_REG(0xB6); //RGB/MCU Interface Control, select MCU I/F
	LCD_WR_DATAX(0x02); 
	LCD_WR_DATAX(0x02); 

	LCD_WR_REG(0xB7); // Entry Mode Set
	LCD_WR_DATAX(0xC6); 

	//LCD_WR_REG(0XBE);
	//LCD_WR_DATAX(0x00);
	//LCD_WR_DATAX(0x04);

	LCD_WR_REG(0xE9); //  Set Image Function
	LCD_WR_DATAX(0x00);

	LCD_WR_REG(0XF7); //  Adjust Control 3
	LCD_WR_DATAX(0xA9); 
	LCD_WR_DATAX(0x51); 
	LCD_WR_DATAX(0x2C); 
	LCD_WR_DATAX(0x82);

	LCD_WR_REG(0x11); // Sleep Out
	DelayMs(120); 
	LCD_WR_REG(0x29); // Display On
}

void ILI9341_Init(void)
{
	DiagPrintf("ILI9341 Init\n");

	if(lcddev.McuLcdBitMode == MCU_LCD_16BIT_IF) {

		#if 1
		delay_ms(50); // delay 50 ms 
		LCD_WriteReg(0x0000,0x0001);
		delay_ms(50); // delay 50 ms 
	  	lcddev.id = LCD_ReadReg(0x0000);   
		if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)
		{	

			LCD_WR_REG(0XD3);				   
			LCD_RD_DATA(); 				//dummy read 	
	 		LCD_RD_DATA();   	 
	  		lcddev.id=LCD_RD_DATA();   							   
	 		lcddev.id<<=8;
			lcddev.id|=LCD_RD_DATA();  		  
		}

	 	MCULCD_Printf(" LCD ID:%x\r\n",lcddev.id);

		LCD_WR_REG(0xCF);    /*power control*/
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0xC1); 
		LCD_WR_DATAX(0X30); 
		LCD_WR_REG(0xED);  /*power on sepuence control*/
		LCD_WR_DATAX(0x64); 
		LCD_WR_DATAX(0x03); 
		LCD_WR_DATAX(0X12); 
		LCD_WR_DATAX(0X81); 
		LCD_WR_REG(0xE8);  /*driver timing control*/
		LCD_WR_DATAX(0x85); 
		LCD_WR_DATAX(0x10); 
		LCD_WR_DATAX(0x7A); 
		LCD_WR_REG(0xCB);  /*power control A*/
		LCD_WR_DATAX(0x39); 
		LCD_WR_DATAX(0x2C); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x34); 
		LCD_WR_DATAX(0x02); 
		LCD_WR_REG(0xF7);  /*pump ratio control*/
		LCD_WR_DATAX(0x20); 
		LCD_WR_REG(0xEA);  /*driver timing control B*/
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_REG(0xC0); /*power control 1*/
		LCD_WR_DATAX(0x1B);
		LCD_WR_REG(0xC1); /*power control 2*/
		LCD_WR_DATAX(0x01);
		LCD_WR_REG(0xC5); /*VCOM control 1*/
		LCD_WR_DATAX(0x30); 
		LCD_WR_DATAX(0x30); 
		LCD_WR_REG(0xC7); /*VCOM control 2*/
		LCD_WR_DATAX(0XB7); 
		LCD_WR_REG(0x36); /*Memory Access Control*/
		//LCD_WR_DATAX(0x48); 
		LCD_WR_DATAX(0x08); 
		LCD_WR_REG(0x3A);   /* Pixel Format Set*/
		LCD_WR_DATAX(0x55); 
		LCD_WR_REG(0xB1);   /*Frame Rate Control */
		LCD_WR_DATAX(0x00);   
		LCD_WR_DATAX(0x1A); 
		LCD_WR_REG(0xB6);  /*Display Function Control */
		LCD_WR_DATAX(0x0A); 
		LCD_WR_DATAX(0xA2); 
		LCD_WR_REG(0xF2);  /*ENABLE 3G*/
		LCD_WR_DATAX(0x00); 
		LCD_WR_REG(0x26); /*Gamma Set */
		LCD_WR_DATAX(0x01); 
		LCD_WR_REG(0xE0); /*Positive Gamma Correction */
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x2A); 
		LCD_WR_DATAX(0x28); 
		LCD_WR_DATAX(0x08); 
		LCD_WR_DATAX(0x0E); 
		LCD_WR_DATAX(0x08); 
		LCD_WR_DATAX(0x54); 
		LCD_WR_DATAX(0XA9); 
		LCD_WR_DATAX(0x43); 
		LCD_WR_DATAX(0x0A); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 		 
		LCD_WR_REG(0XE1); /* Negative Gamma Correction*/
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x15); 
		LCD_WR_DATAX(0x17); 
		LCD_WR_DATAX(0x07); 
		LCD_WR_DATAX(0x11); 
		LCD_WR_DATAX(0x06); 
		LCD_WR_DATAX(0x2B); 
		LCD_WR_DATAX(0x56); 
		LCD_WR_DATAX(0x3C); 
		LCD_WR_DATAX(0x05); 
		LCD_WR_DATAX(0x10); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x3F); 
		LCD_WR_DATAX(0x3F); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_REG(0x2B); /*Page Address Set*/
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x01);
		LCD_WR_DATAX(0x3f);
		LCD_WR_REG(0x2A); /*Column Address Set*/
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0xef);	 
		LCD_WR_REG(0x11); /*Sleep Out*/
		delay_ms(120);
		LCD_WR_REG(0x29); /*Display ON*/
		#else
		LCD_WR_REG(0xcf); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xc1);
		LCD_WR_DATA(0x30);

		LCD_WR_REG(0xed); 
		LCD_WR_DATA(0x64);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x12);
		LCD_WR_DATA(0x81);

		LCD_WR_REG(0xcb); 
		LCD_WR_DATA(0x39);
		LCD_WR_DATA(0x2c);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x34);
		LCD_WR_DATA(0x02);

		LCD_WR_REG(0xea); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xe8); 
		LCD_WR_DATA(0x85);
		LCD_WR_DATA(0x10);
		LCD_WR_DATA(0x79);

		LCD_WR_REG(0xC0); //Power control
		LCD_WR_DATA(0x23); //VRH[5:0]

		LCD_WR_REG(0xC1); //Power control
		LCD_WR_DATA(0x11); //SAP[2:0];BT[3:0]

		LCD_WR_REG(0xC2);
		LCD_WR_DATA(0x11);

		LCD_WR_REG(0xC5); //VCM control
		LCD_WR_DATA(0x3d);
		LCD_WR_DATA(0x30);

		LCD_WR_REG(0xc7); 
		LCD_WR_DATA(0xaa);

		LCD_WR_REG(0x3A); 
		LCD_WR_DATA(0x55);

		LCD_WR_REG(0x36); // Memory Access Control
		LCD_WR_DATA(0x08);

		LCD_WR_REG(0xB1); // Frame Rate Control
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x11);

		LCD_WR_REG(0xB6); // Display Function Control
		LCD_WR_DATA(0x0a);
		LCD_WR_DATA(0xa2);

		LCD_WR_REG(0xF2); // 3Gamma Function Disable
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xF7);
		LCD_WR_DATA(0x20);

		LCD_WR_REG(0xF1);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x30);

		LCD_WR_REG(0x26); //Gamma curve selected
		LCD_WR_DATA(0x01);

		LCD_WR_REG(0xE0); //Set Gamma
		LCD_WR_DATA(0x0f);
		LCD_WR_DATA(0x3f);
		LCD_WR_DATA(0x2f);
		LCD_WR_DATA(0x0c);
		LCD_WR_DATA(0x10);
		LCD_WR_DATA(0x0a);
		LCD_WR_DATA(0x53);
		LCD_WR_DATA(0xd5);
		LCD_WR_DATA(0x40);
		LCD_WR_DATA(0x0a);
		LCD_WR_DATA(0x13);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x08);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xE1); //Set Gamma
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x10);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x0f);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x2c);
		LCD_WR_DATA(0xa2);
		LCD_WR_DATA(0x3f);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x0e);
		LCD_WR_DATA(0x0c);
		LCD_WR_DATA(0x37);
		LCD_WR_DATA(0x3c);
		LCD_WR_DATA(0x0F);
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(200);//˴Ҫʱ80ms߸
		LCD_WR_REG(0x29); //display on
		#endif		
	} else {
		lcddev.id = 0x9341;

		LCD_WR_REG(0xcf); 
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0xc1);
		LCD_WR_DATAX(0x30);

		LCD_WR_REG(0xed); 
		LCD_WR_DATAX(0x64);
		LCD_WR_DATAX(0x03);
		LCD_WR_DATAX(0x12);
		LCD_WR_DATAX(0x81);

		LCD_WR_REG(0xcb); 
		LCD_WR_DATAX(0x39);
		LCD_WR_DATAX(0x2c);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x34);
		LCD_WR_DATAX(0x02);

		LCD_WR_REG(0xea); 
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);

		LCD_WR_REG(0xe8); 
		LCD_WR_DATAX(0x85);
		LCD_WR_DATAX(0x10);
		LCD_WR_DATAX(0x79);

		LCD_WR_REG(0xC0); //Power control
		LCD_WR_DATAX(0x23); //VRH[5:0]

		LCD_WR_REG(0xC1); //Power control
		LCD_WR_DATAX(0x11); //SAP[2:0];BT[3:0]

		LCD_WR_REG(0xC2);
		LCD_WR_DATAX(0x11);

		LCD_WR_REG(0xC5); //VCM control
		LCD_WR_DATAX(0x3d);
		LCD_WR_DATAX(0x30);

		LCD_WR_REG(0xc7); 
		LCD_WR_DATAX(0xaa);

		LCD_WR_REG(0x3A); 
		LCD_WR_DATAX(0x55);

		LCD_WR_REG(0x36); // Memory Access Control
		LCD_WR_DATAX(0x08);

		LCD_WR_REG(0xB1); // Frame Rate Control
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x11);

		LCD_WR_REG(0xB6); // Display Function Control
		LCD_WR_DATAX(0x0a);
		LCD_WR_DATAX(0xa2);

		LCD_WR_REG(0xF2); // 3Gamma Function Disable
		LCD_WR_DATAX(0x00);

		LCD_WR_REG(0xF7);
		LCD_WR_DATAX(0x20);

		LCD_WR_REG(0xF1);
		LCD_WR_DATAX(0x01);
		LCD_WR_DATAX(0x30);

		LCD_WR_REG(0x26); //Gamma curve selected
		LCD_WR_DATAX(0x01);

		LCD_WR_REG(0xE0); //Set Gamma
		LCD_WR_DATAX(0x0f);
		LCD_WR_DATAX(0x3f);
		LCD_WR_DATAX(0x2f);
		LCD_WR_DATAX(0x0c);
		LCD_WR_DATAX(0x10);
		LCD_WR_DATAX(0x0a);
		LCD_WR_DATAX(0x53);
		LCD_WR_DATAX(0xd5);
		LCD_WR_DATAX(0x40);
		LCD_WR_DATAX(0x0a);
		LCD_WR_DATAX(0x13);
		LCD_WR_DATAX(0x03);
		LCD_WR_DATAX(0x08);
		LCD_WR_DATAX(0x03);
		LCD_WR_DATAX(0x00);

		LCD_WR_REG(0xE1); //Set Gamma
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x10);
		LCD_WR_DATAX(0x03);
		LCD_WR_DATAX(0x0f);
		LCD_WR_DATAX(0x05);
		LCD_WR_DATAX(0x2c);
		LCD_WR_DATAX(0xa2);
		LCD_WR_DATAX(0x3f);
		LCD_WR_DATAX(0x05);
		LCD_WR_DATAX(0x0e);
		LCD_WR_DATAX(0x0c);
		LCD_WR_DATAX(0x37);
		LCD_WR_DATAX(0x3c);
		LCD_WR_DATAX(0x0F);
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(80);//˴Ҫʱ80ms߸
		LCD_WR_REG(0x29); //display on		
	}
}


