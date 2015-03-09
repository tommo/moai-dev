#ifndef MOAISTEERLIMITER_H
#define MOAISTEERLIMITER_H

#include "moai-core/headers.h"

class MOAISteerLimiter:
	public MOAILuaObject
{
private:
	static int _setMaxLinearSpeed          ( lua_State* L );
	static int _setMaxAngularSpeed         ( lua_State* L );
	static int _setMaxAngularAcceleration  ( lua_State* L );
	static int _setMaxLinearAcceleration   ( lua_State* L );

	//----------------------------------------------------------------//	
	float   mMaxLinearSpeed;
	float   mMaxAngularSpeed;
	float   mMaxLinearAcceleration;
	float   mMaxAngularAcceleration;

public:
	
	GET_SET( float, MaxLinearSpeed,         mMaxLinearSpeed         )
	GET_SET( float, MaxAngularSpeed,        mMaxAngularSpeed        )
	GET_SET( float, MaxLinearAcceleration,  mMaxLinearAcceleration  )
	GET_SET( float, MaxAngularAcceleration, mMaxAngularAcceleration )

	void LimitLinearVelocity       ( ZLVec3D& vel );
	void LimitLinearAcceleration   ( ZLVec3D& acc );
	void LimitAngularVelocity      ( float& vel );
	void LimitAngularAcceleration  ( float& acc );

	void FitMaxLinearVelocity      ( ZLVec3D& vel );
	void FitMaxLinearAcceleration  ( ZLVec3D& acc );
	void FitMaxAngularVelocity     ( float& vel );
	void FitMaxAngularAcceleration ( float& acc );

	
	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerLimiter )

	MOAISteerLimiter();
	~MOAISteerLimiter();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif