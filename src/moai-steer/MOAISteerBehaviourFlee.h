#ifndef MOAISTEERBEHAVIOURFLEE_H
#define MOAISTEERBEHAVIOURFLEE_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourFlee:
	public MOAISteerBehaviour
{
private:
	static int _setup ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAITransformBase* mTarget;

public:

	void SetTarget( MOAITransformBase* target ) {
		this->mTarget = target;
		this->LuaRetain( this->mTarget );
	}
	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourFlee )

	MOAISteerBehaviourFlee();
	~MOAISteerBehaviourFlee();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
