#ifndef MOAISTEERBEHAVIOURSEEK_H
#define MOAISTEERBEHAVIOURSEEK_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourSeek:
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
	DECL_LUA_FACTORY ( MOAISteerBehaviourSeek )

	MOAISteerBehaviourSeek();
	~MOAISteerBehaviourSeek();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif
