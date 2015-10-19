#include "MOAITBSkin.h"

//----------------------------------------------------------------//
// TODO: doxygen
int MOAITBSkin::_load ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBSkin, "US" )
	cc8* skinFile = state.GetValue < cc8* >( 2, "" );
	bool additive = state.GetValue < bool >( 3, false );
	bool reloadBitmap = state.GetValue < bool >( 4, true );
	if ( !additive ) { //destroy old one
		delete g_tb_skin;
		g_tb_skin = new TBSkin();
	}
	state.Push( (bool)self->mInternal->Load( skinFile, nullptr, reloadBitmap ) );
	return 1;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAITBSkin::_reloadBitmaps ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBSkin, "US" )
	self->mInternal->ReloadBitmaps();
	return 0;
}

//================================================================//
// MOAITBSkin
//================================================================//

//----------------------------------------------------------------//
MOAITBSkin::MOAITBSkin () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAITBSkin::~MOAITBSkin () {
}

//----------------------------------------------------------------//
void MOAITBSkin::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
	luaL_Reg regTable [] = {
		{ "new",             MOAILogMessages::_alertNewIsUnsupported },
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
}

void MOAITBSkin::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ "load",			      _load  },
		{ "reloadBitmaps",	_reloadBitmaps },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
