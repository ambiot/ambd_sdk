include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/3rdparty/haac
MODULE_IFLAGS = -I$(DIR)

vpath %.c $(DIR) $(shell find $(DIR) -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/trigtabs_fltgen.c
CSRC += $(DIR)/trigtabs.c
CSRC += $(DIR)/tns.c
CSRC += $(DIR)/stproc.c
CSRC += $(DIR)/sbrtabs.c
CSRC += $(DIR)/sbrside.c
CSRC += $(DIR)/sbrqmf.c
CSRC += $(DIR)/sbrmath.c
CSRC += $(DIR)/sbrimdct.c
CSRC += $(DIR)/sbrhuff.c
CSRC += $(DIR)/sbrhfgen.c
CSRC += $(DIR)/sbrhfadj.c
CSRC += $(DIR)/sbrfreq.c
CSRC += $(DIR)/sbrfft.c
CSRC += $(DIR)/sbr.c
CSRC += $(DIR)/pns.c
CSRC += $(DIR)/noiseless.c
CSRC += $(DIR)/imdct.c
CSRC += $(DIR)/hufftabs.c
CSRC += $(DIR)/huffman.c
CSRC += $(DIR)/filefmt.c
CSRC += $(DIR)/fft.c
CSRC += $(DIR)/dequant.c
CSRC += $(DIR)/decelmnt.c
CSRC += $(DIR)/dct4.c
CSRC += $(DIR)/buffers.c
CSRC += $(DIR)/bitstream.c
CSRC += $(DIR)/aactabs.c
CSRC += $(DIR)/aacdec.c

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
COPY_RAM_OBJS: CORE_TARGETS
all: COPY_RAM_OBJS
	$(AR) rvs lib_haac.a $(OBJS)
	$(FROMELF) -g -D lib_haac.a
	$(MOVE) -f lib_haac.a $(ROOTDIR)/lib/application
#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)


#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
