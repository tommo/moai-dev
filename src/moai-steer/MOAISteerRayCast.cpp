#include "moai-steer/MOAISteerRayCast.h"


//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAISteerRayConfiguration::MOAISteerRayConfiguration() {
	RTTI_SINGLE( MOAISteerRayConfiguration )
}

MOAISteerRayConfiguration::~MOAISteerRayConfiguration() {
}


//----------------------------------------------------------------//
void MOAISteerRayConfiguration::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
}

void MOAISteerRayConfiguration::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}


//----------------------------------------------------------------//
//----------------------------------------------------------------//
MOAISteerRayCast::MOAISteerRayCast() {
	RTTI_SINGLE( MOAISteerRayCast )
}

MOAISteerRayCast::~MOAISteerRayCast() {
}


//----------------------------------------------------------------//
void MOAISteerRayCast::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
}

void MOAISteerRayCast::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
