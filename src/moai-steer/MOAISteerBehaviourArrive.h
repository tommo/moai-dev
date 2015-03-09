#ifndef MOAISTEERBEHAVIOURARRIVE_H
#define MOAISTEERBEHAVIOURARRIVE_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourArrive:
	public MOAISteerBehaviour
{
private:
	static int _setup             ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	float mArrivalTolerance;
	float mDecelerationRadius;
	float mTimeToTarget;

	MOAILuaSharedPtr < MOAITransformBase > mTarget;

public:

	GET_SET( float, ArrivalTolerance,    mArrivalTolerance   )
	GET_SET( float, DecelerationRadius,  mDecelerationRadius )
	GET_SET( float, TimeToTarget,        mTimeToTarget       )

	void SetTarget( MOAITransformBase* target ) {
		this->mTarget.Set( *this, target );		
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourArrive )

	MOAISteerBehaviourArrive();
	~MOAISteerBehaviourArrive();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif