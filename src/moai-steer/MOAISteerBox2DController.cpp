#include "moai-steer/MOAISteerBox2DController.h"


void MOAISteerBox2DControllerMgr::Register ( b2Body* body, MOAISteerBox2DController* controller ) {
	this->mMap[ body ] = controller;
}

void MOAISteerBox2DControllerMgr::Unregister ( b2Body* body ) {
	this->mMap.erase( body );
}

MOAISteerBox2DController* MOAISteerBox2DControllerMgr::Find( b2Body* body ) {
	return this->mMap.value_for_key( body );
}

//----------------------------------------------------------------//
//----------------------------------------------------------------//

int MOAISteerBox2DController::_setBody ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DController, "UU" )
	MOAIBox2DBody* body = state.GetLuaObject < MOAIBox2DBody >( 2, 0 );
	if( body ){
		self->SetBody( body );
	}
	return 0;
}

int MOAISteerBox2DController::_setCollisionMask ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBox2DController, "UN" )
	u32 mask = state.GetValue < u32 >( 2, 0xffff );
	self->SetCollisionMask( mask );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerBox2DController::MOAISteerBox2DController() :
	mCollisionMask( 0xffff )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerController )
	RTTI_END
}

MOAISteerBox2DController::~MOAISteerBox2DController() {
	this->mBody.Set( *this, 0 );
}

//----------------------------------------------------------------//

void MOAISteerBox2DController::SetBody ( MOAIBox2DBody* body ) {
	MOAISteerBox2DControllerMgr& mgr = MOAISteerBox2DControllerMgr::Get();
	if( this->mBody ) {
		mgr.Unregister( this->mBody->GetBody() );
	}
	this->mBody.Set( *this, body );
	if( body ) {
		mgr.Register( body->GetBody(), this );
	}
}

ZLVec3D MOAISteerBox2DController::GetLoc() {
	if( !this->mBody ) return ZLVec3D();
	b2Body* body = this->mBody->GetBody();
	float unitsToMeters = this->mBody->GetUnitsToMeters ();
	b2Vec2 position = body->GetPosition ();
	return ZLVec3D( position.x / unitsToMeters, position.y / unitsToMeters, 0.0f );
}

float MOAISteerBox2DController::GetRot() {
	if( !this->mBody ) return 0.0f;
	b2Body* body = this->mBody->GetBody();
	return body->GetAngle() * ( float )R2D;
}

ZLVec3D MOAISteerBox2DController::GetLinearVelocity() {
	if( !this->mBody ) return ZLVec3D();
	b2Body* body = this->mBody->GetBody();
	float unitsToMeters = this->mBody->GetUnitsToMeters ();
	b2Vec2 velocity = body->GetLinearVelocity ();
	return ZLVec3D( velocity.x / unitsToMeters, velocity.y / unitsToMeters, 0.0f );
}

float MOAISteerBox2DController::GetAngularVelocity() {
	if( !this->mBody ) return 0.0f;
	b2Body* body = this->mBody->GetBody();
	float omega = body->GetAngularVelocity () * ( float )R2D;
	return omega;
}

void MOAISteerBox2DController::SetLinearVelocity  ( const ZLVec3D& v ) {
	if( !this->mBody ) return;
	float unitsToMeters = this->mBody->GetUnitsToMeters ();
	b2Body* body = this->mBody->GetBody();
	b2Vec2 b2velocity;
	b2velocity.x = v.mX * unitsToMeters;
	b2velocity.y = v.mY * unitsToMeters;
	body->SetLinearVelocity( b2velocity );
}

void MOAISteerBox2DController::SetAngularVelocity ( float v ) {
	if( !this->mBody ) return;
	b2Body* body = this->mBody->GetBody();
	float b2velocity = v * D2R;
	body->SetAngularVelocity( b2velocity );
}


void MOAISteerBox2DController::ApplySteerAcceleration( const MOAISteerAcceleration acc, double elapsed, double delta ) {
	if( !this->mBody ) return;
	b2Body* body = this->mBody->GetBody();
	float unitsToMeters = this->mBody->GetUnitsToMeters ();


	ZLVec3D linearAcc  = acc.mLinear;
	float   angularAcc = acc.mAngular;

	this->GetLimiter()->LimitLinearAcceleration  ( linearAcc );
	this->GetLimiter()->LimitAngularAcceleration ( angularAcc );

	#ifdef USE_IMPULSE
		float mass = body->GetMass();
		b2Vec2 impulse;
		impulse.x = linearAcc.mX * unitsToMeters * mass * delta;
		impulse.y = linearAcc.mY * unitsToMeters * mass * delta;
		body->ApplyLinearImpulse ( impulse, body->GetWorldCenter(), true );

		float inertia = body->GetInertia();
		float angularImpulse;
		angularImpulse = angularAcc * inertia * delta;
		
		body->ApplyAngularImpulse( angularImpulse, true );
		//TODO: limit speed

	#else
		ZLVec3D linearVelocity = this->GetLinearVelocity();
		linearVelocity.Add( linearAcc, delta );
		// linearVelocity.mX = b2LinearVelocity.x + acc.mLinear.mX * unitsToMeters * delta;
		// linearVelocity.mY = b2LinearVelocity.y + acc.mLinear.mY * unitsToMeters * delta;
		
		this->GetLimiter()->LimitLinearVelocity  ( linearVelocity );
		b2Vec2 newVelocity;
		newVelocity.x = linearVelocity.mX * unitsToMeters;
		newVelocity.y = linearVelocity.mY * unitsToMeters;
		body->SetLinearVelocity( newVelocity );
		
		float angularVelocity = this->GetAngularVelocity();
		angularVelocity += angularAcc * delta;

		this->GetLimiter()->LimitAngularVelocity ( angularVelocity );
		float newAngularVelocity = angularVelocity * D2R;
		body->SetAngularVelocity( newAngularVelocity );

	#endif

}

//----------------------------------------------------------------//
void MOAISteerBox2DController::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerController::RegisterLuaClass( state );
}

void MOAISteerBox2DController::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerController::RegisterLuaFuncs( state );

	luaL_Reg regTable [] = {
    { "setBody",   _setBody },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
