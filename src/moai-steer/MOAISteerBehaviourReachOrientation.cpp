#include "moai-steer/MOAISteerBehaviourReachOrientation.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourReachOrientation::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourReachOrientation, "UN" )
	float target = state.GetValue < float >( 2, 0.0f );
	self->SetTargetOrientation ( target );
	self->SetTimeToTarget      ( state.GetValue < float >( 3, 1.0f )   );
	self->SetAlignTolerance    ( state.GetValue < float >( 4, 10.0f )  );
	self->SetDecelerationRadius( state.GetValue < float >( 5, 30.0f ) );
	return 0;
}

int MOAISteerBehaviourReachOrientation::_setTargetOrientation ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourReachOrientation, "UN" )
	float target = state.GetValue < float >( 2, 0.0f );
	self->SetTargetOrientation ( target );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourReachOrientation::MOAISteerBehaviourReachOrientation() :
	mTargetOrientation  ( 0.0f ),
	mAlignTolerance     ( 0.0f ),
	mTimeToTarget       ( 0.0f ),
	mDecelerationRadius ( 0.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourReachOrientation::~MOAISteerBehaviourReachOrientation() {
}


inline float wrapAngle( float angle )
{
    float a = angle - 360.0f * floor( angle / 360.0f );
    if( a > 180.f ) a -= 360.0f;
    return a;
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourReachOrientation::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	float rot = wrapAngle ( this->mTargetOrientation - this->GetOwner()->GetRot() );

	float targetVelocity = this->GetActualLimiter()->GetMaxAngularSpeed();

	float absRot = fabs( rot );
	if ( absRot <= this->mAlignTolerance ) {
		targetVelocity = 0.0f;
	} else {
		if ( absRot <= this->mDecelerationRadius ) { 
			targetVelocity *= absRot / this->mDecelerationRadius;
		}
		targetVelocity *= rot / absRot;
	}

	// Acceleration tries to get to the target rot
	float targetAcc;
	targetAcc = ( targetVelocity - this->GetOwner()->GetAngularVelocity() ) / this->mTimeToTarget / delta;

	// Check if the absolute acceleration is too great
	this->GetActualLimiter()->LimitAngularAcceleration( targetAcc );
	acc.mAngular = targetAcc;
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourReachOrientation::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourReachOrientation::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ "setTargetOrientation",    _setTargetOrientation },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
