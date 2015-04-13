#ifndef	MOAITBWINDOW_H
#define	MOAITBWINDOW_H

#include "MOAITBWidget.h"
#include "tb_window.h"

//================================================================//
// MOAITBWindow
//================================================================//

class MOAITBWindow :
	public MOAITBWidget {
private:
	
	static int _isActive             ( lua_State* L );
	static int _activate             ( lua_State* L );
	static int _ensureFocus          ( lua_State* L );
	static int _setSettings          ( lua_State* L );
	static int _getSettings          ( lua_State* L );
	static int _resizeToFitContent   ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBWindow )
	MOAI_TB_CREATE_INTERNAL ( TBWindow )

public:
	MOAI_TB_GET_INTERNAL    ( TBWindow )

  DECL_LUA_FACTORY ( MOAITBWindow )
	
	//----------------------------------------------------------------//
						MOAITBWindow			();
						~MOAITBWindow			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
