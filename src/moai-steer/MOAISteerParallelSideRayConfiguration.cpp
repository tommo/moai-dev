#include "moai-steer/MOAISteerParallelSideRayConfiguration.h"
#include "moai-steer/MOAISteerController.h"


//----------------------------------------------------------------//

int MOAISteerParallelSideRayConfiguration::_setLength ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerParallelSideRayConfiguration, "UN" )
	self->SetLength( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

int MOAISteerParallelSideRayConfiguration::_setSideOffset ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerParallelSideRayConfiguration, "UN" )
	self->SetSideOffset( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}


//----------------------------------------------------------------//
MOAISteerParallelSideRayConfiguration::MOAISteerParallelSideRayConfiguration() :
	mLength( 10.0f ),
	mSideOffset( 0.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerRayConfiguration )
	RTTI_END
	this->mRays.Init( 2 );
}

MOAISteerParallelSideRayConfiguration::~MOAISteerParallelSideRayConfiguration() {
}


//----------------------------------------------------------------//
bool MOAISteerParallelSideRayConfiguration::UpdateRays( MOAISteerController* owner ) {
	if( this->mLength == 0.0f ) return false;

	ZLVec3D extent = owner->GetLinearVelocity();
	float length0 = extent.Length();
	if( length0 == 0.0f ) return false;

	ZLVec3D start  = owner->GetLoc();
	float offset = owner->GetRadius() + this->mSideOffset;
	float rot  = atan2( extent.mY, extent.mX );
	float rot0 = ( rot + 90.0f * D2R );
	ZLVec3D start0 ( 
		start.mX + Cos( rot0 ) * offset,
		start.mY + Sin( rot0 ) * offset,
		start.mZ
	);

	float rot1 = ( rot - 90.0f * D2R );
	ZLVec3D start1 ( 
		start.mX + Cos( rot1 ) * offset,
		start.mY + Sin( rot1 ) * offset,
		start.mZ
	);

	extent.Scale( this->mLength / length0 );

	MOAISteerRay& ray0 = this->mRays[ 0 ];
	ray0.mStart  = start0;
	ray0.mEnd    = start0 + extent;
	ray0.mLength = this->mLength;

	MOAISteerRay& ray1 = this->mRays[ 1 ];
	ray1.mStart  = start1; 
	ray1.mEnd    = start1 + extent; 
	ray1.mLength = this->mLength; 

	return true;
}

//----------------------------------------------------------------//
void MOAISteerParallelSideRayConfiguration::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerRayConfiguration::RegisterLuaClass( state );
	UNUSED( state );
}

void MOAISteerParallelSideRayConfiguration::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerRayConfiguration::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setSideOffset",     _setSideOffset },
		{ "setLength",         _setLength     },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

