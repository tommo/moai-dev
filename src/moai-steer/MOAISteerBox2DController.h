#ifndef MOAISTEERBOX2DCONTROLLER_H
#define MOAISTEERBOX2DCONTROLLER_H

#include "moai-steer/MOAISteerController.h"
#include "moai-steer/MOAISteerBehaviour.h"

#include "moai-box2d/headers.h"


class MOAISteerBox2DController:
	public virtual MOAISteerController
{
private:
	static int _setBody            ( lua_State* L );
	static int _setCollisionMask   ( lua_State* L );

	MOAILuaSharedPtr < MOAIBox2DBody > mBody;

	// u32 mNeighborMask;
	u32 mCollisionMask;

public:

	MOAIBox2DBody* GetBody() { return mBody; };
	void SetBody( MOAIBox2DBody* body );

	GET_SET( u32, CollisionMask, mCollisionMask )


	virtual ZLVec3D GetLoc();
	virtual float   GetRot();
	virtual ZLVec3D GetLinearVelocity();
	virtual float   GetAngularVelocity();
	virtual void    ApplySteerAcceleration( const MOAISteerAcceleration acc, double elapsed, double delta );


	//----------------------------------------------------------------//	
	DECL_LUA_FACTORY ( MOAISteerBox2DController )

	MOAISteerBox2DController();
	~MOAISteerBox2DController();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );

	//----------------------------------------------------------------//
	//registry

};


//----------------------------------------------------------------//
//Mgr
//----------------------------------------------------------------//
class MOAISteerBox2DControllerMgr:
	public MOAIGlobalClass < MOAISteerBox2DControllerMgr > 
{
private:
	STLMap < b2Body*, MOAISteerBox2DController* > mMap;
public:
	void Register   ( b2Body* body, MOAISteerBox2DController* controller );
	void Unregister ( b2Body* body );
	MOAISteerBox2DController* Find( b2Body* body );
};

#endif