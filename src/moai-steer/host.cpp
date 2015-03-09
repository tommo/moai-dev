
#include <moai-steer/host.h>
#include <moai-steer/headers.h>

//================================================================//
// aku-steer
//================================================================//

//----------------------------------------------------------------//
void AKUSteerAppFinalize () {
}

//----------------------------------------------------------------//
void AKUSteerAppInitialize () {
}

//----------------------------------------------------------------//
void AKUSteerContextInitialize () {

	REGISTER_LUA_CLASS ( MOAISteerController )
	REGISTER_LUA_CLASS ( MOAISteerBehaviour )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourGroup )
	REGISTER_LUA_CLASS ( MOAISteerProximity )
	REGISTER_LUA_CLASS ( MOAISteerLimiter )

	
	REGISTER_LUA_CLASS ( MOAISteerBehaviourArrive )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourSeek )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourFlee )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourPursue )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourEvade )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourSeparation )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourAlignment )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourCohesion )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourCollisionAvoidance )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourMatchVelocity )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourPathFollow )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourRaycastObstacleAvoidance )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourFace )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourReachOrientation )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourWander )

	REGISTER_LUA_CLASS ( MOAISteerBehaviourConstant )
	REGISTER_LUA_CLASS ( MOAISteerBehaviourScript )
	
	REGISTER_LUA_CLASS ( MOAISteerPath )
	REGISTER_LUA_CLASS ( MOAISteerLinePath )

	REGISTER_LUA_CLASS ( MOAISteerRayCast )
	REGISTER_LUA_CLASS ( MOAISteerRayConfiguration )
	REGISTER_LUA_CLASS ( MOAISteerSingleRayConfiguration )
	REGISTER_LUA_CLASS ( MOAISteerParallelSideRayConfiguration )

	//Box2D
	MOAISteerBox2DControllerMgr::Affirm();
	REGISTER_LUA_CLASS ( MOAISteerBox2DController )
	REGISTER_LUA_CLASS ( MOAISteerBox2DRayCast )
	REGISTER_LUA_CLASS ( MOAISteerBox2DAABBProximity )
	REGISTER_LUA_CLASS ( MOAISteerBox2DRadiusProximity )

	//Prop
	REGISTER_LUA_CLASS ( MOAISteerPropController )


}
