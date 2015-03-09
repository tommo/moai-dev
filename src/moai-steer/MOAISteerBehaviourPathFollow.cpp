#include "moai-steer/MOAISteerBehaviourPathFollow.h"

int MOAISteerBehaviourPathFollow::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourPathFollow, "UU" )
	MOAISteerPath* path = state.GetLuaObject < MOAISteerPath >( 2, 0 );
	if( !path ) return 0;
	self->SetPath( path );
	self->SetPathOffset         ( state.GetValue < float >( 3, 0.0f )   );
	self->SetTimeToTarget       ( state.GetValue < float >( 4, 1.0f )   );
	self->SetArrivalTolerance   ( state.GetValue < float >( 5, 10.0f )  );
	self->SetDecelerationRadius ( state.GetValue < float >( 6, 100.0f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourPathFollow::MOAISteerBehaviourPathFollow() :
	mPathOffset ( 0.0f ),
	mArriveEnabled ( false ),
	mDecelerationRadius( 100.0f ),
	mArrivalTolerance( 1.0f ),
	mTimeToTarget( 1.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourPathFollow::~MOAISteerBehaviourPathFollow() {
	this->mPath.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourPathFollow::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mPath ) return false;

	ZLVec3D targetPosition;
	ZLVec3D position = this->GetOwner()->GetLoc();
	// Predictive or non-predictive behavior?
	// T location = (predictionTime == 0) ?
	// // Use the current position of the owner
	// owner.getPosition()
	// 	:
	// 	// Calculate the predicted future position of the owner. We're reusing steering.linear here.
	// 	steering.linear.set(owner.getPosition()).mulAdd(owner.getLinearVelocity(), predictionTime);

	// Find the distance from the start of the path
	float distance;
	ZLVec3D nearest = this->mPath->FindNearestPoint( position, distance );

	// Offset it
	float targetDistance = distance + mPathOffset;

	// Calculate the target position
	targetPosition = this->mPath->FindPointOnPath( targetDistance );

	if ( this->mArriveEnabled && !this->mPath->IsLoop() ) {
		// if (pathOffset >= 0) {
		// 	// Use Arrive to approach the last point of the path
		// 	if (targetDistance > path.getLength() - decelerationRadius) return arrive(steering, internalTargetPosition);
		// } else {
		// 	// Use Arrive to approach the first point of the path
		// 	if (targetDistance < decelerationRadius) return arrive(steering, internalTargetPosition);
		// }
	}

	// Seek the target position
	acc.mLinear.Init( targetPosition - position );
	this->GetActualLimiter()->FitMaxLinearAcceleration( acc.mLinear );

	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourPathFollow::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourPathFollow::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",   _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
