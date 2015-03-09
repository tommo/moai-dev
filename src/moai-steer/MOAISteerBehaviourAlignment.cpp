#include "moai-steer/MOAISteerBehaviourAlignment.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourAlignment::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourAlignment, "UU" )
	MOAISteerProximity* proximity = state.GetLuaObject < MOAISteerProximity >( 2, 0 );
	if( proximity ) {
		self->SetProximity( proximity );
	}
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourAlignment::MOAISteerBehaviourAlignment()
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourAlignment::~MOAISteerBehaviourAlignment() {
	this->mProximity.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourAlignment::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mProximity ) return false;
	this->mCurrentAcceleration = &acc;
	u32 count = this->mProximity->FindNeighbors( this );
	this->mCurrentAcceleration = NULL;	
	if( count == 0 ) return false;
	acc.mLinear.Scale( 1.0f/(float)count );
	return true;
}


bool MOAISteerBehaviourAlignment::OnReportNeighbor( MOAISteerController* neighbor ) {
	this->mCurrentAcceleration->mLinear.Add( neighbor->GetLinearVelocity() );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourAlignment::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourAlignment::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
