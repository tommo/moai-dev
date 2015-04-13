#ifndef	MOAITBTABCONTAINER_H
#define	MOAITBTABCONTAINER_H

#include "MOAITBWidget.h"
#include "MOAITBLayout.h"

#include "tb_tab_container.h"


//================================================================//
// MOAITBTabLayout
//================================================================//

class MOAITBTabLayout :
	public MOAITBLayout {
private:
	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBTabLayout )
	MOAI_TB_CREATE_INTERNAL ( TBTabLayout )

public:
	MOAI_TB_GET_INTERNAL    ( TBTabLayout )
  DECL_LUA_FACTORY ( MOAITBTabLayout )
						MOAITBTabLayout			();
						~MOAITBTabLayout			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};


//================================================================//
// MOAITBTabContainer
//================================================================//

class MOAITBTabContainer :
	public MOAITBWidget {
private:
	
	static int _setAlignment         ( lua_State* L );
	static int _getAlignment         ( lua_State* L );
	static int _setCurrentPage       ( lua_State* L );
	static int _getCurrentPage       ( lua_State* L );
	static int _getPageCount         ( lua_State* L );
	static int _getCurrentPageWidget ( lua_State* L );
	static int _getTabLayout        ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBTabContainer )
	MOAI_TB_CREATE_INTERNAL ( TBTabContainer )

public:
	MOAI_TB_GET_INTERNAL    ( TBTabContainer )

  DECL_LUA_FACTORY ( MOAITBTabContainer )
	
	//----------------------------------------------------------------//
						MOAITBTabContainer			();
						~MOAITBTabContainer			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
