
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = 

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
	@make -C xip all
	@make -C sram all
	#make -C rtsp all

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

	


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: 
	make -C xip clean
	make -C sram clean
	make -C httpc clean
	make -C httpd clean
	make -C websocket clean
	make -C tftp clean
	make -C rtsp clean
	make -C http2 clean
	make -C eap clean
	make -C libcoap clean

