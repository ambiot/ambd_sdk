
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/audio/opus-1.3.1
MODULE_IFLAGS = -I$(DIR)

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/silk/fixed/LTP_analysis_filter_FIX.c 
CSRC += $(DIR)/silk/fixed/LTP_scale_ctrl_FIX.c 
CSRC += $(DIR)/silk/fixed/corrMatrix_FIX.c 
CSRC += $(DIR)/silk/fixed/encode_frame_FIX.c
CSRC += $(DIR)/silk/fixed/find_LPC_FIX.c
CSRC += $(DIR)/silk/fixed/find_LTP_FIX.c
CSRC += $(DIR)/silk/fixed/find_pitch_lags_FIX.c
CSRC += $(DIR)/silk/fixed/find_pred_coefs_FIX.c
CSRC += $(DIR)/silk/fixed/noise_shape_analysis_FIX.c
CSRC += $(DIR)/silk/fixed/process_gains_FIX.c
CSRC += $(DIR)/silk/fixed/regularize_correlations_FIX.c
CSRC += $(DIR)/silk/fixed/residual_energy16_FIX.c
CSRC += $(DIR)/silk/fixed/residual_energy_FIX.c
CSRC += $(DIR)/silk/fixed/warped_autocorrelation_FIX.c
CSRC += $(DIR)/silk/fixed/apply_sine_window_FIX.c
CSRC += $(DIR)/silk/fixed/autocorr_FIX.c
CSRC += $(DIR)/silk/fixed/burg_modified_FIX.c 
CSRC += $(DIR)/silk/fixed/k2a_FIX.c
CSRC += $(DIR)/silk/fixed/k2a_Q16_FIX.c
CSRC += $(DIR)/silk/fixed/pitch_analysis_core_FIX.c
CSRC += $(DIR)/silk/fixed/vector_ops_FIX.c
CSRC += $(DIR)/silk/fixed/schur64_FIX.c
CSRC += $(DIR)/silk/fixed/schur_FIX.c

CSRC += $(DIR)/silk/CNG.c
CSRC += $(DIR)/silk/code_signs.c
CSRC += $(DIR)/silk/init_decoder.c
CSRC += $(DIR)/silk/decode_core.c
CSRC += $(DIR)/silk/decode_frame.c
CSRC += $(DIR)/silk/decode_parameters.c
CSRC += $(DIR)/silk/decode_indices.c
CSRC += $(DIR)/silk/decode_pulses.c
CSRC += $(DIR)/silk/decoder_set_fs.c
CSRC += $(DIR)/silk/dec_API.c
CSRC += $(DIR)/silk/enc_API.c
CSRC += $(DIR)/silk/encode_indices.c
CSRC += $(DIR)/silk/encode_pulses.c
CSRC += $(DIR)/silk/gain_quant.c
CSRC += $(DIR)/silk/interpolate.c
CSRC += $(DIR)/silk/LP_variable_cutoff.c
CSRC += $(DIR)/silk/NLSF_decode.c
CSRC += $(DIR)/silk/NSQ.c
CSRC += $(DIR)/silk/NSQ_del_dec.c
CSRC += $(DIR)/silk/PLC.c
CSRC += $(DIR)/silk/shell_coder.c
CSRC += $(DIR)/silk/tables_gain.c
CSRC += $(DIR)/silk/tables_LTP.c
CSRC += $(DIR)/silk/tables_NLSF_CB_NB_MB.c
CSRC += $(DIR)/silk/tables_NLSF_CB_WB.c
CSRC += $(DIR)/silk/tables_other.c
CSRC += $(DIR)/silk/tables_pitch_lag.c
CSRC += $(DIR)/silk/tables_pulses_per_block.c
CSRC += $(DIR)/silk/VAD.c
CSRC += $(DIR)/silk/control_audio_bandwidth.c
CSRC += $(DIR)/silk/quant_LTP_gains.c
CSRC += $(DIR)/silk/VQ_WMat_EC.c
CSRC += $(DIR)/silk/HP_variable_cutoff.c
CSRC += $(DIR)/silk/NLSF_encode.c
CSRC += $(DIR)/silk/NLSF_VQ.c
CSRC += $(DIR)/silk/NLSF_unpack.c
CSRC += $(DIR)/silk/NLSF_del_dec_quant.c
CSRC += $(DIR)/silk/process_NLSFs.c
CSRC += $(DIR)/silk/stereo_LR_to_MS.c
CSRC += $(DIR)/silk/stereo_MS_to_LR.c
CSRC += $(DIR)/silk/check_control_input.c
CSRC += $(DIR)/silk/control_SNR.c
CSRC += $(DIR)/silk/init_encoder.c
CSRC += $(DIR)/silk/control_codec.c
CSRC += $(DIR)/silk/A2NLSF.c
CSRC += $(DIR)/silk/ana_filt_bank_1.c
CSRC += $(DIR)/silk/biquad_alt.c
CSRC += $(DIR)/silk/bwexpander_32.c
CSRC += $(DIR)/silk/bwexpander.c
#CSRC += $(DIR)/silk/debug.c
CSRC += $(DIR)/silk/decode_pitch.c
CSRC += $(DIR)/silk/inner_prod_aligned.c
CSRC += $(DIR)/silk/lin2log.c
CSRC += $(DIR)/silk/log2lin.c
CSRC += $(DIR)/silk/LPC_analysis_filter.c
CSRC += $(DIR)/silk/LPC_inv_pred_gain.c
CSRC += $(DIR)/silk/table_LSF_cos.c
CSRC += $(DIR)/silk/NLSF2A.c
CSRC += $(DIR)/silk/NLSF_stabilize.c
CSRC += $(DIR)/silk/NLSF_VQ_weights_laroia.c
CSRC += $(DIR)/silk/pitch_est_tables.c
CSRC += $(DIR)/silk/resampler.c
CSRC += $(DIR)/silk/resampler_down2_3.c
CSRC += $(DIR)/silk/resampler_down2.c
CSRC += $(DIR)/silk/resampler_private_AR2.c
CSRC += $(DIR)/silk/resampler_private_down_FIR.c
CSRC += $(DIR)/silk/resampler_private_IIR_FIR.c
CSRC += $(DIR)/silk/resampler_private_up2_HQ.c
CSRC += $(DIR)/silk/resampler_rom.c
CSRC += $(DIR)/silk/sigm_Q15.c
CSRC += $(DIR)/silk/sort.c
CSRC += $(DIR)/silk/sum_sqr_shift.c
CSRC += $(DIR)/silk/stereo_decode_pred.c
CSRC += $(DIR)/silk/stereo_encode_pred.c
CSRC += $(DIR)/silk/stereo_find_predictor.c
CSRC += $(DIR)/silk/stereo_quant_pred.c
CSRC += $(DIR)/silk/LPC_fit.c




CSRC += $(DIR)/celt/bands.c
CSRC +=$(DIR)/celt/celt.c
CSRC +=$(DIR)/celt/celt_encoder.c
CSRC +=$(DIR)/celt/celt_decoder.c
CSRC +=$(DIR)/celt/cwrs.c
CSRC +=$(DIR)/celt/entcode.c
CSRC +=$(DIR)/celt/entdec.c
CSRC +=$(DIR)/celt/entenc.c
CSRC +=$(DIR)/celt/kiss_fft.c
CSRC +=$(DIR)/celt/laplace.c
CSRC +=$(DIR)/celt/mathops.c
CSRC +=$(DIR)/celt/mdct.c
CSRC +=$(DIR)/celt/modes.c
CSRC +=$(DIR)/celt/pitch.c
CSRC +=$(DIR)/celt/celt_lpc.c
CSRC +=$(DIR)/celt/quant_bands.c
CSRC +=$(DIR)/celt/rate.c
CSRC +=$(DIR)/celt/vq.c


CSRC += $(DIR)/src/opus.c
CSRC +=$(DIR)/src/opus_decoder.c
CSRC +=$(DIR)/src/opus_encoder.c
CSRC +=$(DIR)/src/opus_multistream.c
CSRC +=$(DIR)/src/opus_multistream_encoder.c
CSRC +=$(DIR)/src/opus_multistream_decoder.c
CSRC +=$(DIR)/src/repacketizer.c
CSRC +=$(DIR)/src/opus_projection_encoder.c
CSRC +=$(DIR)/src/opus_projection_decoder.c
CSRC +=$(DIR)/src/mapping_matrix.c

#add for supporting encoding
CSRC +=$(DIR)/src/analysis.c
CSRC +=$(DIR)/src/mlp.c
CSRC +=$(DIR)/src/mlp_data.c

MODULE_IFLAGS += -I$(DIR)/celt
MODULE_IFLAGS += -I$(DIR)/silk
MODULE_IFLAGS += -I$(DIR)/silk/fixed
#MODULE_IFLAGS += -I$(DIR)/silk/float
MODULE_IFLAGS += -I$(DIR)/src
MODULE_IFLAGS += -I$(DIR)/include
MODULE_IFLAGS += -I$(DIR)/win32

#GLOBAL_CFLAGS += -DHAVE_CONFIG_H
#GLOBAL_CFLAGS += -DHAVE_ALLOCA_H
GLOBAL_CFLAGS += -DFIXED_POINT=1 
GLOBAL_CFLAGS += -DOPUS_BUILD=1
#GLOBAL_CFLAGS += -DDISABLE_FLOAT_API
GLOBAL_CFLAGS += -DVAR_ARRAYS=1
#GLOBAL_CFLAGS += -DUSE_ALLOCA=1
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))
STATIC_LIB = lib_opus.a
#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS:	$(OBJS) $(STATIC_LIB)
$(STATIC_LIB):$(OBJS)
	$(AR) rvs $@ $^
	$(MOVE) -f $@ $(ROOTDIR)/lib/application
#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)