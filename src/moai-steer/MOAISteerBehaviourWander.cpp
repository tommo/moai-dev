#include "moai-steer/MOAISteerBehaviourWander.h"
#include "moai-steer/MOAISteerController.h"


int MOAISteerBehaviourWander::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourWander, "U" )
	self->SetWanderOffset      ( state.GetValue < float >( 2, 1.0f ) );
	self->SetWanderRadius      ( state.GetValue < float >( 3, 1.0f ) );
	self->SetWanderRate        ( state.GetValue < float >( 4, 1.0f ) );
	return 0;
}

int MOAISteerBehaviourWander::_setupFace ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourWander, "U" )
	self->SetFaceEnabled       ( state.GetValue < bool > ( 2, true )  );
	self->SetTimeToTarget      ( state.GetValue < float >( 3, 1.0f )  );
	self->SetAlignTolerance    ( state.GetValue < float >( 4, 10.0f ) );
	self->SetDecelerationRadius( state.GetValue < float >( 5, 30.0f ) );
	return 0;
}

int MOAISteerBehaviourWander::_setWanderOrientation ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourWander, "U" )
	self->SetWanderOrientation  ( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}


//----------------------------------------------------------------//
MOAISteerBehaviourWander::MOAISteerBehaviourWander() :
	mWanderOffset      ( 1.0f ),
	mWanderRadius      ( 1.0f ),
	mWanderRate        ( 1.0f ),
	mWanderOrientation ( 0.0f ),
	mFaceEnabled       ( false )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviourReachOrientation )
	RTTI_END
}

MOAISteerBehaviourWander::~MOAISteerBehaviourWander() {
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourWander::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	// Update the wander orientation
	// TODO it should be frame rate independent by interpreting wanderRate as a max distance per second.
	this->mWanderOrientation += ZLFloat::Rand( -this->mWanderRate, this->mWanderRate );

	// Calculate the combined target orientation
	float orientation = this->GetOwner()->GetRot();
	ZLVec3D vecOffset( Cos( orientation*D2R ), Sin( orientation*D2R ), 0.0f );

	// Calculate the center of the wander circle
	ZLVec3D wanderCenter = this->GetOwner()->GetLoc();
	wanderCenter.Add( vecOffset, this->mWanderOffset );

	// Calculate the target location
	// Notice that we're using steering.linear as temporary vector
	float targetOrientation = orientation + this->mWanderOrientation;
	ZLVec3D vecTarget( Cos( targetOrientation*D2R ), Sin( targetOrientation*D2R ), 0.0f );
	ZLVec3D targetLoc = wanderCenter;
	targetLoc.Add( vecTarget, this->mWanderRadius );

	if ( this->mFaceEnabled) {
		ZLVec3D diff = targetLoc - this->GetOwner()->GetLoc();
		if( diff.LengthSqrd() > 0.0f ) {
			float angle = atan2( diff.mY, diff.mX );
			this->SetTargetOrientation( angle * R2D );
			MOAISteerBehaviourReachOrientation::OnCalculate( acc, elapsed, delta );
		}
		acc.mLinear = vecOffset;
	} else {
		// Seek the internal target position
		acc.mLinear = targetLoc - this->GetOwner()->GetLoc();
	}

	this->GetActualLimiter()->FitMaxLinearAcceleration( acc.mLinear );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourWander::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviourReachOrientation::RegisterLuaClass( state );
}

void MOAISteerBehaviourWander::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviourReachOrientation::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setupFace",             _setupFace            },
		{ "setup",                 _setup                },
		{ "setWanderOrientation",  _setWanderOrientation },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
