#include "moai-steer/MOAISteerBehaviourArrive.h"

int MOAISteerBehaviourArrive::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourArrive, "UUNNN" )
	MOAITransformBase* target = state.GetLuaObject < MOAITransformBase >( 2, 0 );
	if( !target ) return 0;
	self->SetTarget( target );
	self->SetTimeToTarget      ( state.GetValue < float >( 3, 1.0f )   );
	self->SetArrivalTolerance  ( state.GetValue < float >( 4, 10.0f )  );
	self->SetDecelerationRadius( state.GetValue < float >( 5, 100.0f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourArrive::MOAISteerBehaviourArrive() :
	mDecelerationRadius( 100.0f ),
	mArrivalTolerance( 1.0f ),
	mTimeToTarget( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourArrive::~MOAISteerBehaviourArrive() {
	this->mTarget.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourArrive::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	// Get the direction and distance to the target
	if( !this->mTarget ) return false;

	ZLVec3D toTarget = this->mTarget->GetWorldLoc() - this->GetOwner()->GetLoc();
	
	// Check if we are there, return no steering
	MOAISteerLimiter* actualLimiter = this->GetActualLimiter();
	float distance = toTarget.Length();

	if ( distance <= this->mArrivalTolerance ) {
		// return MOAISteerAcceleration();
		ZLVec3D targetVelocity ( 0.0f, 0.0f, 0.0f );
		ZLVec3D targetAcc = targetVelocity - this->GetOwner()->GetLinearVelocity();
		targetAcc.Scale( 1.0f / delta );
		actualLimiter->LimitLinearAcceleration( targetAcc );
		acc.mLinear.Init( targetAcc );

	} else {
		float targetSpeed = actualLimiter->GetMaxLinearSpeed();
		if ( ( distance - mArrivalTolerance ) <= mDecelerationRadius ) {
			targetSpeed *= ( distance - mArrivalTolerance ) / mDecelerationRadius;
		}
		ZLVec3D targetVelocity = toTarget;
		targetVelocity.Scale( targetSpeed / distance ); // Optimized code for: toTarget.nor().scl(targetSpeed)
		
		ZLVec3D targetAcc = targetVelocity - this->GetOwner()->GetLinearVelocity();
		targetAcc.Scale( 1.0f / this->mTimeToTarget / delta );
		actualLimiter->LimitLinearAcceleration( targetAcc );
		acc.mLinear.Init( targetAcc );
		
	}

	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourArrive::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourArrive::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",   _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
