#include "moai-steer/MOAISteerLimiter.h"

int MOAISteerLimiter::_setMaxLinearSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLimiter, "UN" )
	self->SetMaxLinearSpeed( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

int MOAISteerLimiter::_setMaxLinearAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLimiter, "UN" )
	self->SetMaxLinearAcceleration( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

int MOAISteerLimiter::_setMaxAngularSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLimiter, "UN" )
	self->SetMaxAngularSpeed( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

int MOAISteerLimiter::_setMaxAngularAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLimiter, "UN" )
	self->SetMaxAngularAcceleration( state.GetValue < float >( 2, 1.0f ) );
	return 0;
}

//----------------------------------------------------------------//
MOAISteerLimiter::MOAISteerLimiter() :
	mMaxLinearSpeed( 100.0f ),
	mMaxAngularSpeed( 100.0f ),
	mMaxLinearAcceleration( 10.0f ),
	mMaxAngularAcceleration( 10.0f )
{
	RTTI_SINGLE( MOAISteerLimiter )
}

MOAISteerLimiter::~MOAISteerLimiter() {
}

//----------------------------------------------------------------//
void MOAISteerLimiter::LimitLinearVelocity ( ZLVec3D& vec ) {
	float l = vec.Length();
	if( l > this->mMaxLinearSpeed ) {
		vec.NormSafe();
		vec.Scale( this->mMaxLinearSpeed );
	}
}

void MOAISteerLimiter::LimitAngularVelocity( float& v ) {
	if( v > 0 ){
		if( v > this->mMaxAngularSpeed ) v = this->mMaxAngularSpeed;
	} else {
		if( v < -this->mMaxAngularSpeed ) v = -this->mMaxAngularSpeed;
	}
}

void MOAISteerLimiter::LimitLinearAcceleration ( ZLVec3D& vec ) {
	float l = vec.Length();
	if( l > this->mMaxLinearAcceleration ) {
		vec.NormSafe();
		vec.Scale( this->mMaxLinearAcceleration );
	}
}

void MOAISteerLimiter::LimitAngularAcceleration ( float& v ) {
	if( v > 0 ){
		if( v > this->mMaxAngularAcceleration ) v = this->mMaxAngularAcceleration;
	} else {
		if( v < -this->mMaxAngularAcceleration ) v = -this->mMaxAngularAcceleration;
	}
}

void MOAISteerLimiter::FitMaxLinearVelocity ( ZLVec3D& vec ) {
	vec.NormSafe();
	vec.Scale( this->mMaxLinearSpeed );
}

void MOAISteerLimiter::FitMaxAngularVelocity ( float& v ) {
	if( v > 0 ) {
		v = this->mMaxAngularSpeed;
	} else if( v < 0 ) {
		v = - this->mMaxAngularSpeed;
	}
}

void MOAISteerLimiter::FitMaxLinearAcceleration ( ZLVec3D& vec ) {
	vec.NormSafe();
	vec.Scale( this->mMaxLinearAcceleration);
}

void MOAISteerLimiter::FitMaxAngularAcceleration ( float& acc ) {
	if( acc > 0 ) {
		acc = this->mMaxAngularAcceleration;
	} else if( acc < 0 ) {
		acc = - this->mMaxAngularAcceleration;
	}
}

//----------------------------------------------------------------//
void MOAISteerLimiter::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
}

void MOAISteerLimiter::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ "setMaxLinearSpeed",         _setMaxLinearSpeed         },
		{ "setMaxAngularSpeed",        _setMaxAngularSpeed        },
		{ "setMaxAngularAcceleration", _setMaxAngularAcceleration },
		{ "setMaxLinearAcceleration",  _setMaxLinearAcceleration  },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
