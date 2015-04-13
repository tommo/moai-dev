#ifndef	MOAITBTOGGLECONTAINER_H
#define	MOAITBTOGGLECONTAINER_H

#include "MOAITBWidget.h"
#include "MOAITBCommon.h"
#include "MOAITBButton.h"
#include "tb_toggle_container.h"

//================================================================//
// MOAITBToggleContainer
//================================================================//

class MOAITBToggleContainer :
	public MOAITBWidget {
private:
	
	static int _setToggle    ( lua_State* L );
	static int _getToggle    ( lua_State* L );
	static int _setInvert    ( lua_State* L );
	static int _getInvert    ( lua_State* L );
	static int _isOn         ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBToggleContainer )
	MOAI_TB_CREATE_INTERNAL ( TBToggleContainer )

public:
	MOAI_TB_GET_INTERNAL    ( TBToggleContainer )

  DECL_LUA_FACTORY ( MOAITBToggleContainer )
	
	//----------------------------------------------------------------//
						MOAITBToggleContainer			();
						~MOAITBToggleContainer			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


//================================================================//
// MOAITBToggleContainer
//================================================================//

class MOAITBSection :
	public MOAITBWidget {
private:
	
	static int _getLayout                 ( lua_State* L );
	static int _getHeader                 ( lua_State* L );
	static int _getContainer              ( lua_State* L );
	static int _setPendingScrollIntoView  ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBSection )
	MOAI_TB_CREATE_INTERNAL ( TBSection )

public:
	MOAI_TB_GET_INTERNAL    ( TBSection )

  DECL_LUA_FACTORY ( MOAITBSection )
	
	//----------------------------------------------------------------//
						MOAITBSection			();
						~MOAITBSection			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAI_TB_EMPTY_WIDGET( SectionHeader, Button ) ;

#endif
