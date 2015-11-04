// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIANIMCURVECOLOR_H
#define MOAIANIMCURVECOLOR_H

#include <moai-sim/MOAIAnimCurveBase.h>
#include <moai-sim/MOAINode.h>

//================================================================//
// MOAIAnimCurveColor
//================================================================//
/** @lua  MOAIAnimCurveColor
  @text Implementation of animation curve for color vector values.
*/
class MOAIAnimCurveColor :
  public virtual MOAIAnimCurveBase {
private:

  ZLLeanArray < ZLColorVec > mSamples;
  ZLColorVec mValue;

  //----------------------------------------------------------------//
  static int    _getValueAtTime   ( lua_State* L );
  static int    _setKey       ( lua_State* L );

  //----------------------------------------------------------------//
  ZLColorVec      GetCurveDelta   () const;
  ZLColorVec      GetValue      ( const MOAIAnimKeySpan& span ) const;

public:
  
  DECL_LUA_FACTORY ( MOAIAnimCurveColor )
  
  //----------------------------------------------------------------//
  void       ApplyValueAttrOp    ( MOAIAttrOp& attrOp, u32 op );
  void       GetDelta            ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span0, const MOAIAnimKeySpan& span1 ) const;
  ZLColorVec GetValue            ( float time ) const;
  void       GetValue            ( MOAIAttrOp& attrOp, const MOAIAnimKeySpan& span ) const;
  void       GetZero             ( MOAIAttrOp& attrOp ) const;
          MOAIAnimCurveColor     ();
          ~MOAIAnimCurveColor    ();
  void       OnDepNodeUpdate     ();
  void       RegisterLuaClass    ( MOAILuaState& state );
  void       RegisterLuaFuncs    ( MOAILuaState& state );
  void       ReserveSamples      ( u32 total );
  void       SetSample           ( u32 id, const ZLColorVec& value );
};

#endif
