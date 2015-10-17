#ifndef	MOAITBEDITFIELD_H
#define	MOAITBEDITFIELD_H

#include "MOAITBWidget.h"
#include "tb_editfield.h"

//================================================================//
// MOAITBEditField
//================================================================//

class MOAITBEditField :
	public MOAITBWidget {
private:
	
	static int _setMultiline       ( lua_State* L );
	static int _isMultiline        ( lua_State* L );
	static int _setStyling         ( lua_State* L );
	static int _isStyling          ( lua_State* L );
	static int _setReadOnly        ( lua_State* L );
	static int _isReadOnly         ( lua_State* L );
	static int _setWrapping        ( lua_State* L );
	static int _isWrapping         ( lua_State* L );
	static int _setAdaptToContent  ( lua_State* L );
	static int _isAdaptToContent   ( lua_State* L );
	static int _setVirtualWidth    ( lua_State* L );
	static int _getVirtualWidth    ( lua_State* L );	
	static int _setEditType        ( lua_State* L );
	static int _getEditType        ( lua_State* L );
	static int _setTextAlign       ( lua_State* L );
	static int _getTextAlign       ( lua_State* L );
	static int _setPlaceholderText ( lua_State* L );
	static int _getPlaceholderText ( lua_State* L );


	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBEditField )
	MOAI_TB_CREATE_INTERNAL ( TBEditField )

public:
	MOAI_TB_GET_INTERNAL    ( TBEditField )

  DECL_LUA_FACTORY ( MOAITBEditField )
	
	//----------------------------------------------------------------//
						MOAITBEditField			();
						~MOAITBEditField			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
