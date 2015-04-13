// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIANIMCURVEEX_H
#define	MOAIANIMCURVEEX_H

#include <moai-sim/pch.h>
#include <moai-sim/MOAIAnimCurve.h>
#include <moai-sim/MOAINode.h>

//================================================================//
// MOAIAnimCurveEX
//================================================================//
/**	@lua	MOAIAnimCurveEX
	@text	Implementation of animation curve for floating point values.
*/

class MOAIAnimCurveEXKeyParam
{
public:
	ZLVec2D  mCP1;
	ZLVec2D  mCP2;

	MOAIAnimCurveEXKeyParam() {
		this->mCP1.Init( 0.0f, 0.0f );
		this->mCP2.Init( 0.0f, 0.0f );
	};

};

//----------------------------------------------------------------//
class MOAIAnimCurveEX :
	public virtual MOAIAnimCurve {
private:

	ZLLeanArray < float > mSamples;
	ZLLeanArray < MOAIAnimCurveEXKeyParam > mKeyParams;
	float mValue;

	//----------------------------------------------------------------//
	static int		_getValueAtTime		( lua_State* L );
	static int		_setKey				( lua_State* L );
	static int		_setKeyParam  ( lua_State* L );
	static int		_getKeyParam  ( lua_State* L );
	static int		_setKeyMode   ( lua_State* L );
	static int		_getKeyMode   ( lua_State* L );

	//----------------------------------------------------------------//
	float			GetCurveDelta		() const;
	float			GetValue			( const MOAIAnimKeySpan& span ) const;

public:
	enum {
		SPAN_MODE_LINEAR,
		SPAN_MODE_CONSTANT,
		SPAN_MODE_BEZIER
	};
	
	DECL_LUA_FACTORY ( MOAIAnimCurveEX )
	
	//----------------------------------------------------------------//
	void			ApplyValueAttrOp	( MOAIAttrOp& attrOp, u32 op );
	void			Draw				( u32 resolution ) const;
	void			GetDelta			( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span0, const MOAIAnimKeySpan& span1 ) const;
	float			GetSample			( u32 id );
	float			GetValue			( float time ) const;
	void			GetValue			( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span ) const;
	void			GetZero				( MOAIAttrOp& attrOp ) const;
	MOAIAnimCurveEXKeyParam* GetKeyParam( u32 id );
					MOAIAnimCurveEX		();
					~MOAIAnimCurveEX		();
	void			OnDepNodeUpdate		();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
	void			ReserveSamples		( u32 total );
	void			SetSample			( u32 id, float value );
};

#endif
