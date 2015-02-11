// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIParticleTimedEmitter.h>
#include <moai-sim/MOAIParticleSystem.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@lua	setFrequency
	@text	Set timer frequency.
	
	@in		MOAIParticleTimedEmitter self
	@in		number min
	@opt	number max		Default value is min.
	@out	nil
*/
int MOAIParticleTimedEmitter::_setFrequency ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleTimedEmitter, "UN" )

	float min = state.GetValue < float >( 2, 1.0f );
	float max = state.GetValue < float >( 3, min );

	self->SetFrequencyRange ( min, max );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setDuration
	@text	Set timer duration.
	
	@in		MOAIParticleTimedEmitter self
	@in		number duration ( nil or <0 for infinite duration )
	@out	nil
*/
int MOAIParticleTimedEmitter::_setDuration ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleTimedEmitter, "U" )
	float duration = state.GetValue < float >( 2, -1.0f );
	self->SetDuraion ( duration );
	return 0;
}


//================================================================//
// MOAIParticleTimedEmitter
//================================================================//

//----------------------------------------------------------------//
float MOAIParticleTimedEmitter::GetRandomFrequency () {

	return ZLFloat::Rand ( this->mMinFrequency, this->mMaxFrequency );
}

//----------------------------------------------------------------//
MOAIParticleTimedEmitter::MOAIParticleTimedEmitter () :
	mTime ( 0.0f ),
	mEmitTime ( 0.0f ),
	mDuration ( -1.0f ),
	mMinFrequency ( 1.0f ),
	mMaxFrequency ( 1.0f ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIParticleEmitter )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIParticleTimedEmitter::~MOAIParticleTimedEmitter () {
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::OnUpdate ( double step ) {

	this->mTime += step;
	if ( this->mDuration > 0.0f && this->mTime > this->mDuration ) {
		this->Stop();
		return;
	}
	if ( !this->mSystem ) return;
	if ( this->mTime < this->mEmitTime ) return;
	
	u32 emission = this->GetRandomEmission ();
	this->Surge ( emission );
	
	this->mEmitTime = this->mTime + this->GetRandomFrequency ();
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::RegisterLuaClass ( MOAILuaState& state ) {

	this->MOAIParticleEmitter::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	this->MOAIParticleEmitter::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setFrequency",		_setFrequency },
		{ "setDuration",		_setDuration },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::SetFrequencyRange ( float min, float max ) {

	this->mMinFrequency = min;
	this->mMaxFrequency = max;
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::SetDuraion ( float duration ) {

	this->mDuration = duration;
}
