
include $(MAKE_INCLUDE_GEN)
IFLAGS += -I$(BASEDIR)/component/common/network/libcoap/include

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES                                     #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/network/libcoap

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

CSRC +=	$(DIR)/async.c \
		$(DIR)/block.c \
		$(DIR)/coap_debug.c \
		$(DIR)/coap_list.c \
		$(DIR)/coap_net.c \
		$(DIR)/encode.c \
		$(DIR)/hashkey.c \
		$(DIR)/option.c \
		$(DIR)/pdu.c \
		$(DIR)/resource.c \
		$(DIR)/str.c \
		$(DIR)/subscribe.c \
		$(DIR)/uri.c \


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(CSRC:.c=.o)

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS
	$(AR) rvs lib_coap.a $(OBJS)
	$(MOVE) -f lib_coap.a $(ROOTDIR)/lib/application

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

-include $(DEPS)
