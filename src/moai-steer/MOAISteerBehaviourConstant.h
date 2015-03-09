#ifndef MOAISTEERBEHAVIOURCONSTANT_H
#define MOAISTEERBEHAVIOURCONSTANT_H

#include "moai-steer/headers.h"

class MOAISteerBehaviourConstant:
	public MOAISteerBehaviour
{
private:
	static int _setLinearAcceleration      ( lua_State* L );
	static int _setAngularAcceleration     ( lua_State* L );
	static int _setLinearVelocity          ( lua_State* L );
	static int _setAngularVelocity         ( lua_State* L );
	static int _setLinearSpeed             ( lua_State* L );
	static int _setAngularSpeed            ( lua_State* L );

	//----------------------------------------------------------------//
	virtual bool OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta );
	
	ZLVec3D mLinearVelocity;
	ZLVec3D mLinearAcceleration;
	float   mLinearSpeed;

	float   mAngularVelocity;
	float   mAngularAcceleration;
	float   mAngularSpeed;

	u32     mFlags;
	
	static const u32 ANGULAR_ACCELERATION  = 1;
	static const u32 LINEAR_ACCELERATION   = 2;
	static const u32 ANGULAR_VELOCITY      = 4;
	static const u32 LINEAR_VELOCITY       = 8;
	static const u32 ANGULAR_SPEED         = 16;
	static const u32 LINEAR_SPEED          = 3;

public:

  GET_SET( ZLVec3D, LinearVelocity,      mLinearVelocity      )
  GET_SET( ZLVec3D, LinearAcceleration,  mLinearAcceleration  )
  GET_SET( float,   LinearSpeed,         mLinearSpeed         )
  
  GET_SET( float,   AngularVelocity,     mAngularVelocity     )
	GET_SET( float,   AngularAcceleration, mAngularAcceleration )
  GET_SET( float,   AngularSpeed,        mAngularSpeed        )

  void SetAngularAccelerationEnabled ( bool enabled );
	void SetLinearAccelerationEnabled  ( bool enabled );
	void SetAngularVelocityEnabled     ( bool enabled );
	void SetLinearVelocityEnabled      ( bool enabled );
	void SetAngularSpeedEnabled        ( bool enabled );
	void SetLinearSpeedEnabled         ( bool enabled );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerBehaviourConstant )

	MOAISteerBehaviourConstant();
	~MOAISteerBehaviourConstant();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif