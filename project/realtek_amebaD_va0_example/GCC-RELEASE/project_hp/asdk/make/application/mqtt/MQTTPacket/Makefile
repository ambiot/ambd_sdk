include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/mqtt/MQTTPacket
vpath %.c $(DIR)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC += $(DIR)/MQTTConnectClient.c
CSRC += $(DIR)/MQTTConnectServer.c
CSRC += $(DIR)/MQTTDeserializePublish.c
CSRC += $(DIR)/MQTTFormat.c
CSRC += $(DIR)/MQTTPacket.c
CSRC += $(DIR)/MQTTSerializePublish.c
CSRC += $(DIR)/MQTTSubscribeClient.c
CSRC += $(DIR)/MQTTSubscribeServer.c
CSRC += $(DIR)/MQTTUnsubscribeClient.c
CSRC += $(DIR)/MQTTUnsubscribeServer.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	$(REMOVE) *.c

-include $(DEPS)	
