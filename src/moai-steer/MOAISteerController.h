#ifndef MOAISTEERCONTROLLER_H
#define MOAISTEERCONTROLLER_H

#include <moai-sim/headers.h>
#include "moai-steer/MOAISteerBehaviour.h"
#include "moai-steer/MOAISteerBehaviourGroup.h"

//----------------------------------------------------------------//
class MOAISteerController:
	public MOAIAction
{
private:
	friend class MOAISteerBehaviour;
	
	static int _getRoot               ( lua_State* L );
	static int _getLimiter            ( lua_State* L );
	static int _setLimiter            ( lua_State* L );
	static int _pushBehaviour         ( lua_State* L );
	static int _removeBehaviour       ( lua_State* L );
	static int _clearBehaviours       ( lua_State* L );

	static int _getRadius             ( lua_State* L );
	static int _setRadius             ( lua_State* L );

	static int _getLoc                ( lua_State* L );
	static int _getRot                ( lua_State* L );
	static int _getAngularVelocity    ( lua_State* L );
	static int _getLinearVelocity     ( lua_State* L );
	static int _getAngularSpeed       ( lua_State* L );
	static int _getLinearSpeed        ( lua_State* L );
	static int _getLinearAcceleration ( lua_State* L );
	static int _getAngularAcceleration( lua_State* L );

	static int _setLinearVeloicty     ( lua_State* L );
	static int _setAngularVeloicty    ( lua_State* L );


protected:

	double mElapsed;
	MOAISteerBehaviourRoot* mRootBehaviour;
	MOAISteerLimiter* mLimiter;
	MOAISteerAcceleration mAcceleration;

	float mRadius;

public:


	void OnUpdate ( double step );
	bool IsDone ();
	
	void PushBehaviour   ( MOAISteerBehaviour* behaviour );
	void PushBehaviour   ( MOAISteerBehaviour* behaviour, float weight );
	void RemoveBehaviour ( MOAISteerBehaviour* behaviour );
	void ClearBehaviours ();

	virtual ZLVec3D  GetLoc()                 { return ZLVec3D(); };
	virtual float    GetRot()                 { return 0.0f;      };
	virtual ZLVec3D  GetLinearVelocity()      { return ZLVec3D(); };
	virtual float    GetAngularVelocity()     { return 0.0f;      };
	virtual float    GetLinearSpeed()         { return this->GetLinearVelocity().Length(); };
	virtual float    GetAngularSpeed()        { return fabs( this->GetAngularVelocity() ); };
	virtual ZLVec3D  GetLinearAcceleration()  { return mAcceleration.mLinear; };
	virtual float    GetAngularAcceleration() { return mAcceleration.mAngular; };

	virtual void     ApplySteerAcceleration ( const MOAISteerAcceleration acc, double elapsed, double delta ) {};

	virtual float    GetRadius() { return mRadius; };
	virtual void     SetRadius( float radius ) { this->mRadius = radius; };

	MOAISteerBehaviourRoot* AffirmRoot();
	MOAISteerLimiter*       AffirmLimiter();

	GET ( MOAISteerBehaviourRoot*, RootBehaviour, mRootBehaviour )
	GET ( MOAISteerLimiter*,       Limiter,       mLimiter       )
	GET ( double, Elapsed, mElapsed )

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerController )

	MOAISteerController();
	~MOAISteerController();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};


#endif