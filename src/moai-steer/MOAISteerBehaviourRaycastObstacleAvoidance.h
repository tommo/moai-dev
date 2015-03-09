#ifndef MOAISTEERBEHAVIOURRAYCASTOBSTACLEAVOIDANCE_H
#define MOAISTEERBEHAVIOURRAYCASTOBSTACLEAVOIDANCE_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourRaycastObstacleAvoidance:
	public MOAISteerBehaviour
{
private:
	static int _setup             ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	float mDistanceFromObstacle;

	MOAILuaSharedPtr < MOAISteerRayCast > mRayCast;
	MOAILuaSharedPtr < MOAISteerRayConfiguration > mRayConfiguration;

public:

	GET_SET( float, DistanceFromObstacle,    mDistanceFromObstacle   )

	void SetRayCast( MOAISteerRayCast* rayCast ) {
		this->mRayCast.Set( *this, rayCast );		
	}

	void SetRayConfiguration( MOAISteerRayConfiguration* configuration ) {
		this->mRayConfiguration.Set( *this, configuration );		
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourRaycastObstacleAvoidance )

	MOAISteerBehaviourRaycastObstacleAvoidance();
	~MOAISteerBehaviourRaycastObstacleAvoidance();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif