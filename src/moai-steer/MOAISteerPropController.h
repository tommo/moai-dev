#ifndef MOAISTEERPROPCONTROLLER_H
#define MOAISTEERPROPCONTROLLER_H

#include "moai-steer/MOAISteerController.h"

class MOAISteerPropController:
	public MOAISteerController
{
private:
	static int _setProp     ( lua_State* L );
	static int _setRadius   ( lua_State* L );

	MOAILuaSharedPtr < MOAITransform > mProp;
	float   mRadius;
	ZLVec3D mLinearVelocity;
	float   mAngularVelocity;

public:

	virtual ZLVec3D GetLoc();
	virtual ZLVec3D GetLinearVelocity();
	virtual float   GetAngularVelocity();
	virtual float   GetRadius();
	virtual void    ApplySteerAcceleration( const MOAISteerAcceleration acc, double elapsed, double delta );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerPropController )

	MOAISteerPropController();
	~MOAISteerPropController();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );

};

#endif