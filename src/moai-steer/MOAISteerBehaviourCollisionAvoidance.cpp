#include "moai-steer/MOAISteerBehaviourCollisionAvoidance.h"
#include "moai-steer/MOAISteerController.h"

int MOAISteerBehaviourCollisionAvoidance::_setup ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourCollisionAvoidance, "UU" )
	MOAISteerProximity* proximity = state.GetLuaObject < MOAISteerProximity >( 2, 0 );
	if( proximity ) {
		self->SetProximity( proximity );
	}
	return 0;
}
//----------------------------------------------------------------//
MOAISteerBehaviourCollisionAvoidance::MOAISteerBehaviourCollisionAvoidance()
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourCollisionAvoidance::~MOAISteerBehaviourCollisionAvoidance() {
	this->mProximity.Set( *this, 0 );
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourCollisionAvoidance::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {
	if( !this->mProximity ) return false;
	this->mShortestTime       = FLT_MAX;
	this->mFirstNeighbor      = NULL;
	this->mFirstMinSeparation = 0;
	this->mFirstDistance      = 0;
	
	ZLVec3D relativePosition;

	// Take into consideration each neighbor to find the most imminent collision.
	u32 count = this->mProximity->FindNeighbors( this );

	// If we have no target, then return no steering acceleration
	if ( count == 0 || this->mFirstNeighbor == NULL ) return false;

	// If we're going to hit exactly, or if we're already
	// colliding, then do the steering based on current position.
	if ( this->mFirstMinSeparation <= 0
		|| this->mFirstDistance < this->GetOwner()->GetRadius() + this->mFirstNeighbor->GetRadius() )
	{
		relativePosition.Init( this->mFirstNeighbor->GetLoc() - this->GetOwner()->GetLoc() );
	} else {
		// Otherwise calculate the future relative position
		relativePosition.Init( this->mFirstRelativePosition );
		relativePosition.Add( this->mFirstRelativeVelocity, this->mShortestTime );
	}

	// Avoid the target
	// Notice that steerling.linear and relativePosition are the same vector
	acc.mLinear.Init( relativePosition );
	acc.mLinear.NormSafe();
	acc.mLinear.Scale( -this->GetActualLimiter()->GetMaxLinearAcceleration() );

	return true;
}


bool MOAISteerBehaviourCollisionAvoidance::OnReportNeighbor( MOAISteerController* neighbor ) {
	ZLVec3D	relativePosition = neighbor->GetLoc() - this->GetOwner()->GetLoc();
	ZLVec3D relativeVelocity = neighbor->GetLinearVelocity() - this->GetOwner()->GetLinearVelocity();
	
	float relativeSpeedSqrd = relativeVelocity.LengthSqrd();
	if( relativeSpeedSqrd == 0.0f ) return true;
	
	ZLVec3D	relativePositionNegative( relativePosition );
	relativePositionNegative.Reverse();
	float timeToCollision = relativePositionNegative.Dot( relativeVelocity ) / relativeSpeedSqrd;
	// If timeToCollision is negative, i.e. the owner is already moving away from the the neighbor,
	// or it's not the most imminent collision then no action needs to be taken.
	if ( timeToCollision <= 0 || timeToCollision >= this->mShortestTime ) return true;

	// Check if it is going to be a collision at all
	float distance = relativePosition.Length();
	float minSeparation = distance - sqrtf( relativeSpeedSqrd ) * timeToCollision /* shortestTime */;
	float minDistance = this->GetOwner()->GetRadius() + neighbor->GetRadius();
	if ( minSeparation > minDistance ) return true;

	// Store most imminent collision data
	this->mShortestTime = timeToCollision;
	this->mFirstNeighbor = neighbor;
	this->mFirstMinSeparation = minSeparation;
	this->mFirstDistance = distance;
	this->mFirstRelativePosition.Init( relativePosition );
	this->mFirstRelativeVelocity.Init( relativeVelocity );
	return true;
}


//----------------------------------------------------------------//
void MOAISteerBehaviourCollisionAvoidance::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourCollisionAvoidance::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setup",    _setup },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
