#ifndef MOAISTEERBEHAVIOURMATCHVELOCITY_H
#define MOAISTEERBEHAVIOURMATCHVELOCITY_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourMatchVelocity:
	public MOAISteerBehaviour
{
private:
	static int _setup             ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	float mTimeToTarget;
	MOAILuaSharedPtr < MOAISteerController > mTarget;

public:

	GET_SET( float, TimeToTarget,        mTimeToTarget       )

	void SetTarget( MOAISteerController* target ) {
		this->mTarget.Set( *this, target );		
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourMatchVelocity )

	MOAISteerBehaviourMatchVelocity();
	~MOAISteerBehaviourMatchVelocity();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif