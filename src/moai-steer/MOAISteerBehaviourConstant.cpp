#include "moai-steer/MOAISteerBehaviourConstant.h"

int MOAISteerBehaviourConstant::_setLinearAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		ZLVec3D acc = state.GetVec3D( 2, 0.0f );
		self->SetLinearAcceleration( acc );
		self->SetLinearAccelerationEnabled( true );
	} else {
		self->SetLinearAccelerationEnabled( false );
	}
	return 0;
}

int MOAISteerBehaviourConstant::_setLinearVelocity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		ZLVec3D vel = state.GetVec3D( 2, 0.0f );
		self->SetLinearVelocity( vel );
		self->SetLinearVelocityEnabled( true );
	} else {
		self->SetLinearVelocityEnabled( false );
	}
	return 0;
}

int MOAISteerBehaviourConstant::_setLinearSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		float spd = state.GetValue < float >( 2, 0.0f );
		self->SetLinearSpeed( spd );
		self->SetLinearSpeedEnabled( true );
	} else {
		self->SetLinearSpeedEnabled( false );
	}
	return 0;
}

int MOAISteerBehaviourConstant::_setAngularAcceleration ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		float acc = state.GetValue < float >( 2, 0.0f );
		self->SetAngularAcceleration( acc );
		self->SetAngularAccelerationEnabled( true );
	} else {
		self->SetAngularAccelerationEnabled( false );
	}
	return 0;
}

int MOAISteerBehaviourConstant::_setAngularVelocity ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		float vel = state.GetValue < float >( 2, 0.0f );
		self->SetAngularVelocity( vel );
		self->SetAngularVelocityEnabled( true );
	} else {
		self->SetAngularVelocityEnabled( false );
	}
	return 0;
}


int MOAISteerBehaviourConstant::_setAngularSpeed ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerBehaviourConstant, "U" )
	if( state.IsType( 2, LUA_TNUMBER ) ) {
		float spd = state.GetValue < float >( 2, 0.0f );
		self->SetAngularSpeed( spd );
		self->SetAngularSpeedEnabled( true );
	} else {
		self->SetAngularSpeedEnabled( false );
	}
	return 0;
}


//----------------------------------------------------------------//
MOAISteerBehaviourConstant::MOAISteerBehaviourConstant() :
	mFlags( 0 ),
	mLinearVelocity      ( 0.0f, 0.0f, 0.0f ),
	mLinearAcceleration  ( 0.0f, 0.0f, 0.0f ),
	mLinearSpeed         ( 0.0f ),
	mAngularVelocity     ( 0.0f ),
	mAngularAcceleration ( 0.0f ),
	mAngularSpeed        ( 0.0f )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerBehaviour )
	RTTI_END
}

MOAISteerBehaviourConstant::~MOAISteerBehaviourConstant() {
}

//----------------------------------------------------------------//
bool MOAISteerBehaviourConstant::OnCalculate ( MOAISteerAcceleration& acc, double elapsed, double delta ) {

	bool hasAngular = false;
	bool hasLinear  = false;
	if( ( this->mFlags & LINEAR_ACCELERATION ) != 0 ) {
		acc.mLinear = this->mLinearAcceleration;
		hasLinear = true;

	} else if( ( this->mFlags & LINEAR_VELOCITY ) != 0 ) {
		acc.mLinear = this->mLinearVelocity - this->GetOwner()->GetLinearVelocity();
		hasLinear = true;

	} else if( ( this->mFlags & LINEAR_SPEED ) != 0 ) {
		ZLVec3D v = this->GetOwner()->GetLinearVelocity();
		float speed = v.Length();
		if( speed != 0.0f ) {
			v.SetLength( this->mLinearSpeed - speed );
		}
		acc.mLinear = v;
		hasLinear = true;

	}

	if( ( this->mFlags & ANGULAR_ACCELERATION ) != 0 ) {
		acc.mAngular = this->mAngularAcceleration;
		hasAngular = true;

	} else if( ( this->mFlags & ANGULAR_VELOCITY ) != 0 ) {
		acc.mAngular = this->mAngularVelocity - this->GetOwner()->GetAngularVelocity();
		hasAngular = true;
				
	} else if( ( this->mFlags & ANGULAR_SPEED ) != 0 ) {
		float av = this->GetOwner()->GetAngularVelocity();
		if( av >= 0 ) {
			acc.mAngular = this->mAngularSpeed - av;
		} else {
			acc.mAngular = - this->mAngularSpeed - av;
		}
		hasAngular = true;
	}
	if( hasLinear ) this->GetActualLimiter()->LimitLinearAcceleration( acc.mLinear );
	if( hasAngular ) this->GetActualLimiter()->LimitAngularAcceleration( acc.mAngular );
	
	return true;
}

//----------------------------------------------------------------//
void MOAISteerBehaviourConstant::SetAngularAccelerationEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= ANGULAR_ACCELERATION;
	} else {
		this->mFlags &= ~ANGULAR_ACCELERATION;
	}
}

void MOAISteerBehaviourConstant::SetLinearAccelerationEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= LINEAR_ACCELERATION;
	} else {
		this->mFlags &= ~LINEAR_ACCELERATION;
	}
}

void MOAISteerBehaviourConstant::SetAngularVelocityEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= ANGULAR_VELOCITY;
	} else {
		this->mFlags &= ~ANGULAR_VELOCITY;
	}
}

void MOAISteerBehaviourConstant::SetLinearVelocityEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= LINEAR_VELOCITY;
	} else {
		this->mFlags &= ~LINEAR_VELOCITY;
	}
}

void MOAISteerBehaviourConstant::SetAngularSpeedEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= ANGULAR_SPEED;
	} else {
		this->mFlags &= ~ANGULAR_SPEED;
	}
}

void MOAISteerBehaviourConstant::SetLinearSpeedEnabled ( bool enabled ) {
	if( enabled ) {
		this->mFlags |= LINEAR_SPEED;
	} else {
		this->mFlags &= ~LINEAR_SPEED;
	}
}


//----------------------------------------------------------------//
void MOAISteerBehaviourConstant::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaClass( state );
}

void MOAISteerBehaviourConstant::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerBehaviour::RegisterLuaFuncs( state );
	luaL_Reg regTable [] = {
		{ "setLinearAcceleration",  _setLinearAcceleration  },
		{ "setAngularAcceleration", _setAngularAcceleration },
		{ "setLinearVelocity",      _setLinearVelocity      },
		{ "setAngularVelocity",     _setAngularVelocity     },
		{ "setLinearSpeed",         _setLinearSpeed         },
		{ "setAngularSpeed",        _setAngularSpeed        },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
