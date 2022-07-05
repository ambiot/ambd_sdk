include $(MAKE_INCLUDE_GEN)
IFLAGS               += -I$(BASEDIR)/component/audio/base/log/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/osal/osal_c/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/osal/osal_cxx/interfaces
IFLAGS               += -I$(BASEDIR)/component/audio/base/libs/src/include

.PHONY: lib clean

#*****************************************************************************#
#                                  VARIABLES                                  #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/base/osal/osal_cxx

vpath %.cpp $(shell find $(DIR)/src $(DIR)/adapter/freertos -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__  -DARM_CORE_CM4

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = $(DIR)/src/refptr.cpp
CSRC += $(DIR)/adapter/freertos/mutex.cpp
CSRC += $(DIR)/adapter/freertos/condition.cpp
CSRC += $(DIR)/adapter/freertos/threads.cpp

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.cpp=.o))

#*****************************************************************************#
#                               Dependency	                                  #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS

lib: COPY_RAM_OBJS
	$(COPY) $(OBJS) ../../xip/

#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS:	$(OBJS)

%.o:%.c
	$(Q)$(CC) $(GLOBAL_CFLAGS) $(MODULE_IFLAGS) $<  -o $@

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d
