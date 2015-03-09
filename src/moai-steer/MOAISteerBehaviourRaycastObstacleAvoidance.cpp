#include "moai-steer/MOAISteerBehaviourRaycastObstacleAvoidance.h"

int MOAISteerBehaviourRaycastObstacleAvoidance::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourRaycastObstacleAvoidance, "UUUN" )
	MOAISteerRayCast* rayCast = state.GetLuaObject < MOAISteerRayCast >( 2, 0 );
	if( !rayCast ) return 0;
	MOAISteerRayConfiguration* rayConfiguration = state.GetLuaObject < MOAISteerRayConfiguration >( 3, 0 );
	if( !rayConfiguration ) return 0;
	self->SetRayCast( rayCast );
	self->SetRayConfiguration( rayConfiguration );
	self->SetDistanceFromObstacle ( state.GetValue < float >( 4, 1.0f )   );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBehaviourRaycastObstacleAvoidance::MOAISteerBehaviourRaycastObstacleAvoidance() :
	mDistanceFromObstacle( 10.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourRaycastObstacleAvoidance::~MOAISteerBehaviourRaycastObstacleAvoidance() {
	this->mRayCast.Set( *this, 0 );
	this->mRayConfiguration.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourRaycastObstacleAvoidance::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mRayCast ) return false;
	if( !this->mRayConfiguration ) return false;
	
	MOAISteerController* owner = this->GetOwner();
	const ZLVec3D& loc = owner->GetLoc();
	MOAISteerRayCastResult result;
	MOAISteerRayCastResult tmpResult;
	float minDistanceSquare = FLT_MAX;

	if( !mRayConfiguration->UpdateRays( owner ) ) return false;
	ZLLeanArray< MOAISteerRay > & rays = mRayConfiguration->GetRays();

	// Process rays
	for ( u32 i = 0; i < rays.Size(); ++i ) {
		// Find the collision with current ray
		bool collided = mRayCast->FindCollision( tmpResult, owner, rays[ i ] );
		if ( collided ) {
			float distanceSquare = loc.DistSqrd( tmpResult.mPoint );
			if ( distanceSquare < minDistanceSquare ) {
				minDistanceSquare = distanceSquare;
				result.mPoint  = tmpResult.mPoint;
				result.mNormal = tmpResult.mNormal;
			}
		}
	}

	// Return zero steering if no collision has occurred
	if (minDistanceSquare == FLT_MAX) return false;

	// Calculate and seek the target position
	float distance = this->mDistanceFromObstacle + owner->GetRadius();
	ZLVec3D targetAcc( result.mPoint );
	targetAcc.Add( result.mNormal, distance );
	targetAcc.Sub( loc );
	this->GetActualLimiter()->FitMaxLinearAcceleration( targetAcc );

	// Output steering acceleration
	acc.mLinear.Init( targetAcc );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourRaycastObstacleAvoidance::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourRaycastObstacleAvoidance::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",   _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

