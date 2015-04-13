// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-sim/MOAIAnimCurveEX.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <float.h>

float EvaluateCubicCurve2D( float x0, float y0,	float x1, float y1,	float x2, float y2,	float x3, float y3,	float x );
float SolveCubic           (float a, float b, float c, float d );
float SolveQuadratic       (float a, float b, float c);

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@lua	getValueAtTime
	@text	Return the interpolated value given a point in time along the curve. This does not change
					the curve's built in TIME attribute (it simply performs the requisite computation on demand).
	
	@in		MOAIAnimCurveEX self
	@in		number time
	@out	number value	The interpolated value
*/
int MOAIAnimCurveEX::_getValueAtTime ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UN" );

	float time = state.GetValue < float >( 2, 0 );
	float value = self->GetValue ( time );
	state.Push ( value );
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	setKey
	@text	Initialize a key frame at a given time with a give value. Also set the transition type between
			the specified key frame and the next key frame.
	
	@in		MOAIAnimCurveEX self
	@in		number index			Index of the keyframe.
	@in		number time				Location of the key frame along the curve.
	@in		number value			Value of the curve at time.
	@opt	number mode				The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
									MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH. Defaults to MOAIEaseType.SMOOTH.
	@opt	number weight			Blends between chosen ease type (of any) and a linear transition. Defaults to 1.
	@out	nil
*/
int MOAIAnimCurveEX::_setKey ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UNN" );

	u32 index		  = state.GetValue < u32 >( 2, 1 ) - 1;
	float time		= state.GetValue < float >( 3, 0.0f );
	float value		= state.GetValue < float >( 4, 0.0f );
	u32 mode		  = state.GetValue < u32 >( 5, SPAN_MODE_LINEAR );
	float weight	= state.GetValue < float >( 6, 1.0f );
	
	if ( MOAILogMessages::CheckIndexPlusOne ( index, self->mKeys.Size (), L )) {
	
		self->SetKey ( index, time, mode, weight );
		self->SetSample ( index, value );
	}
	return 0;
}

int MOAIAnimCurveEX::_setKeyMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UNN" );
	u32 index		  = state.GetValue < u32 >( 2, 1 ) - 1;
	u32 mode      = state.GetValue < u32 >( 3, 0 );
	if( index < self->Size() ) {
		MOAIAnimKey& key = self->mKeys[ index ];
		key.mMode = mode;
	}
	return 0;
}


int MOAIAnimCurveEX::_getKeyMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UN" );
	u32 index		  = state.GetValue < u32 >( 2, 1 ) - 1;
	if( index < self->Size() ) {
		MOAIAnimKey& key = self->mKeys[ index ];
		state.Push( key.mMode );
		return 1;
	}
	return 0;
}

int MOAIAnimCurveEX::_setKeyParam ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UNNNNN" );

	u32 index		  = state.GetValue < u32 >( 2, 1 ) - 1;
	float x1      = state.GetValue < float >( 3, 0.0f );
	float y1      = state.GetValue < float >( 4, 0.0f );
	float x2      = state.GetValue < float >( 5, 0.0f );
	float y2      = state.GetValue < float >( 6, 0.0f );
	MOAIAnimCurveEXKeyParam* param = self->GetKeyParam( index );
	if( param ) {
		param->mCP1.mX = x1;
		param->mCP1.mY = y1;
		param->mCP2.mX = x2;
		param->mCP2.mY = y2;
	}
	return 0;
}

int MOAIAnimCurveEX::_getKeyParam ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIAnimCurveEX, "UN" );

	u32 index		  = state.GetValue < u32 >( 2, 1 ) - 1;
	MOAIAnimCurveEXKeyParam* param = self->GetKeyParam( index );
	if( param ) {
		state.Push( param->mCP1.mX );
		state.Push( param->mCP1.mY );
		state.Push( param->mCP2.mX );
		state.Push( param->mCP2.mY );
		return 5;
	} else {
		return 0;
	}
}

//================================================================//
// MOAIAnimCurveEX
//================================================================//

//----------------------------------------------------------------//
void MOAIAnimCurveEX::ApplyValueAttrOp ( MOAIAttrOp& attrOp, u32 op ) {

	this->mValue = attrOp.Apply ( this->mValue, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::Draw ( u32 resolution ) const {

	// TODO: this isn't entirely correct. the value of each key frame should be drawn
	// and then the spans between keys should be filled in with an approximation of
	// the resolution.
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	float length = this->GetLength ();
	float step = length / ( float )resolution;
	
	gfxDevice.BeginPrim ( ZGL_PRIM_LINE_STRIP );
	
	for ( u32 i = 0; i < resolution; ++i ) {
		
		float t = step * ( float )i;
		float v = this->GetValue ( t );
		
		gfxDevice.WriteVtx ( t, v, 0.0f );
		gfxDevice.WriteFinalColor4b ();
	}
	
	float t = length;
	float v = this->GetValue ( t );
	
	gfxDevice.WriteVtx ( t, v, 0.0f );
	gfxDevice.WriteFinalColor4b ();
	
	gfxDevice.EndPrim ();
}

//----------------------------------------------------------------//
float MOAIAnimCurveEX::GetCurveDelta () const {

	u32 size = this->mKeys.Size ();
	if ( size > 1 ) {
		return this->mSamples [ size - 1 ] - this->mSamples [ 0 ];
	}
	return 0.0f;
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::GetDelta ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span0, const MOAIAnimKeySpan& span1 ) const {

	float v0 = this->GetValue ( span0 );
	float v1 = this->GetValue ( span1 );
	
	attrOp.SetValue < float >( v1 - v0, MOAIAttrOp::ATTR_TYPE_FLOAT );
}

//----------------------------------------------------------------//
float MOAIAnimCurveEX::GetSample ( u32 id ) {

	if ( id < this->mKeys.Size ()) {
		return this->mSamples [ id ];
	}
	return 0.0f;
}

//----------------------------------------------------------------//
MOAIAnimCurveEXKeyParam* MOAIAnimCurveEX::GetKeyParam ( u32 id ) {

	if ( id < this->mKeys.Size ()) {
		return &this->mKeyParams [ id ];
	}
	return NULL;
}

//----------------------------------------------------------------//
float MOAIAnimCurveEX::GetValue ( float time ) const {

	MOAIAnimKeySpan span = this->GetSpan ( time );
	return this->GetValue ( span );
}

//----------------------------------------------------------------//
float MOAIAnimCurveEX::GetValue ( const MOAIAnimKeySpan& span ) const {
	MOAIAnimKey& key = this->mKeys [ span.mKeyID ];
	float v0 = this->mSamples [ span.mKeyID ];
	float v1 = this->mSamples [ span.mKeyID + 1 ];
	if ( span.mTime > 0.0f ) {
		switch( key.mMode ) {
			case SPAN_MODE_LINEAR:
				v0 = ZLInterpolate::Interpolate ( ZLInterpolate::kLinear, v0, v1, span.mTime );
				break;
			case SPAN_MODE_CONSTANT:
				//v0 = v0
				break;
			case SPAN_MODE_BEZIER:
				MOAIAnimCurveEXKeyParam& p0 = this->mKeyParams [ span.mKeyID ];
				MOAIAnimCurveEXKeyParam& p1 = this->mKeyParams [ span.mKeyID + 1 ];
				// v0 = ZLInterpolate::Interpolate ( ZLInterpolate::kSmooth, v0, v1, span.mTime );
				float x0, y0, x1, y1, x2, y2, x3, y3;
				x0 = 0.0f; y0 = v0;
				x1 = x0 + p0.mCP2.mX;
				y1 = y0 + p0.mCP2.mY;
				x3 = 1.0f; y3 = v1;
				x2 = x3 + p1.mCP1.mX;
				y2 = y3 + p1.mCP1.mY;

				v0 = EvaluateCubicCurve2D(
					x0, y0, x1, y1, x2, y2, x3, y3, span.mTime
					);
				break;
		}
	}
	return v0 + ( this->GetCurveDelta () * span.mCycle );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::GetValue ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span ) const {

	attrOp.SetValue < float >( this->GetValue ( span ), MOAIAttrOp::ATTR_TYPE_FLOAT );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::GetZero ( MOAIAttrOp& attrOp ) const {

	attrOp.SetValue < float >( 0.0f, MOAIAttrOp::ATTR_TYPE_FLOAT );
}

//----------------------------------------------------------------//
MOAIAnimCurveEX::MOAIAnimCurveEX () :
	mValue ( 0.0f ) {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIAnimCurve )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIAnimCurveEX::~MOAIAnimCurveEX () {
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::OnDepNodeUpdate () {

	this->mValue = this->GetValue ( this->mTime );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::RegisterLuaClass ( MOAILuaState& state ) {
	state.SetField ( -1, "SPAN_MODE_LINEAR",	  ( u32 )SPAN_MODE_LINEAR   );
	state.SetField ( -1, "SPAN_MODE_CONSTANT",	( u32 )SPAN_MODE_CONSTANT );
	state.SetField ( -1, "SPAN_MODE_BEZIER",	  ( u32 )SPAN_MODE_BEZIER   );
	MOAIAnimCurve::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIAnimCurve::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "setKeyParam",      _setKeyParam    },
		{ "getKeyParam",      _getKeyParam    },
		{ "setKeyMode",       _setKeyMode     },
		{ "getKeyMode",       _getKeyMode     },
		{ "getValueAtTime",   _getValueAtTime },
		{ "setKey",           _setKey         },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::ReserveSamples ( u32 total ) {
	this->mKeyParams.Init ( total );
	this->mSamples.Init ( total );
}

//----------------------------------------------------------------//
void MOAIAnimCurveEX::SetSample ( u32 id, float value ) {

	if ( id < this->mKeys.Size ()) {
		this->mSamples [ id ] = value;
	}
}


//----------------------------------------------------------------//
inline float Squared   ( float x ) { return ( x*x ) ; }
inline float Cubed     ( float x ) { return ( x*x*x ) ; }
inline float CubicRoot ( float x ) { return powf( x, 1.0f/3.0f ) ; }

float EvaluateCubicCurve2D( 
	float x0, float y0,
	float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	float x ) {
	// Determine t
	float t;
	if (x == x0) {
			// Handle corner cases explicitly to prevent rounding errors
			t = 0;
	} else if (x == x3) {
			t = 1;
	} else {
			// Calculate t
			float a = -x0 + 3 * x1 - 3 * x2 + x3;
			float b = 3 * x0 - 6 * x1 + 3 * x2;
			float c = -3 * x0 + 3 * x1;
			float d = x0 - x;
			float tTemp = SolveCubic(a, b, c, d);
			if (tTemp == FLT_MAX) return FLT_MAX;
			t = tTemp;
	}

	// Calculate y from t
	return Cubed(1 - t) * y0
			+ 3 * t * Squared(1 - t) * y1
			+ 3 * Squared(t) * (1 - t) * y2
			+ Cubed(t) * y3;
}
// Solves the equation ax³+bx²+cx+d = 0 for x ϵ ℝ
// and returns the first result in [0, 1] or null.
float SolveCubic(float a, float b, float c, float d ) {
	if (a == 0) return SolveQuadratic(b, c, d);
	if (d == 0) return 0;

	b /= a;
	c /= a;
	d /= a;
	float q = (3.0 * c - Squared(b)) / 9.0;
	float r = (-27.0 * d + b * (9.0 * c - 2.0 * Squared(b))) / 54.0;
	float disc = Cubed(q) + Squared(r);
	float term1 = b / 3.0;

	if (disc > 0) {
			float s = r + Sqrt(disc);
			s = (s < 0) ? -CubicRoot(-s) : CubicRoot(s);
			float t = r - Sqrt(disc);
			t = (t < 0) ? -CubicRoot(-t) : CubicRoot(t);

			float result = -term1 + s + t;
			if (result >= 0 && result <= 1) return result;
	} else if (disc == 0) {
			float r13 = (r < 0) ? -CubicRoot(-r) : CubicRoot(r);

			float result = -term1 + 2.0 * r13;
			if (result >= 0 && result <= 1) return result;

			result = -(r13 + term1);
			if (result >= 0 && result <= 1) return result;
	} else {
			q = -q;
			float dum1 = q * q * q;
			dum1 = ACos(r / Sqrt(dum1));
			float r13 = 2.0 * Sqrt(q);

			float result = -term1 + r13 * Cos(dum1 / 3.0);
			if (result >= 0 && result <= 1) return result;

			result = -term1 + r13 * Cos((dum1 + 2.0 * PI) / 3.0);
			if (result >= 0 && result <= 1) return result;

			result = -term1 + r13 * Cos((dum1 + 4.0 * PI) / 3.0);
			if (result >= 0 && result <= 1) return result;
	}

	return FLT_MAX;
}

// Solves the equation ax² + bx + c = 0 for x ϵ ℝ
// and returns the first result in [0, 1] or null.
float SolveQuadratic(float a, float b, float c) {
	float result = (-b + Sqrt(Squared(b) - 4 * a * c)) / (2 * a);
	if (result >= 0 && result <= 1) return result;

	result = (-b - Sqrt(Squared(b) - 4 * a * c)) / (2 * a);
	if (result >= 0 && result <= 1) return result;

	return FLT_MAX;
}

