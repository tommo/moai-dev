cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-crypto )

if ( BUILD_ANDROID )
  set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${MOAI_ROOT}/src/zl-vfs/zl_replace.h" )
   set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${MOAI_ROOT}/src/zl-vfs/zl_replace.h" )
endif ( BUILD_ANDROID )

set ( MOAI_CRYPTO_INCLUDES 
  "${MOAI_ROOT}/src/"
  "${MOAI_ROOT}/src/config-default/"
  )

include_directories ( 
  ${MOAI_CRYPTO_INCLUDES} 
)

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/moai-crypto/" )

file ( GLOB MOAI_CRYPTO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

include_directories ( ${MOAI_CRYPTO_INCLUDES} )

add_library ( moai-crypto STATIC ${MOAI_CRYPTO_SRC} )

target_link_libraries ( moai-crypto moai-core zlcore  )
target_link_libraries (moai-crypto crypto )
target_link_libraries (moai-crypto tinyxml )
set_target_properties( moai-crypto PROPERTIES FOLDER Core)
