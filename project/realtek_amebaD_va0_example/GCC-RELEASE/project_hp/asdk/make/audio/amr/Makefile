
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/audio/opencore-amr
NB_DEC_DIR = $(DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/src
NB_ENC_DIR = $(DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/enc/src
NB_COM_DIR = $(DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/src
WB_DEC_DIR = $(DIR)/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/src

MODULE_IFLAGS += -I$(DIR)

vpath %.cpp $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                          Header FILE Directory LIST                         #
#*****************************************************************************#
MODULE_IFLAGS = -I$(BASEDIR)/component/common/audio/opencore-amr/amrnb
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/amrwb
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/oscl
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/include
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/include
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/src
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_nb/enc/include
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_nb/enc/src
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/include
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/src
MODULE_IFLAGS += -I$(BASEDIR)/component/common/audio/opencore-amr/opencore/codecs_v2/audio/gsm_amr/common/dec/include

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/amrnb/wrapper.cpp
CSRC += $(DIR)/amrwb/wrapper_wb.cpp

CSRC += $(NB_DEC_DIR)/a_refl.cpp
CSRC += $(NB_DEC_DIR)/agc.cpp
CSRC += $(NB_DEC_DIR)/amrdecode.cpp
CSRC += $(NB_DEC_DIR)/b_cn_cod.cpp
CSRC += $(NB_DEC_DIR)/bgnscd.cpp
CSRC += $(NB_DEC_DIR)/c_g_aver.cpp
CSRC += $(NB_DEC_DIR)/d_gain_c.cpp
CSRC += $(NB_DEC_DIR)/d_gain_p.cpp
CSRC += $(NB_DEC_DIR)/d_plsf.cpp
CSRC += $(NB_DEC_DIR)/d_plsf_3.cpp
CSRC += $(NB_DEC_DIR)/d_plsf_5.cpp
CSRC += $(NB_DEC_DIR)/d2_9pf.cpp
CSRC += $(NB_DEC_DIR)/d2_11pf.cpp
CSRC += $(NB_DEC_DIR)/d3_14pf.cpp
CSRC += $(NB_DEC_DIR)/d4_17pf.cpp
CSRC += $(NB_DEC_DIR)/d8_31pf.cpp
CSRC += $(NB_DEC_DIR)/d1035pf.cpp
CSRC += $(NB_DEC_DIR)/dec_amr.cpp
CSRC += $(NB_DEC_DIR)/dec_gain.cpp
CSRC += $(NB_DEC_DIR)/dec_input_format_tab.cpp
CSRC += $(NB_DEC_DIR)/dec_lag3.cpp
CSRC += $(NB_DEC_DIR)/dec_lag6.cpp
#CSRC += $(NB_DEC_DIR)/decoder_gsm_amr.cpp
CSRC += $(NB_DEC_DIR)/dtx_dec.cpp
CSRC += $(NB_DEC_DIR)/ec_gains.cpp
CSRC += $(NB_DEC_DIR)/ex_ctrl.cpp
CSRC += $(NB_DEC_DIR)/if2_to_ets.cpp
CSRC += $(NB_DEC_DIR)/int_lsf.cpp
CSRC += $(NB_DEC_DIR)/lsp_avg.cpp
CSRC += $(NB_DEC_DIR)/ph_disp.cpp
CSRC += $(NB_DEC_DIR)/post_pro.cpp
CSRC += $(NB_DEC_DIR)/preemph.cpp
CSRC += $(NB_DEC_DIR)/pstfilt.cpp
CSRC += $(NB_DEC_DIR)/pvgsmamrdecoder.cpp
CSRC += $(NB_DEC_DIR)/qgain475_tab.cpp
CSRC += $(NB_DEC_DIR)/sp_dec.cpp
CSRC += $(NB_DEC_DIR)/wmf_to_ets.cpp

# CSRC += $(NB_EN_DIR)/amrencode.cpp
# CSRC += $(NB_EN_DIR)/autocorr.cpp
# CSRC += $(NB_EN_DIR)/c1035pf.cpp
# CSRC += $(NB_EN_DIR)/c2_11pf.cpp
# CSRC += $(NB_EN_DIR)/c2_9pf.cpp
# CSRC += $(NB_EN_DIR)/c3_14pf.cpp
# CSRC += $(NB_EN_DIR)/c4_17pf.cpp
# CSRC += $(NB_EN_DIR)/c8_31pf.cpp
# CSRC += $(NB_EN_DIR)/calc_cor.cpp
# CSRC += $(NB_EN_DIR)/calc_en.cpp
# CSRC += $(NB_EN_DIR)/cbsearch.cpp
# CSRC += $(NB_EN_DIR)/cl_ltp.cpp
# CSRC += $(NB_EN_DIR)/cod_amr.cpp
# CSRC += $(NB_EN_DIR)/convolve.cpp
# CSRC += $(NB_EN_DIR)/cor_h.cpp
# CSRC += $(NB_EN_DIR)/cor_h_x.cpp
# CSRC += $(NB_EN_DIR)/cor_h_x2.cpp
# CSRC += $(NB_EN_DIR)/corrwght_tab.cpp
# CSRC += $(NB_EN_DIR)/div_32.cpp
# CSRC += $(NB_EN_DIR)/dtx_enc.cpp
# CSRC += $(NB_EN_DIR)/enc_lag3.cpp
# CSRC += $(NB_EN_DIR)/enc_lag6.cpp
# CSRC += $(NB_EN_DIR)/enc_output_format_tab.cpp
# CSRC += $(NB_EN_DIR)/ets_to_if2.cpp
# CSRC += $(NB_EN_DIR)/ets_to_wmf.cpp
# CSRC += $(NB_EN_DIR)/g_adapt.cpp
# CSRC += $(NB_EN_DIR)/g_code.cpp
# CSRC += $(NB_EN_DIR)/g_pitch.cpp
# CSRC += $(NB_EN_DIR)/gain_q.cpp
# CSRC += $(NB_EN_DIR)/gsmamr_encoder_wrapper.cpp
# CSRC += $(NB_EN_DIR)/hp_max.cpp
# CSRC += $(NB_EN_DIR)/inter_36.cpp
# CSRC += $(NB_EN_DIR)/inter_36_tab.cpp
# CSRC += $(NB_EN_DIR)/l_abs.cpp
# CSRC += $(NB_EN_DIR)/l_comp.cpp
# CSRC += $(NB_EN_DIR)/l_extract.cpp
# CSRC += $(NB_EN_DIR)/l_negate.cpp
# CSRC += $(NB_EN_DIR)/lag_wind.cpp
# CSRC += $(NB_EN_DIR)/lag_wind_tab.cpp
# CSRC += $(NB_EN_DIR)/levinson.cpp
# CSRC += $(NB_EN_DIR)/lpc.cpp
# CSRC += $(NB_EN_DIR)/ol_ltp.cpp
# CSRC += $(NB_EN_DIR)/p_ol_wgh.cpp
# CSRC += $(NB_EN_DIR)/pitch_fr.cpp
# CSRC += $(NB_EN_DIR)/pitch_ol.cpp
# CSRC += $(NB_EN_DIR)/pre_big.cpp
# CSRC += $(NB_EN_DIR)/pre_proc.cpp
# CSRC += $(NB_EN_DIR)/prm2bits.cpp
# CSRC += $(NB_EN_DIR)/q_gain_c.cpp
# CSRC += $(NB_EN_DIR)/q_gain_p.cpp
# CSRC += $(NB_EN_DIR)/qgain475.cpp
# CSRC += $(NB_EN_DIR)/qgain795.cpp
# CSRC += $(NB_EN_DIR)/qua_gain.cpp
# CSRC += $(NB_EN_DIR)/s10_8pf.cpp
# CSRC += $(NB_EN_DIR)/set_sign.cpp
# CSRC += $(NB_EN_DIR)/sid_sync.cpp
# CSRC += $(NB_EN_DIR)/sp_enc.cpp
# CSRC += $(NB_EN_DIR)/spreproc.cpp
# CSRC += $(NB_EN_DIR)/spstproc.cpp
# CSRC += $(NB_EN_DIR)/ton_stab.cpp
# CSRC += $(NB_EN_DIR)/vad1.cpp 

CSRC += $(NB_COM_DIR)/add.cpp
CSRC += $(NB_COM_DIR)/az_lsp.cpp
CSRC += $(NB_COM_DIR)/bitno_tab.cpp
CSRC += $(NB_COM_DIR)/bitreorder_tab.cpp
CSRC += $(NB_COM_DIR)/c2_9pf_tab.cpp
CSRC += $(NB_COM_DIR)/div_s.cpp
CSRC += $(NB_COM_DIR)/gains_tbl.cpp
CSRC += $(NB_COM_DIR)/gc_pred.cpp
CSRC += $(NB_COM_DIR)/get_const_tbls.cpp
CSRC += $(NB_COM_DIR)/gmed_n.cpp
CSRC += $(NB_COM_DIR)/grid_tbl.cpp
CSRC += $(NB_COM_DIR)/gray_tbl.cpp
CSRC += $(NB_COM_DIR)/int_lpc.cpp
CSRC += $(NB_COM_DIR)/inv_sqrt.cpp
CSRC += $(NB_COM_DIR)/inv_sqrt_tbl.cpp
CSRC += $(NB_COM_DIR)/l_shr_r.cpp
CSRC += $(NB_COM_DIR)/log2.cpp
CSRC += $(NB_COM_DIR)/log2_norm.cpp
CSRC += $(NB_COM_DIR)/log2_tbl.cpp
CSRC += $(NB_COM_DIR)/lsfwt.cpp
CSRC += $(NB_COM_DIR)/lsp.cpp
CSRC += $(NB_COM_DIR)/lsp_az.cpp
CSRC += $(NB_COM_DIR)/lsp_lsf.cpp
CSRC += $(NB_COM_DIR)/lsp_lsf_tbl.cpp
CSRC += $(NB_COM_DIR)/lsp_tab.cpp
CSRC += $(NB_COM_DIR)/mult_r.cpp
CSRC += $(NB_COM_DIR)/norm_l.cpp
CSRC += $(NB_COM_DIR)/norm_s.cpp
CSRC += $(NB_COM_DIR)/overflow_tbl.cpp
CSRC += $(NB_COM_DIR)/ph_disp_tab.cpp
CSRC += $(NB_COM_DIR)/pow2.cpp
CSRC += $(NB_COM_DIR)/pow2_tbl.cpp
CSRC += $(NB_COM_DIR)/pred_lt.cpp
CSRC += $(NB_COM_DIR)/q_plsf.cpp
CSRC += $(NB_COM_DIR)/q_plsf_3.cpp
CSRC += $(NB_COM_DIR)/q_plsf_3_tbl.cpp
CSRC += $(NB_COM_DIR)/q_plsf_5.cpp
CSRC += $(NB_COM_DIR)/q_plsf_5_tbl.cpp
CSRC += $(NB_COM_DIR)/qua_gain_tbl.cpp
CSRC += $(NB_COM_DIR)/reorder.cpp
CSRC += $(NB_COM_DIR)/residu.cpp
CSRC += $(NB_COM_DIR)/round.cpp
CSRC += $(NB_COM_DIR)/shr.cpp
CSRC += $(NB_COM_DIR)/shr_r.cpp
CSRC += $(NB_COM_DIR)/sqrt_l.cpp
CSRC += $(NB_COM_DIR)/sqrt_l_tbl.cpp
CSRC += $(NB_COM_DIR)/sub.cpp
CSRC += $(NB_COM_DIR)/syn_filt.cpp
CSRC += $(NB_COM_DIR)/weight_a.cpp
CSRC += $(NB_COM_DIR)/window_tab.cpp

CSRC += $(WB_DEC_DIR_DIR)/agc2_amr_wb.cpp
CSRC += $(WB_DEC_DIR_DIR)/band_pass_6k_7k.cpp
CSRC += $(WB_DEC_DIR_DIR)/dec_acelp_2p_in_64.cpp
CSRC += $(WB_DEC_DIR_DIR)/dec_acelp_4p_in_64.cpp
CSRC += $(WB_DEC_DIR_DIR)/dec_alg_codebook.cpp
CSRC += $(WB_DEC_DIR_DIR)/dec_gain2_amr_wb.cpp
#CSRC += $(WB_DEC_DIR_DIR)/decoder_amr_wb.cpp
CSRC += $(WB_DEC_DIR_DIR)/deemphasis_32.cpp
CSRC += $(WB_DEC_DIR_DIR)/dtx_decoder_amr_wb.cpp
CSRC += $(WB_DEC_DIR_DIR)/get_amr_wb_bits.cpp
CSRC += $(WB_DEC_DIR_DIR)/highpass_400hz_at_12k8.cpp
CSRC += $(WB_DEC_DIR_DIR)/highpass_50hz_at_12k8.cpp
CSRC += $(WB_DEC_DIR_DIR)/homing_amr_wb_dec.cpp
CSRC += $(WB_DEC_DIR_DIR)/interpolate_isp.cpp
CSRC += $(WB_DEC_DIR_DIR)/isf_extrapolation.cpp
CSRC += $(WB_DEC_DIR_DIR)/isp_az.cpp
CSRC += $(WB_DEC_DIR_DIR)/isp_isf.cpp
CSRC += $(WB_DEC_DIR_DIR)/lagconceal.cpp
CSRC += $(WB_DEC_DIR_DIR)/low_pass_filt_7k.cpp
CSRC += $(WB_DEC_DIR_DIR)/median5.cpp
CSRC += $(WB_DEC_DIR_DIR)/mime_io.cpp
CSRC += $(WB_DEC_DIR_DIR)/noise_gen_amrwb.cpp
CSRC += $(WB_DEC_DIR_DIR)/normalize_amr_wb.cpp
CSRC += $(WB_DEC_DIR_DIR)/oversamp_12k8_to_16k.cpp
CSRC += $(WB_DEC_DIR_DIR)/phase_dispersion.cpp
CSRC += $(WB_DEC_DIR_DIR)/pit_shrp.cpp
CSRC += $(WB_DEC_DIR_DIR)/pred_lt4.cpp
CSRC += $(WB_DEC_DIR_DIR)/preemph_amrwb_dec.cpp
CSRC += $(WB_DEC_DIR_DIR)/pvamrwb_math_op.cpp
CSRC += $(WB_DEC_DIR_DIR)/pvamrwbdecoder.cpp
CSRC += $(WB_DEC_DIR_DIR)/q_gain2_tab.cpp
CSRC += $(WB_DEC_DIR_DIR)/qisf_ns.cpp
CSRC += $(WB_DEC_DIR_DIR)/qisf_ns_tab.cpp
CSRC += $(WB_DEC_DIR_DIR)/qpisf_2s.cpp
CSRC += $(WB_DEC_DIR_DIR)/qpisf_2s_tab.cpp
CSRC += $(WB_DEC_DIR_DIR)/scale_signal.cpp
CSRC += $(WB_DEC_DIR_DIR)/synthesis_amr_wb.cpp
CSRC += $(WB_DEC_DIR_DIR)/voice_factor.cpp
CSRC += $(WB_DEC_DIR_DIR)/wb_syn_filt.cpp
CSRC += $(WB_DEC_DIR_DIR)/weight_amrwb_lpc.cpp
	
#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.cpp=.o))
STATIC_LIB = lib_amr.a

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: CORE_TARGETS
	
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
	$(REMOVE) *.ii
-include $(DEPS)	
