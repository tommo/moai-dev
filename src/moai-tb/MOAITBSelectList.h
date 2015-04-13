#ifndef	MOAITBSELECTLIST_H
#define	MOAITBSELECTLIST_H

#include "MOAITBWidget.h"
#include "tb_select.h"

//================================================================//
// MOAITBSelectList
//================================================================//

class MOAITBSelectList :
	public MOAITBWidget {
private:
	
	// static int _setSqueezable    ( lua_State* L );
	// static int _getSqueezable    ( lua_State* L );
	// static int _setAutoRepeat    ( lua_State* L );
	// static int _getAutoRepeat    ( lua_State* L );
	// static int _setToggleMode    ( lua_State* L );
	// static int _getToggleMode    ( lua_State* L );


	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBSelectList )
	MOAI_TB_CREATE_INTERNAL ( TBSelectList )

public:
	MOAI_TB_GET_INTERNAL    ( TBSelectList )

  DECL_LUA_FACTORY ( MOAITBSelectList )
	
	//----------------------------------------------------------------//
						MOAITBSelectList			();
						~MOAITBSelectList			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
