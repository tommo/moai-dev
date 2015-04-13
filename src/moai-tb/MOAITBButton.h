#ifndef	MOAITBBUTTON_H
#define	MOAITBBUTTON_H

#include "MOAITBWidget.h"
#include "tb_widgets_common.h"

//================================================================//
// MOAITBButton
//================================================================//

class MOAITBButton :
	public MOAITBWidget {
private:
	
	static int _setSqueezable    ( lua_State* L );
	static int _getSqueezable    ( lua_State* L );
	static int _setAutoRepeat    ( lua_State* L );
	static int _getAutoRepeat    ( lua_State* L );
	static int _setToggleMode    ( lua_State* L );
	static int _getToggleMode    ( lua_State* L );


	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBButton )
	MOAI_TB_CREATE_INTERNAL ( TBButton )

public:
	MOAI_TB_GET_INTERNAL    ( TBButton )

  DECL_LUA_FACTORY ( MOAITBButton )
	
	//----------------------------------------------------------------//
						MOAITBButton			();
						~MOAITBButton			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
