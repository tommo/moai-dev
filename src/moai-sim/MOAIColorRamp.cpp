#include "pch.h"

#include "moai-sim/MOAIColorRamp.h"

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_reserveColorStops ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UN" )
	u32 count = state.GetValue < u32 >( 2, 0 );
	self->ReserveColorStops( count);
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_setColorStop ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UNNNN" )
	u32   idx = state.GetValue < u32 >  ( 2, 1 ) - 1;

	float pos = state.GetValue < float >( 3, 0.0f );

	float r   = state.GetValue < float >( 4, 0.0f );
	float g   = state.GetValue < float >( 5, 0.0f );
	float b   = state.GetValue < float >( 6, 0.0f );
	float a   = state.GetValue < float >( 7, 1.0f );

	self->SetColorStop( idx, pos, r, g, b, a );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_getColorAtPos ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UN" )
	float pos = state.GetValue < float >( 2, 0.0f );
	ZLColorVec result = self->CaculateColor( pos );
	state.Push( result.mR );
	state.Push( result.mG );
	state.Push( result.mB );
	state.Push( result.mA );
	return 4;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_getCursor ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "U" )
	state.Push( self->GetCursor() );
	return 1;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_setCursor ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UN" )
	float cursor = state.GetValue < float >( 2, 0.0f );
	self->SetCursor( cursor );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_seekCursor ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UN" )

	float delay  = state.GetValue < float >( 3, 0.0f );

	if ( delay > 0.0f ) {
		u32 mode = state.GetValue < u32 >( 7, ZLInterpolate::kSmooth );
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		
		action->ParseForSeek ( state, 2, self, 1, mode,
			MOAIColorRampAttr::Pack ( ATTR_CURSOR ), self->mCursor, 0.0f
		);
		
		action->SetSpan ( delay );
		action->Start ( false );
		action->PushLuaUserdata ( state );

		return 1;
	}
	
	float cursor = state.GetValue < float >( 2, 0.0f );
	self->SetCursor( cursor );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIColorRamp::_createImage ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAIColorRamp, "UN" )
	u32 width  = state.GetValue < u32 >( 2, 256 );
	u32 height = state.GetValue < u32 >( 3, 1 );
	MOAIImage* img = self->CreateImage( width, height );
	if( img ) {
		img->PushLuaUserdata( state );
		return 1;
	}
	return 0;
}


//================================================================//
// MOAIColorRamp
//================================================================//

//----------------------------------------------------------------//
void MOAIColorRamp::OnDepNodeUpdate () {
	if( this->mDirty ) {
		this->mDirty = false;
		ZLColorVec calculated = this->CaculateColor( this->mCursor );
		this->Set( calculated.mR, calculated.mG, calculated.mB, calculated.mA );
	}
	MOAIColor::OnDepNodeUpdate ();
}

//----------------------------------------------------------------//
bool MOAIColorRamp::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {

	if ( MOAIColorRampAttr::Check ( attrID )) {

		switch ( UNPACK_ATTR ( attrID )) {
			case ATTR_CURSOR:
				this->SetCursor(
					ZLFloat::Clamp ( 
						attrOp.Apply ( this->mCursor, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT ),
						0.0f, 1.0f
					)
				);
				return true;
		}
	}

	return MOAIColor::ApplyAttrOp( attrID, attrOp, op );

}

//----------------------------------------------------------------//
void MOAIColorRamp::ReserveColorStops ( u32 count ) {
	this->mColorCurve.ReserveKeys( count );
	this->mDirty = true;
	this->ScheduleUpdate();
}

//----------------------------------------------------------------//
void MOAIColorRamp::SetCursor ( float cursor ) {
	this->mCursor = cursor;
	this->mDirty = true;
	this->ScheduleUpdate();
}

//----------------------------------------------------------------//
void MOAIColorRamp::SetColorStop( u32 idx, float pos, float r, float g, float b, float a ) {
	this->mColorCurve.SetKey( idx, pos, ZLInterpolate::kLinear, 1.0f );
	this->mColorCurve.SetSample( idx, ZLColorVec( r, g, b, a ) );
	this->mDirty = true;
	this->ScheduleUpdate();
}

//----------------------------------------------------------------//
ZLColorVec MOAIColorRamp::CaculateColor( float pos ) {
	return this->mColorCurve.GetValue( pos );
}

//----------------------------------------------------------------//
MOAIImage* MOAIColorRamp::CreateImage ( u32 width, u32 height ) {
	MOAIImage* img = new MOAIImage();
	img->Init( width, height, ZLColor::RGBA_8888, MOAIImage::TRUECOLOR );
	for ( u32 x = 0; x < width; ++x ) {
		float pos = (float)x/(float)width;
		ZLColorVec c = this->CaculateColor( pos );
		printf( "%.1f, %.1f, %.1f, %.1f \n", pos, c.mR, c.mG, c.mB, c.mA );
		img->SetPixel( x, 0, c.PackRGBA() );
	}

	for ( u32 y = 1; y < height; ++y ) {
		img->Blit( *img, 0, 0, 0, y, width, 1 );
	}
	// u32 rowSize = img->GetRowSize();
	// for ( u32 y = 1; y < height; ++y ) {
	// 	 memcpy( img->GetRowAddr( y ), 0, rowSize );
	// }
	return img;
}

//----------------------------------------------------------------//
MOAIColorRamp::MOAIColorRamp () {
	this->mDirty  = true;
	this->mCursor = 0.0f;
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIColor )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIColorRamp::~MOAIColorRamp () {
}

//----------------------------------------------------------------//
void MOAIColorRamp::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIColor::RegisterLuaClass ( state );
	
	state.SetField ( -1, "ATTR_CURSOR", MOAIColorRampAttr::Pack ( ATTR_CURSOR ));

}

void MOAIColorRamp::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIColor::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "reserveColorStops",  _reserveColorStops },
		{ "setColorStop",       _setColorStop      },
		{ "getColorAtPos",      _getColorAtPos     },
		{ "getCursor",          _getCursor         },
		{ "setCursor",          _setCursor         },
		{ "seekCursor",         _seekCursor        },
		{ "createImage",        _createImage       },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
