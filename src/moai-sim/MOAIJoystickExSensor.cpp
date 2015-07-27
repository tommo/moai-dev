// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIJoystickExSensor.h>
#include <moai-sim/MOAIInputQueue.h>
#include <contrib/moai_utf8.h>

namespace JoystickExEventType {
	enum {
		BUTTON,
		AXIS,
		INVALID
	};
}

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	buttonDown
	@text	Checks to see if one or more buttons were pressed during the last iteration.

	@in		MOAIJoystickExSensor self
	@in		... buttons					Buttons to be checked against the input table.
										Each button can be specified using a MOAIJoystickExSensor.* constant or the corresponding string.
										Multiple strings can be combined: 'wasd' is equivalent to 'w', 'a', 's', 'd'.
	@out	boolean... down				For every specified button, indicates whether this button was pressed during the last iteration.
*/
int MOAIJoystickExSensor::_buttonDown ( lua_State* L ) {
	return CheckButtons ( L, &MOAIJoystickExSensor::ButtonDown );
}

//----------------------------------------------------------------//
/**	@lua	buttonIsDown
	@text	Checks to see if one or more buttons are currently pressed.

	@in		MOAIJoystickExSensor self
	@in		... buttons					Buttons to be checked against the input table.
										Each button can be specified using a MOAIJoystickExSensor.* constant or the corresponding string.
										Multiple strings can be combined: 'wasd' is equivalent to 'w', 'a', 's', 'd'.
	@out	boolean... isDown			For every specified button, indicates whether this button is currently pressed.
*/
int MOAIJoystickExSensor::_buttonIsDown ( lua_State* L ) {
	return CheckButtons ( L, &MOAIJoystickExSensor::ButtonIsDown );
}

//----------------------------------------------------------------//
/**	@lua	buttonIsUp
	@text	Checks to see if one or more buttons are currently up.

	@in		MOAIJoystickExSensor self
	@in		... buttons					Buttons to be checked against the input table.
										Each button can be specified using a MOAIJoystickExSensor.* constant or the corresponding string.
										Multiple strings can be combined: 'wasd' is equivalent to 'w', 'a', 's', 'd'.
	@out	boolean... isUp				For every specified button, indicates whether this button is currently up.
*/
int MOAIJoystickExSensor::_buttonIsUp ( lua_State* L ) {
	return CheckButtons ( L, &MOAIJoystickExSensor::ButtonIsUp );
}

//----------------------------------------------------------------//
/**	@lua	buttonUp
	@text	Checks to see if one or more buttons were released during the last iteration.

	@in		MOAIJoystickExSensor self
	@in		... buttons					Buttons to be checked against the input table.
										Each button can be specified using a MOAIJoystickExSensor.* constant or the corresponding string.
										Multiple strings can be combined: 'wasd' is equivalent to 'w', 'a', 's', 'd'.
	@out	boolean... up				For every specified button, indicates whether this button was released during the last iteration.
*/
int MOAIJoystickExSensor::_buttonUp ( lua_State* L ) {
	return CheckButtons ( L, &MOAIJoystickExSensor::ButtonUp );
}


//----------------------------------------------------------------//
/**	@lua	setButtonCallback
	@text	Sets or clears the callback to be issued when a button is pressed or released.

	@in		MOAIJoystickExSensor self
	@opt	function callback			A callback function with the signature "void callback(number buttonCode, bool down)".
										Default value is nil.
	@out	nil
*/
int MOAIJoystickExSensor::_getName ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIJoystickExSensor, "U" )
	
	lua_pushstring( state, self->mName );
	return 1;
}


//----------------------------------------------------------------//
/**	@lua	setButtonCallback
	@text	Sets or clears the callback to be issued when a button is pressed or released.

	@in		MOAIJoystickExSensor self
	@opt	function callback			A callback function with the signature "void callback(number buttonCode, bool down)".
										Default value is nil.
	@out	nil
*/
int MOAIJoystickExSensor::_setButtonCallback ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIJoystickExSensor, "U" )
	
	self->mOnButton.SetRef ( state, 2 );
	
	return 0;
}


//----------------------------------------------------------------//
/**	@lua	setButtonCallback
	@text	Sets or clears the callback to be issued when a button is pressed or released.

	@in		MOAIJoystickExSensor self
	@opt	function callback			A callback function with the signature "void callback(number buttonCode, bool down)".
										Default value is nil.
	@out	nil
*/
int MOAIJoystickExSensor::_setAxisCallback ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIJoystickExSensor, "U" )
	
	self->mOnAxis.SetRef ( state, 2 );
	
	return 0;
}
//================================================================//
// MOAIJoystickExSensor
//================================================================//

//----------------------------------------------------------------//
void MOAIJoystickExSensor::EnqueueJoystickExButtonEvent ( MOAIInputQueue& queue, u8 deviceID, u8 sensorID, u32 buttonID, bool down ) {

	if ( buttonID >= MOAI_JOYSTICK_BUTTON_TOTAL ) return;

	if ( queue.WriteEventHeader < MOAIJoystickExSensor >( deviceID, sensorID )) {
		queue.Write < u32 >( JoystickExEventType::BUTTON );
		queue.Write < u32 >( buttonID );
		queue.Write < bool >( down );
	}
}


//----------------------------------------------------------------//
void MOAIJoystickExSensor::EnqueueJoystickExAxisEvent ( MOAIInputQueue& queue, u8 deviceID, u8 sensorID, u32 axisID, float value ) {

	if ( axisID >= MOAI_JOYSTICK_AXIS_TOTAL ) return;

	if ( queue.WriteEventHeader < MOAIJoystickExSensor >( deviceID, sensorID )) {
		queue.Write < u32 >( JoystickExEventType::AXIS );
		queue.Write < u32 >( axisID );
		queue.Write < float >( value );
	}
}


//----------------------------------------------------------------//
// For each button, returns whether the specified predicate returns true.
// Expects self and a number of buttoncodes or strings on the stack.
int MOAIJoystickExSensor::CheckButtons ( lua_State* L, bool ( MOAIJoystickExSensor::* predicate )( u32 buttonCode )) {
	MOAI_LUA_SETUP ( MOAIJoystickExSensor, "U" )

	u32 argCount = lua_gettop ( state );
	int resultCount = 0;

	for ( u32 arg = 2; arg <= argCount; ++arg ) {
		if ( state.IsType ( arg, LUA_TNUMBER )) {
			// Argument is number. Treat as single button code.
			u32 buttonCode = state.GetValue < u32 > ( arg, 0 );
			bool result = ( self->*predicate )( buttonCode );
			lua_pushboolean ( state, result );
			++resultCount;
		}
		else if ( state.IsType ( arg, LUA_TSTRING ) ) {
			// Argument is string. Treat as list of button codes.
			cc8* str = lua_tostring ( state, arg );
			for ( u32 i = 0; str [ i ]; ++i ) {
				u32 buttonCode = str [ i ];
				bool result = ( self->*predicate )( buttonCode );
				lua_pushboolean ( state, result );
				++resultCount;
			}
		}
		else {
			// Argument is invalid. Push nil to return the expected number of results
			lua_pushnil ( state );
			++resultCount;
		}
	}

	return resultCount;
}

//----------------------------------------------------------------//
bool MOAIJoystickExSensor::ButtonDown ( u32 buttonID ) {

	return (( this->mState [ buttonID ] & DOWN ) == DOWN );
}

//----------------------------------------------------------------//
bool MOAIJoystickExSensor::ButtonIsDown ( u32 buttonID ) {

	return (( this->mState [ buttonID ] & IS_DOWN ) == IS_DOWN );
}

//----------------------------------------------------------------//
bool MOAIJoystickExSensor::ButtonIsUp ( u32 buttonID ) {

	return (( this->mState [ buttonID ] & IS_DOWN ) == 0 );
}

//----------------------------------------------------------------//
bool MOAIJoystickExSensor::ButtonUp ( u32 buttonID ) {

	return (( this->mState [ buttonID ] & UP ) == UP );
}

//----------------------------------------------------------------//
MOAIJoystickExSensor::MOAIJoystickExSensor () :
	mClearCount ( 0 ) {
	
	RTTI_SINGLE ( MOAISensor )
	
	memset ( this->mState, 0, MOAI_JOYSTICK_BUTTON_TOTAL * sizeof ( u32 ));
	memset ( this->mAxis, 0, MOAI_JOYSTICK_AXIS_TOTAL * sizeof ( float ));
	this->mName = "Joystick";
}

//----------------------------------------------------------------//
MOAIJoystickExSensor::~MOAIJoystickExSensor () {
}

//----------------------------------------------------------------//
void MOAIJoystickExSensor::ParseEvent ( ZLStream& eventStream ) {
	
	u32 eventType = eventStream.Read < u32 >( JoystickExEventType::INVALID );
	if ( eventType == JoystickExEventType::BUTTON ) {

		u32 buttonCode = eventStream.Read < u32 >( 0 );
		bool down = eventStream.Read < bool >( false );
	
		// Ignore redundant events
		if ( down == ButtonIsDown ( buttonCode )) return;

		bool alreadyInClearQueue = ( this->mState [ buttonCode ] & ( DOWN | UP )) != 0;
	
		if ( down ) {
			this->mState [ buttonCode ] |= IS_DOWN | DOWN;
		}
		else {
			this->mState [ buttonCode ] &= ~IS_DOWN;
			this->mState [ buttonCode ] |= UP;
		}
	
		if ( this->mOnButton ) {
			MOAIScopedLuaState state = this->mOnButton.GetSelf ();
			lua_pushnumber ( state, buttonCode );
			lua_pushboolean ( state, down );
			state.DebugCall ( 2, 0 );
		}
	
		if ( !alreadyInClearQueue ) {
			this->mClearQueue [ this->mClearCount ] = buttonCode;
			this->mClearCount++;
		}
	} else if ( eventType == JoystickExEventType::AXIS ) {

		u32 axisId = eventStream.Read < u32 >( 0 );
		float value = eventStream.Read < float >( 0.0f );
		this->mAxis [ axisId ] = value;

		if ( this->mOnAxis ) {
			MOAIScopedLuaState state = this->mOnAxis.GetSelf ();
			lua_pushnumber ( state, axisId );
			lua_pushnumber ( state, value );
			state.DebugCall ( 2, 0 );
		}

	}
}

//----------------------------------------------------------------//
void MOAIJoystickExSensor::RegisterLuaClass ( MOAILuaState& state ) {

	MOAISensor::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIJoystickExSensor::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAISensor::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "buttonDown",				_buttonDown },
		{ "buttonIsDown",				_buttonIsDown },
		{ "buttonIsUp",				_buttonIsUp },
		{ "buttonUp",					_buttonUp },
		{ "getName",					_getName },
		{ "setButtonCallback",			_setButtonCallback },
		{ "setAxisCallback",			_setAxisCallback },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIJoystickExSensor::Reset () {
	// Clear the DOWN and UP flags
	for ( u32 i = 0; i < this->mClearCount; ++i ) {
		u32 buttonCode = this->mClearQueue [ i ];
		this->mState [ buttonCode ] &= ~( DOWN | UP );	
	}
	this->mClearCount = 0;
}


void MOAIJoystickExSensor::SetName ( cc8* name ) {
	this->mName = name;
}
