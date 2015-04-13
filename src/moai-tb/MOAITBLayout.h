#ifndef	MOAITBLAYOUT_H
#define	MOAITBLAYOUT_H

#include "MOAITBWidget.h"
#include "tb_layout.h"

//================================================================//
// MOAITBLayout
//================================================================//

class MOAITBLayout :
	public MOAITBWidget {
private:
	static int _getSpacing                    ( lua_State* L );
	static int _setSpacing                    ( lua_State* L );
	static int _getOverflowScroll             ( lua_State* L );
	static int _setOverflowScroll             ( lua_State* L );
	static int _setPaintOverflowFadeout       ( lua_State* L );
	static int _setLayoutSize                 ( lua_State* L );
	static int _setLayoutPosition             ( lua_State* L );
	static int _setLayoutOverflow             ( lua_State* L );
	static int _setLayoutDistribution         ( lua_State* L );
	static int _setLayoutDistributionPosition ( lua_State* L );
	static int _setLayoutOrder                ( lua_State* L );
	
	//----------------------------------------------------------------//
	MOAI_TB_NEW( MOAITBLayout )
	MOAI_TB_CREATE_INTERNAL ( TBLayout )

public:
	MOAI_TB_GET_INTERNAL    ( TBLayout )

  DECL_LUA_FACTORY ( MOAITBLayout )
	
	//----------------------------------------------------------------//
						MOAITBLayout			();
						~MOAITBLayout			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
