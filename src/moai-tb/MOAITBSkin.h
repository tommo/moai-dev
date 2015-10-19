#ifndef SKIN_H
#define SKIN_H

#include <moai-core/headers.h>
#include "tb_skin.h"

using namespace tb;
//================================================================//
// MOAITBSkin
//================================================================//
// TODO: doxygen
class MOAITBSkin :
	public MOAILuaObject{
private:
		//----------------------------------------------------------------//
		static int		_load            ( lua_State* L );
		static int		_reloadBitmaps   ( lua_State* L );

		TBSkin* mInternal;

public:
	
	GET( TBSkin*, Internal, mInternal )

	DECL_LUA_FACTORY ( MOAITBSkin )

	//----------------------------------------------------------------//
					MOAITBSkin			();
					~MOAITBSkin			();
	void    RegisterLuaClass ( MOAILuaState& state );
	void    RegisterLuaFuncs ( MOAILuaState& state );
};

#endif
