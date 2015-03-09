#ifndef MOAISTEERBEHAVIOURSCRIPT_H
#define MOAISTEERBEHAVIOURSCRIPT_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourScript:
	public MOAISteerBehaviour
{
private:
	static int _setLinearAcceleration      ( lua_State* L );
	static int _setAngularAcceleration     ( lua_State* L );
	static int _getMaxLinearAcceleration   ( lua_State* L );
	static int _getMaxAngularAcceleration  ( lua_State* L );
	static int _getMaxLinearSpeed          ( lua_State* L );
	static int _getMaxAngularSpeed         ( lua_State* L );
	static int _setup                      ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	MOAILuaMemberRef		mOnCalculate;

	ZLVec3D mLinearAcceleration;
	float   mAngularAcceleration;

public:

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourScript )

	MOAISteerBehaviourScript();
	~MOAISteerBehaviourScript();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif