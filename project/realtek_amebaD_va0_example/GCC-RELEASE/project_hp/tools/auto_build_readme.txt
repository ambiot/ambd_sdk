1.	Build
	a)	Cygwin中切换工作目录至文件夹project_hp所在路径
	b)	输入cd tools
	c)	输入./auto_build.sh
	d)  编译得到的bin文档和build log在tools/peripheral_xxxxxxxx_xxxxxx文件夹中
	e)  重新编译LCDC的example
		(1). 输入cd ../
		(2). 输入make menuconfig并配置GUI Config -> Enable GUI -> 勾选emwin(NEW)
		(3). 修改rtl8721dhp_intfcfg.c文件以使能psram
		(4). 修改autobuild.sh文件取消最后一行注释build_example lcdc.txt并注释掉上面两行build_default和build_example interface.txt
		(5). 重复步骤 b)和 c)
		(6). 为了不影响后续其他example需要取消(2)和(3)步骤里对sdk的修改和(4)步骤中对autobuild.sh的修改
	f)  手动编译rdp的example，编译方法请参见rdp的Readme
2.	auto_build.sh
	a)	build_default: build km0 & km4 default image
	b)	build_example interface.txt: build examples in interface.txt
	c)	build_example lcdc.txt: build examples in lcdc.txt


