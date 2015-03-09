#include "moai-steer/MOAISteerSingleRayConfiguration.h"
#include "moai-steer/MOAISteerController.h"


//----------------------------------------------------------------//

int MOAISteerSingleRayConfiguration::_setLength ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerSingleRayConfiguration, "UN" )
	self->SetLength( state.GetValue < float >( 2, 0.0f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerSingleRayConfiguration::MOAISteerSingleRayConfiguration() :
	mLength( 10.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerRayConfiguration )
	RTTI_END
	this->mRays.Init( 1 );
}

MOAISteerSingleRayConfiguration::~MOAISteerSingleRayConfiguration() {
}


//----------------------------------------------------------------//
bool MOAISteerSingleRayConfiguration::UpdateRays( MOAISteerController* owner ) {
	if( this->mLength == 0.0f ) return false;

	ZLVec3D extent = owner->GetLinearVelocity();
	float length0 = extent.Length();
	if( length0 == 0.0f ) return false;

	extent.Scale( this->mLength / length0 );

	MOAISteerRay& ray = this->mRays[ 0 ];
	ray.mStart  = owner->GetLoc();
	ray.mEnd    = ray.mStart + extent;
	ray.mLength = this->mLength;

	return true;
}

//----------------------------------------------------------------//
void MOAISteerSingleRayConfiguration::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerRayConfiguration::RegisterLuaClass( state );
	UNUSED( state );
}

void MOAISteerSingleRayConfiguration::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerRayConfiguration::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setLength",     _setLength },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

