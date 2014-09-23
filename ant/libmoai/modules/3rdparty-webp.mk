#================================================================#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#================================================================#

include $(CLEAR_VARS)

	LOCAL_MODULE 		:= webp
	LOCAL_ARM_MODE 		:= $(MY_ARM_MODE)
	LOCAL_CFLAGS		:= -include $(MOAI_SDK_HOME)/src/zl-vfs/zl_replace.h
	LOCAL_CFLAGS		+= -fvisibility=hidden
	LOCAL_C_INCLUDES 	:= $(MY_HEADER_SEARCH_PATHS)

	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/alpha.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/buffer.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/frame.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/idec.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/io.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/layer.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/quant.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/tree.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/vp8.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/vp8l.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dec/webp.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/demux/demux.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/cpu.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/dec_neon.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/dec_sse2.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/dec.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/enc_neon.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/enc_sse2.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/enc.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/lossless.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/upsampling_neon.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/upsampling_sse2.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/upsampling.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/dsp/yuv.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/bit_reader.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/bit_writer.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/color_cache.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/filters.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/huffman_encode.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/huffman.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/quant_levels_dec.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/quant_levels.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/rescaler.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/thread.c
	LOCAL_SRC_FILES 	+= $(MOAI_SDK_HOME)/3rdparty/libwebp-0.3.1/src/utils/utils.c

	include $(BUILD_STATIC_LIBRARY)


