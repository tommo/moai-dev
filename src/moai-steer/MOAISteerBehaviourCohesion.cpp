#include "moai-steer/MOAISteerBehaviourCohesion.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourCohesion::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourCohesion, "UU" )
	MOAISteerProximity* proximity = state.GetLuaObject < MOAISteerProximity >( 2, 0 );
	if( proximity ) {
		self->SetProximity( proximity );
	}
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourCohesion::MOAISteerBehaviourCohesion()
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourCohesion::~MOAISteerBehaviourCohesion() {
	this->mProximity.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourCohesion::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mProximity ) return false;
	this->mCenterOfMass.Init( 0.0f, 0.0f, 0.0f );
	u32 count = this->mProximity->FindNeighbors( this );
	if( count == 0 ) return false;

	this->mCenterOfMass.Scale( 1.0f/(float)count );

	acc.mLinear = this->mCenterOfMass - this->GetOwner()->GetLoc();
	this->GetActualLimiter()->FitMaxLinearAcceleration( acc.mLinear );
	return true;
}


bool MOAISteerBehaviourCohesion::OnReportNeighbor( MOAISteerController* neighbor ) {
	this->mCenterOfMass.Add( neighbor->GetLoc() );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourCohesion::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourCohesion::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
