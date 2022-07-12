
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/network/http2/nghttp2-1.31.0
IFLAGS += -I$(BASEDIR)/component/common/network/http2/nghttp2-1.31.0/includes
vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

CSRC +=	$(DIR)/nghttp2_buf.o \
		$(DIR)/nghttp2_callbacks.o \
		$(DIR)/nghttp2_debug.o \
		$(DIR)/nghttp2_frame.o \
		$(DIR)/nghttp2_hd.o \
		$(DIR)/nghttp2_hd_huffman.o \
		$(DIR)/nghttp2_hd_huffman_data.o \
		$(DIR)/nghttp2_helper.o \
		$(DIR)/nghttp2_http.o \
		$(DIR)/nghttp2_map.o \
		$(DIR)/nghttp2_mem.o \
		$(DIR)/nghttp2_npn.o \
		$(DIR)/nghttp2_option.o \
		$(DIR)/nghttp2_outbound_item.o \
		$(DIR)/nghttp2_pq.o \
		$(DIR)/nghttp2_priority_spec.o \
		$(DIR)/nghttp2_queue.o \
		$(DIR)/nghttp2_rcbuf.o \
		$(DIR)/nghttp2_session.o \
		$(DIR)/nghttp2_stream.o \
		$(DIR)/nghttp2_submit.o \
		$(DIR)/nghttp2_version.o \

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
	$(AR) rvs lib_http2.a $(OBJS)
	$(FROMELF) --strip-debug lib_http2.a
	$(MOVE) -f lib_http2.a $(ROOTDIR)/lib/application
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
