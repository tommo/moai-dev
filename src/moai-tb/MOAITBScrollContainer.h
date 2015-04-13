#ifndef	MOAITBScrollContainer_H
#define	MOAITBScrollContainer_H

#include "MOAITBWidget.h"
#include "tb_scroll_container.h"

//================================================================//
// MOAITBScrollContainer
//================================================================//

class MOAITBScrollContainer :
	public MOAITBWidget {
private:
	
	static int _setAdaptToContentSize    ( lua_State* L );
	static int _getAdaptToContentSize    ( lua_State* L );
	static int _setAdaptContentSize      ( lua_State* L );
	static int _getAdaptContentSize      ( lua_State* L );
	static int _setScrollMode            ( lua_State* L );
	static int _getScrollMode            ( lua_State* L );

	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBScrollContainer )
	MOAI_TB_CREATE_INTERNAL ( TBScrollContainer )

public:
	MOAI_TB_GET_INTERNAL    ( TBScrollContainer )

  DECL_LUA_FACTORY ( MOAITBScrollContainer )
	
	//----------------------------------------------------------------//
						MOAITBScrollContainer			();
						~MOAITBScrollContainer			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
