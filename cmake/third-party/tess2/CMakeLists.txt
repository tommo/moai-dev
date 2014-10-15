cmake_minimum_required ( VERSION 2.8.5 )
project ( tess2 )

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/3rdparty/libtess2/Source/" )
set ( TESS2_INCLUDES "${MOAI_ROOT}/3rdparty/libtess2/Include/" )

file ( GLOB TESS2_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" )
file ( GLOB TESS2_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_library ( tess2 STATIC ${TESS2_SOURCES} ${TESS2_HEADERS} )
target_include_directories ( tess2 PUBLIC ${TESS2_INCLUDES} )
set_target_properties ( tess2 PROPERTIES FOLDER Third-Party )
