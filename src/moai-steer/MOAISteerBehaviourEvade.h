#ifndef MOAISTEERBEHAVIOUREVADE_H
#define MOAISTEERBEHAVIOUREVADE_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourEvade:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaSharedPtr < MOAISteerController > mTarget;

	float mPredictionTime;

public:

	void SetTarget( MOAISteerController* target ) {
		this->mTarget.Set( *this, target );
	}

	GET_SET( float, PredictionTime, mPredictionTime )
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourEvade )

	MOAISteerBehaviourEvade();
	~MOAISteerBehaviourEvade();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
