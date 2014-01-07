// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIEaseType.h>

//================================================================//
// MOAIEaseType
//================================================================//

//----------------------------------------------------------------//
void MOAIEaseType::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "EASE_IN", ( u32 )ZLInterpolate::kEaseIn );
	state.SetField ( -1, "EASE_OUT", ( u32 )ZLInterpolate::kEaseOut );
	state.SetField ( -1, "FLAT", ( u32 )ZLInterpolate::kFlat );
	state.SetField ( -1, "LINEAR", ( u32 )ZLInterpolate::kLinear );
	state.SetField ( -1, "SHARP_EASE_IN", ( u32 )ZLInterpolate::kSharpEaseIn );
	state.SetField ( -1, "SHARP_EASE_OUT", ( u32 )ZLInterpolate::kSharpEaseOut );
	state.SetField ( -1, "SHARP_SMOOTH", ( u32 )ZLInterpolate::kSharpSmooth );
	state.SetField ( -1, "SMOOTH", ( u32 )ZLInterpolate::kSmooth );
	state.SetField ( -1, "SOFT_EASE_IN", ( u32 )ZLInterpolate::kSoftEaseIn );
	state.SetField ( -1, "SOFT_EASE_OUT", ( u32 )ZLInterpolate::kSoftEaseOut );
	state.SetField ( -1, "SOFT_SMOOTH", ( u32 )ZLInterpolate::kSoftSmooth );
	state.SetField ( -1, "BACK_IN", ( u32 )ZLInterpolate::kBackIn );
	state.SetField ( -1, "BACK_OUT", ( u32 )ZLInterpolate::kBackOut );
	state.SetField ( -1, "BACK_SMOOTH", ( u32 )ZLInterpolate::kBackSmooth );
	state.SetField ( -1, "ELASTIC_IN", ( u32 )ZLInterpolate::kElasticIn );
	state.SetField ( -1, "ELASTIC_OUT", ( u32 )ZLInterpolate::kElasticOut );
	state.SetField ( -1, "ELASTIC_SMOOTH", ( u32 )ZLInterpolate::kElasticSmooth );
	state.SetField ( -1, "BOUNCE_IN", ( u32 )ZLInterpolate::kBounceIn );
	state.SetField ( -1, "BOUNCE_OUT", ( u32 )ZLInterpolate::kBounceOut );
	state.SetField ( -1, "BOUNCE_SMOOTH", ( u32 )ZLInterpolate::kBounceSmooth );
	
}
