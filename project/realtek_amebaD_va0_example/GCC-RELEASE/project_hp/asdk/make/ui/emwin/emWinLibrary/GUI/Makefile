
include $(MAKE_INCLUDE_GEN)


.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/ui/emwin/emWinLibrary/GUI
	
vpath %.c $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC_LIB += $(wildcard $(DIR)/AntiAlias/*.c) \
	$(wildcard $(DIR)/ConvertColor/*.c) \
	$(wildcard $(DIR)/ConvertMono/*.c) \
	$(wildcard $(DIR)/Core/*.c) \
	$(wildcard $(DIR)/DisplayDriver/*.c) \
	$(wildcard $(DIR)/Font/*.c) \
	$(wildcard $(DIR)/MemDev/*.c) \
	$(wildcard $(DIR)/TouchDriver/*.c) \
	$(wildcard $(DIR)/Widget/*.c) \
	$(wildcard $(DIR)/WM/*.c)

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS_LIB = $(notdir $(CSRC_LIB:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
lib: CORE_TARGETS_LIB
	$(AR) rvs lib_emwin.a $(OBJS_LIB) 
	$(MOVE) -f lib_emwin.a $(BASEDIR)/component/common/ui/emwin/emWinLibrary/lib/rtl8721d

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS_LIB: $(OBJS_LIB)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d
	$(REMOVE) *.su

-include $(DEPS)
