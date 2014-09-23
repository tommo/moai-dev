cmake_minimum_required ( VERSION 2.8.5 )
project ( webp )

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/3rdparty/libwebp-0.3.1/src" )

set ( WEBP_INCLUDES "${MOAI_ROOT}/3rdparty/libwebp-0.3.1/src"  )

set ( WEBP_SOURCES 
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/alpha.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/buffer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/frame.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/idec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/io.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/layer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/quant.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/tree.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/vp8.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/vp8l.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dec/webp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/demux/demux.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/cpu.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/dec_neon.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/dec_sse2.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/dec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/enc_neon.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/enc_sse2.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/lossless.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/upsampling_neon.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/upsampling_sse2.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/upsampling.c
  ${CMAKE_CURRENT_SOURCE_DIR}/dsp/yuv.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/bit_reader.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/bit_writer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/color_cache.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/filters.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/huffman_encode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/huffman.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/quant_levels_dec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/quant_levels.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/rescaler.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/thread.c
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.c 
)

file ( GLOB_RECURSE WEBP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

include_directories ( ${WEBP_INCLUDES} )
add_library ( webp STATIC ${WEBP_SOURCES} ${WEBP_HEADERS} )
target_include_directories ( webp PUBLIC ${WEBP_INCLUDES} )
set_target_properties( webp PROPERTIES FOLDER Third-Party )