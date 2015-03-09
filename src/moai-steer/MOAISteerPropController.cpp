#include "moai-steer/MOAISteerPropController.h"

int MOAISteerPropController::_setProp ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPropController, "UU" )
	MOAITransform* t = state.GetLuaObject < MOAITransform >( 2, 0 );
	if( t ){
		self->mProp.Set( *self, t );
	}
	return 0;
}

int MOAISteerPropController::_setRadius ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerPropController, "UN" )
	self->mRadius = state.GetValue < float >( 2, 1.0f );
	return 0;
}

MOAISteerPropController::MOAISteerPropController() :
	mRadius( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerController )
	RTTI_END
}

MOAISteerPropController::~MOAISteerPropController() {
	this->mProp.Set( *this, 0 );
}

ZLVec3D MOAISteerPropController::GetLoc() {
	if( !this->mProp ) return ZLVec3D();
	return this->mProp->GetWorldLoc();
}

float MOAISteerPropController::GetRadius() {
	return this->mRadius;
}

float MOAISteerPropController::GetAngularVelocity() {
	return this->mAngularVelocity;
}

ZLVec3D MOAISteerPropController::GetLinearVelocity() {
	return this->mLinearVelocity;
}


void MOAISteerPropController::ApplySteerAcceleration( const MOAISteerAcceleration acc, double elapsed, double delta ) {
	if( !this->mProp ) return;
	//update velocity
	this->mLinearVelocity.Add( acc.mLinear, delta );
	ZLVec3D localDiff( this->mLinearVelocity );

	ZLAffine3D worldToModel = this->mProp->GetWorldToLocalMtx ();
	worldToModel.Transform ( localDiff );

	this->mProp->SetLoc( localDiff + mProp->GetLoc() );
	mProp->ScheduleUpdate();
}


//----------------------------------------------------------------//
void MOAISteerPropController::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerController::RegisterLuaClass( state );
}

void MOAISteerPropController::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerController::RegisterLuaFuncs( state );

	luaL_Reg regTable [] = {
    { "setProp",      _setProp   },
		{ "setRadius",    _setRadius },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
