#include "MOAITBPropContainer.h"
#include "TBRendererMOAI.h"

//----------------------------------------------------------------//
TBPropContainer::TBPropContainer():
	mProp( 0 )
{

}

TBPropContainer::~TBPropContainer() {
	if( this->mProp )
		this->mProp->Release();
}

void TBPropContainer::SetProp( MOAIGraphicsProp* prop ) {
	if( this->mProp ) this->mProp->Release();
	this->mProp = prop;
	if( prop ) prop->Retain();
}

void TBPropContainer::OnPaint(const PaintProps &paint_props) {
	if( !this->mProp ) return;
	//TODO: renderer state retain/restore
	static_cast< TBRendererMOAI* >(g_renderer)->RenderMOAIProp( this->mProp );
}


//----------------------------------------------------------------//
int MOAITBPropContainer::_setProp ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAITBPropContainer, "U" )
	MOAIGraphicsProp* prop = state.GetLuaObject< MOAIGraphicsProp >( 2, true );
	self->GetInternal()->SetProp( prop );
	return 0;
}


//----------------------------------------------------------------//
MOAITBPropContainer::MOAITBPropContainer () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITBWidget )
	RTTI_END	
}

//----------------------------------------------------------------//
MOAITBPropContainer::~MOAITBPropContainer () {
}


//----------------------------------------------------------------//
void MOAITBPropContainer::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaClass( state );
	
	luaL_Reg regTable [] = {
		{ "new", _new },
		{ NULL,  NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITBPropContainer::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITBWidget::RegisterLuaFuncs( state );
	
	luaL_Reg regTable [] = {
		{ "setProp",   _setProp },
		{ NULL, NULL  }
	};
	
	luaL_register ( state, 0, regTable );
}
