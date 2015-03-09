#include "moai-steer/MOAISteerProximity.h"


//----------------------------------------------------------------//
MOAISteerProximity::MOAISteerProximity()
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAINode )
	RTTI_END
}

MOAISteerProximity::~MOAISteerProximity() {
}

//----------------------------------------------------------------//
void MOAISteerProximity::RegisterLuaClass ( MOAILuaState& state ) {
	MOAINode::RegisterLuaClass( state );
}

void MOAISteerProximity::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAINode::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
