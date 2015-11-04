// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIAnimCurveColor.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/** @lua    getValueAtTime
    @text   Return the interpolated vector components given a point in
            time along the curve. This does not change the curve's built in TIME
            attribute (it simply performs the requisite computation on demand).
    
    @in     MOAIAnimCurveColor self
    @in     number time
    @out    number r
    @out    number g
    @out    number b
    @out    number a
*/
int MOAIAnimCurveColor::_getValueAtTime ( lua_State* L ) {
    MOAI_LUA_SETUP ( MOAIAnimCurveColor, "UN" );

    float time = state.GetValue < float >( 2, 0 );
    ZLColorVec value = self->GetValue ( time );
    state.Push ( value.mR );
    state.Push ( value.mG );
    state.Push ( value.mB );
    state.Push ( value.mA );
    return 4;
}

//----------------------------------------------------------------//
/** @lua    setKey
    @text   Initialize a key frame at a given time with a give vector.
            Also set the transition type between the specified key frame
            and the next key frame.
    
    @in     MOAIAnimCurveColor self
    @in     number index            Index of the keyframe.
    @in     number time             Location of the key frame along the curve.
    @in     number r                R component at time.
    @in     number g                G component at time.
    @in     number b                B component at time.
    @in     number a                A component at time.
    @opt    number mode             The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
                                    MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH. Defaults to MOAIEaseType.SMOOTH.
    @opt    number weight           Blends between chosen ease type (of any) and a linear transition. Defaults to 1.
    @out    nil
*/
int MOAIAnimCurveColor::_setKey ( lua_State* L ) {
    MOAI_LUA_SETUP ( MOAIAnimCurveColor, "UNNNNN" );

    u32 index         = state.GetValue < u32 >( 2, 1 ) - 1;
    float time        = state.GetValue < float >( 3, 0.0f );
    ZLColorVec value  = state.GetColor ( 4, 0.0f, 0.0f, 0.0f, 1.0f );
    u32 mode          = state.GetValue < u32 >( 8, ZLInterpolate::kSmooth );
    float weight      = state.GetValue < float >( 9, 1.0f );
    
    if ( MOAILogMessages::CheckIndexPlusOne ( index, self->mKeys.Size (), L )) {
        
        self->SetKey ( index, time, mode, weight );
        self->SetSample ( index, value );
    }
    return 0;
}

//================================================================//
// MOAIAnimCurveColor
//================================================================//

//----------------------------------------------------------------//
void MOAIAnimCurveColor::ApplyValueAttrOp ( MOAIAttrOp& attrOp, u32 op ) {

    this->mValue = attrOp.Apply < ZLColorVec >( this->mValue, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_COLOR );
}

//----------------------------------------------------------------//
ZLColorVec MOAIAnimCurveColor::GetCurveDelta () const {

    ZLColorVec delta;

    u32 size = this->mKeys.Size ();
    if ( size > 1 ) {
        delta = this->mSamples [ size - 1 ];
        delta.Sub ( this->mSamples [ 0 ]);
    }
    else {
        delta.Set ( 0.0f, 0.0f, 0.0f, 0.0f );
    }
    return delta;
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::GetDelta ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span0, const MOAIAnimKeySpan& span1 ) const {

    ZLColorVec v0 = this->GetValue ( span0 );
    ZLColorVec v1 = this->GetValue ( span1 );
    
    v1.Sub ( v0 );
    
    attrOp.SetValue < ZLColorVec >( v1, MOAIAttrOp::ATTR_TYPE_COLOR );
}

//----------------------------------------------------------------//
ZLColorVec MOAIAnimCurveColor::GetValue ( float time ) const {

    MOAIAnimKeySpan span = this->GetSpan ( time );
    return this->GetValue ( span );
}

//----------------------------------------------------------------//
ZLColorVec MOAIAnimCurveColor::GetValue ( const MOAIAnimKeySpan& span ) const {

    MOAIAnimKey& key = this->mKeys [ span.mKeyID ];
    ZLColorVec v0 = this->mSamples [ span.mKeyID ];
    
    if ( span.mTime > 0.0f ) {
    
        ZLColorVec v1 = this->mSamples [ span.mKeyID + 1 ];
    
        v0.mR = ZLInterpolate::Interpolate ( key.mMode, v0.mR, v1.mR, span.mTime, key.mWeight );
        v0.mG = ZLInterpolate::Interpolate ( key.mMode, v0.mG, v1.mG, span.mTime, key.mWeight );
        v0.mB = ZLInterpolate::Interpolate ( key.mMode, v0.mB, v1.mB, span.mTime, key.mWeight );
        v0.mA = ZLInterpolate::Interpolate ( key.mMode, v0.mA, v1.mA, span.mTime, key.mWeight );
    }
    
    if ( span.mCycle != 0.0f ) {
        ZLColorVec curveDelta = this->GetCurveDelta ();
        curveDelta.Scale ( span.mCycle );
        v0.Add ( curveDelta );
    }
    return v0;
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::GetValue ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span ) const {

    attrOp.SetValue < ZLColorVec >( this->GetValue ( span ), MOAIAttrOp::ATTR_TYPE_COLOR );
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::GetZero ( MOAIAttrOp& attrOp ) const {

    ZLColorVec zero ( 0.0f, 0.0f, 0.0f, 0.0f );
    attrOp.SetValue < ZLColorVec >( zero, MOAIAttrOp::ATTR_TYPE_COLOR );
}

//----------------------------------------------------------------//
MOAIAnimCurveColor::MOAIAnimCurveColor () :
    mValue ( 0.0f, 0.0f, 0.0f, 0.0f ) {
    
    RTTI_SINGLE ( MOAIAnimCurveBase )
}

//----------------------------------------------------------------//
MOAIAnimCurveColor::~MOAIAnimCurveColor () {
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::OnDepNodeUpdate () {

    this->mValue = this->GetValue ( this->mTime );
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::RegisterLuaClass ( MOAILuaState& state ) {

    MOAIAnimCurveBase::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::RegisterLuaFuncs ( MOAILuaState& state ) {

    MOAIAnimCurveBase::RegisterLuaFuncs ( state );

    luaL_Reg regTable [] = {
        { "getValueAtTime",     _getValueAtTime },
        { "setKey",             _setKey },
        { NULL, NULL }
    };

    luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::ReserveSamples ( u32 total ) {

    this->mSamples.Init ( total );
}

//----------------------------------------------------------------//
void MOAIAnimCurveColor::SetSample ( u32 id, const ZLColorVec& value ) {

    if ( id < this->mKeys.Size ()) {
        this->mSamples [ id ] = value;
    }
}
