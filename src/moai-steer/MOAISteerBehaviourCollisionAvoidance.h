#ifndef MOAISTEERBEHAVIOURCOLLISIONAVOIDANCE_H
#define MOAISTEERBEHAVIOURCOLLISIONAVOIDANCE_H

#include "moai-steer/headers.h"
#include "moai-steer/MOAISteerProximity.h"
#include "moai-steer/MOAISteerBehaviour.h"

class MOAISteerBehaviourCollisionAvoidance:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerProximity > mProximity;

	MOAISteerAcceleration* mCurrentAcceleration;
	//temp variable
	float                mShortestTime;
	MOAISteerController* mFirstNeighbor;
	float                mFirstMinSeparation;
	float                mFirstDistance;
	ZLVec3D              mFirstRelativePosition;
	ZLVec3D              mFirstRelativeVelocity;

public:

	void SetProximity( MOAISteerProximity* proximity ) {
		this->mProximity.Set( *this, proximity );
	}

	bool OnReportNeighbor( MOAISteerController* neighbor );

	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourCollisionAvoidance )

	MOAISteerBehaviourCollisionAvoidance();
	~MOAISteerBehaviourCollisionAvoidance();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
