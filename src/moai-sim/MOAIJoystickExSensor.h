// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIJOYSITCKEXSENSOR_H
#define MOAIJOYSITCKEXSENSOR_H

#include <moai-sim/MOAISensor.h>

#define MOAI_JOYSTICK_BUTTON_TOTAL 16
#define MOAI_JOYSTICK_AXIS_TOTAL 16

//================================================================//
// MOAIJoystickExSensor
//================================================================//
/**	@lua	MOAIJoystickExSensor
	@text	Hardware buttonboard sensor.


*/
class MOAIJoystickExSensor :
	public MOAISensor {
private:

	enum {
		IS_DOWN		= 1 << 0x00,	// The button is currently pressed
		DOWN		= 1 << 0x01,	// The button was pressed during the last iteration
		UP			= 1 << 0x02,	// The button was released during the last iteration
	};

	u32 mState [ MOAI_JOYSTICK_BUTTON_TOTAL ];

	u32 mClearCount;
	u32 mClearQueue [ MOAI_JOYSTICK_BUTTON_TOTAL ];	// The buttons whose DOWN or UP flags are set

	float mAxis [ MOAI_JOYSTICK_AXIS_TOTAL ];

	MOAILuaStrongRef		mOnButton;
	MOAILuaStrongRef		mOnAxis;
	STLString				mName;

	//----------------------------------------------------------------//
	static int		_buttonDown				( lua_State* L );
	static int		_buttonIsDown				( lua_State* L );
	static int		_buttonIsUp				( lua_State* L );
	static int		_buttonUp					( lua_State* L );
	static int		_setButtonCallback		( lua_State* L );
	static int		_setAxisCallback			( lua_State* L );
	static int		_getName			( lua_State* L );

public:

	DECL_LUA_FACTORY ( MOAIJoystickExSensor )

	void				SetName					( cc8* name );

	//----------------------------------------------------------------//
	static void			EnqueueJoystickExButtonEvent		( MOAIInputQueue& queue, u8 deviceID, u8 sensorID, u32 buttonID, bool down );
	static void			EnqueueJoystickExAxisEvent		( MOAIInputQueue& queue, u8 deviceID, u8 sensorID, u32 axisID, float value );
	static int			CheckButtons					( lua_State* L, bool ( MOAIJoystickExSensor::*predicate )( u32 buttonCode ));
	bool				ButtonDown						( u32 buttonID );
	bool				ButtonIsDown					( u32 buttonID );
	bool				ButtonIsUp						( u32 buttonID );
	bool				ButtonUp						( u32 buttonID );
						MOAIJoystickExSensor			();
						~MOAIJoystickExSensor			();
	void				ParseEvent					( ZLStream& eventStream );
	void				RegisterLuaClass			( MOAILuaState& state );
	void				RegisterLuaFuncs			( MOAILuaState& state );
	void				Reset						();
};

#endif
