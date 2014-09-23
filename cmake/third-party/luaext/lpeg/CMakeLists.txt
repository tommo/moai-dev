  project( lpeg )

 set ( LUAEXT_SOURCES 
      ${MOAI_ROOT}/3rdparty/lpeg-0.10.2/lpeg.c
      
    )

 add_library (lpeg STATIC ${LUAEXT_SOURCES})
 target_link_libraries ( lpeg ${LUA_LIB} )
 add_dependencies ( lpeg lualib-static)
set_target_properties( lpeg PROPERTIES FOLDER Third-Party )

 target_include_directories ( lpeg PUBLIC ${LUA_HEADERS})