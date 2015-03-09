#include "moai-steer/MOAISteerBox2DRadiusProximity.h"


//----------------------------------------------------------------//
MOAISteerBox2DRadiusProximity::MOAISteerBox2DRadiusProximity() 
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBox2DAABBProximity )
	RTTI_END
}

MOAISteerBox2DRadiusProximity::~MOAISteerBox2DRadiusProximity() {
}

bool MOAISteerBox2DRadiusProximity::AcceptNeighbor ( MOAISteerController* neighbor ) {
	ZLVec3D diff = neighbor->GetLoc() - mCurrentController->GetLoc();
	float radius = this->mRadius;
	return diff.LengthSqrd() <= radius * radius;
}

//----------------------------------------------------------------//
void MOAISteerBox2DRadiusProximity::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBox2DAABBProximity::RegisterLuaClass( state );
}

void MOAISteerBox2DRadiusProximity::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBox2DAABBProximity::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

