include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/audio/third_party/aac
MODULE_IFLAGS += -I$(DIR)/libAACdec/include
MODULE_IFLAGS += -I$(DIR)/libPCMutils/include
MODULE_IFLAGS += -I$(DIR)/libFDK/include
MODULE_IFLAGS += -I$(DIR)/libSYS/include
MODULE_IFLAGS += -I$(DIR)/libMpegTPDec/include
MODULE_IFLAGS += -I$(DIR)/libSBRdec/include
MODULE_IFLAGS += -I$(DIR)/libArithCoding/include
MODULE_IFLAGS += -I$(DIR)/libDRCdec/include
MODULE_IFLAGS += -I$(DIR)/libSACdec/include

vpath %.cpp $(shell find $(DIR)/ -type d)
#*****************************************************************************#
#                               CFLAGS                                        #
#*****************************************************************************#
GLOBAL_CFLAGS += -D__RTOS__

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC  = \
    $(DIR)/libAACdec/src/aacdec_drc.cpp \
    $(DIR)/libAACdec/src/aacdec_hcr_bit.cpp \
    $(DIR)/libAACdec/src/aacdec_hcr.cpp \
    $(DIR)/libAACdec/src/aacdec_hcrs.cpp \
    $(DIR)/libAACdec/src/aacdecoder.cpp \
    $(DIR)/libAACdec/src/aacdecoder_lib.cpp \
    $(DIR)/libAACdec/src/aacdec_pns.cpp \
    $(DIR)/libAACdec/src/aacdec_tns.cpp \
    $(DIR)/libAACdec/src/aac_ram.cpp \
    $(DIR)/libAACdec/src/aac_rom.cpp \
    $(DIR)/libAACdec/src/block.cpp \
    $(DIR)/libAACdec/src/channel.cpp \
    $(DIR)/libAACdec/src/channelinfo.cpp \
    $(DIR)/libAACdec/src/conceal.cpp \
    $(DIR)/libAACdec/src/FDK_delay.cpp \
    $(DIR)/libAACdec/src/ldfiltbank.cpp \
    $(DIR)/libAACdec/src/pulsedata.cpp \
    $(DIR)/libAACdec/src/rvlcbit.cpp \
    $(DIR)/libAACdec/src/rvlcconceal.cpp \
    $(DIR)/libAACdec/src/rvlc.cpp \
    $(DIR)/libAACdec/src/stereo.cpp \
    $(DIR)/libAACdec/src/usacdec_ace_d4t64.cpp \
    $(DIR)/libAACdec/src/usacdec_acelp.cpp \
    $(DIR)/libAACdec/src/usacdec_ace_ltp.cpp \
    $(DIR)/libAACdec/src/usacdec_fac.cpp \
    $(DIR)/libAACdec/src/usacdec_lpc.cpp \
    $(DIR)/libAACdec/src/usacdec_lpd.cpp \
    $(DIR)/libAACdec/src/usacdec_rom.cpp

CSRC  += \
    $(DIR)/libPCMutils/src/limiter.cpp \
    $(DIR)/libPCMutils/src/pcm_utils.cpp \
    $(DIR)/libPCMutils/src/pcmdmx_lib.cpp

CSRC  += \
    $(DIR)/libFDK/src/FDK_lpc.cpp \
    $(DIR)/libFDK/src/fixpoint_math.cpp \
    $(DIR)/libFDK/src/FDK_matrixCalloc.cpp \
    $(DIR)/libFDK/src/qmf.cpp \
    $(DIR)/libFDK/src/FDK_tools_rom.cpp \
    $(DIR)/libFDK/src/FDK_qmf_domain.cpp \
    $(DIR)/libFDK/src/FDK_decorrelate.cpp \
    $(DIR)/libFDK/src/mdct.cpp \
    $(DIR)/libFDK/src/autocorr2nd.cpp \
    $(DIR)/libFDK/src/FDK_bitbuffer.cpp \
    $(DIR)/libFDK/src/fft_rad2.cpp \
    $(DIR)/libFDK/src/nlc_dec.cpp \
    $(DIR)/libFDK/src/FDK_crc.cpp \
    $(DIR)/libFDK/src/fft.cpp \
    $(DIR)/libFDK/src/FDK_trigFcts.cpp \
    $(DIR)/libFDK/src/scale.cpp \
    $(DIR)/libFDK/src/FDK_hybrid.cpp \
    $(DIR)/libFDK/src/huff_nodes.cpp \
    $(DIR)/libFDK/src/FDK_core.cpp \
    $(DIR)/libFDK/src/dct.cpp

CSRC  += \
    $(DIR)/libSYS/src/syslib_channelMapDescr.cpp \
    $(DIR)/libSYS/src/genericStds.cpp

CSRC  += \
    $(DIR)/libMpegTPDec/src/tpdec_adts.cpp \
    $(DIR)/libMpegTPDec/src/tpdec_lib.cpp \
    $(DIR)/libMpegTPDec/src/tpdec_adif.cpp \
    $(DIR)/libMpegTPDec/src/tpdec_drm.cpp \
    $(DIR)/libMpegTPDec/src/tpdec_latm.cpp \
    $(DIR)/libMpegTPDec/src/tpdec_asc.cpp

CSRC  += \
    $(DIR)/libArithCoding/src/ac_arith_coder.cpp

CSRC  += \
    $(DIR)/libDRCdec/src/drcDec_tools.cpp \
    $(DIR)/libDRCdec/src/drcGainDec_init.cpp \
    $(DIR)/libDRCdec/src/drcDec_reader.cpp \
    $(DIR)/libDRCdec/src/drcDec_rom.cpp \
    $(DIR)/libDRCdec/src/drcDec_selectionProcess.cpp \
    $(DIR)/libDRCdec/src/drcGainDec_process.cpp \
    $(DIR)/libDRCdec/src/FDK_drcDecLib.cpp \
    $(DIR)/libDRCdec/src/drcDec_gainDecoder.cpp \
    $(DIR)/libDRCdec/src/drcGainDec_preprocess.cpp


CSRC  += \
    $(DIR)/libSBRdec/src/pvc_dec.cpp \
    $(DIR)/libSBRdec/src/psbitdec.cpp \
    $(DIR)/libSBRdec/src/sbr_ram.cpp \
    $(DIR)/libSBRdec/src/env_extr.cpp \
    $(DIR)/libSBRdec/src/sbrdec_drc.cpp \
    $(DIR)/libSBRdec/src/huff_dec.cpp \
    $(DIR)/libSBRdec/src/sbrdecoder.cpp \
    $(DIR)/libSBRdec/src/env_calc.cpp \
    $(DIR)/libSBRdec/src/env_dec.cpp \
    $(DIR)/libSBRdec/src/lpp_tran.cpp \
    $(DIR)/libSBRdec/src/psdec_drm.cpp \
    $(DIR)/libSBRdec/src/sbr_dec.cpp \
    $(DIR)/libSBRdec/src/sbr_crc.cpp \
    $(DIR)/libSBRdec/src/HFgen_preFlat.cpp \
    $(DIR)/libSBRdec/src/psdecrom_drm.cpp \
    $(DIR)/libSBRdec/src/sbr_deb.cpp \
    $(DIR)/libSBRdec/src/hbe.cpp \
    $(DIR)/libSBRdec/src/psdec.cpp \
    $(DIR)/libSBRdec/src/sbrdec_freq_sca.cpp \
    $(DIR)/libSBRdec/src/sbr_rom.cpp \

CSRC  += \
    $(DIR)/libSACdec/src/sac_tsd.cpp \
    $(DIR)/libSACdec/src/sac_process.cpp \
    $(DIR)/libSACdec/src/sac_calcM1andM2.cpp \
    $(DIR)/libSACdec/src/sac_dec_conceal.cpp \
    $(DIR)/libSACdec/src/sac_stp.cpp \
    $(DIR)/libSACdec/src/sac_dec.cpp \
    $(DIR)/libSACdec/src/sac_qmf.cpp \
    $(DIR)/libSACdec/src/sac_rom.cpp \
    $(DIR)/libSACdec/src/sac_bitdec.cpp \
    $(DIR)/libSACdec/src/sac_reshapeBBEnv.cpp \
    $(DIR)/libSACdec/src/sac_smoothing.cpp \
    $(DIR)/libSACdec/src/sac_dec_lib.cpp


#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.cpp=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
COPY_RAM_OBJS: CORE_TARGETS
all: COPY_RAM_OBJS
	$(AR) rvs lib_fdkaac.a $(OBJS)
	$(FROMELF) -g -D lib_fdkaac.a
	$(MOVE) -f lib_fdkaac.a $(ROOTDIR)/lib/application
#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              GENERATE GIT VERSION FILE                                      #
#*****************************************************************************#

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
