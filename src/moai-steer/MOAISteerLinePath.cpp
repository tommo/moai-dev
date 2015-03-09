#include "moai-steer/MOAISteerLinePath.h"

#define clamp(a, b, c) min(max((a), (b)), (c))

void MOAISteerLinePathSegment::Init ( ZLVec3D* beginPoint, ZLVec3D* endPoint, float prevLength ) {
	this->mBegin  = beginPoint;
	this->mEnd    = endPoint;
	if( beginPoint && endPoint ) {
		this->mLength = endPoint->Dist( *beginPoint );
		this->mTotalLength = this->mLength + prevLength;
	} else {
		this->mLength = 0.0f;
		this->mTotalLength = 0.0f;
	}
}


//----------------------------------------------------------------//
int MOAISteerLinePath::_setLoop ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLinePath, "UB" )
	self->SetLoop( state.GetValue < bool >( 2, true ) );
	return 0;
}

int MOAISteerLinePath::_reservePoints ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLinePath, "UN" )
	u32 count = state.GetValue < u32 >( 2, 0 );
	self->ReservePoints( count );
	return 0;
}

int MOAISteerLinePath::_setPoint ( lua_State *L ) {
	MOAI_LUA_SETUP( MOAISteerLinePath, "UN" )
	u32 id  = state.GetValue < u32 >( 2, 1 ) - 1;
	ZLVec3D point = state.GetVec3D ( 3, 0.0f );
	self->SetPoint( id, point );
	return 0;
}


//----------------------------------------------------------------//
MOAISteerLinePath::MOAISteerLinePath () :
	mDirty  ( false ),
	mLength ( 0.0f  ),
	mLoop   ( false )
{
	RTTI_BEGIN
		RTTI_EXTEND( MOAISteerPath )
	RTTI_END
}

MOAISteerLinePath::~MOAISteerLinePath () {
}

//----------------------------------------------------------------//
void MOAISteerLinePath::ReservePoints ( u32 count ) {
	this->mPoints.Init( count );
	this->mSegmentLengths.Init( count );
	this->mSegments.Init( count );
}

void MOAISteerLinePath::SetPoint( u32 id, const ZLVec3D& v ) {
	if ( id < this->mPoints.Size() ) {
		this->mPoints[ id ] = v;
	}
	this->mDirty = true;
}

void MOAISteerLinePath::AffirmSegments ( ) {
	if( !this->mDirty ) return;
	
	u32 count = this->mPoints.Size();
	float length = 0.0f;
	if( count > 1 ) {
		for( u32 i = 1; i < count; ++i ) {
			MOAISteerLinePathSegment& seg = this->mSegments[ i - 1 ];
			seg.Init( &this->mPoints[ i - 1 ], &this->mPoints[ i ], length );
			length = seg.mTotalLength;
		}
		
		MOAISteerLinePathSegment& lastSeg = mSegments[ count - 1 ];
		if( this->IsLoop() ) {
			lastSeg.Init( &this->mPoints[ count - 1 ], &this->mPoints[ 0 ], length );
			length = lastSeg.mTotalLength;
		} else {
			lastSeg.Init( 0, 0, 0.0f );
		}
		this->mLength = length;

	} else {
		this->mLength = 0.0f;

	}

	this->mDirty = false;
}

void MOAISteerLinePath::SetLoop ( bool loop ) {
	this->mLoop = loop;
	this->mDirty = true;
}

bool MOAISteerLinePath::IsLoop () {
	return this->mLoop;
}

float MOAISteerLinePath::GetLength () {
	this->AffirmSegments();
	return this->mLength;
}

const ZLVec3D* MOAISteerLinePath::GetStartPoint () {
	if( this->mPoints.Size() > 0 )
		return &this->mPoints[ 0 ];
	else
		return NULL;
}

const ZLVec3D* MOAISteerLinePath::GetEndPoint () {
	if( this->mPoints.Size() > 0 )
		return &this->mPoints[ this->mPoints.Size() - 1 ];
	else
		return NULL;
}

float MOAISteerLinePath::CalculatePointSegmentDistanceSqrd ( ZLVec3D& output, const ZLVec3D& a,  const ZLVec3D& b,  const ZLVec3D& c ) {
	ZLVec3D ab = b - a;
	ZLVec3D ac = c - a;
	float t = ac.Dot( ab ) / ab.LengthSqrd();
	t = clamp( t, 0.0f, 1.0f );

	ZLVec3D ab1( ab );
	ab1.Scale( t );
	output.Init( a + ab1 );

	ZLVec3D distance = output - c;
	return distance.LengthSqrd();
}

ZLVec3D MOAISteerLinePath::FindNearestPoint ( const ZLVec3D& from, float& distance ) {
	this->AffirmSegments();
	// Find the nearest segment
	float minDistanceSqrd = FLT_MAX;
	ZLVec3D nearestPointOnSegment;
	ZLVec3D nearestPoint;
	const MOAISteerLinePathSegment* nearestSeg = NULL;

	u32 count = this->mPoints.Size();
	u32 endIdx = this->IsLoop() ? count : count - 1;
	
	for ( u32 idx = 0; idx < endIdx; ++idx ) {
		const MOAISteerLinePathSegment* seg = &this->mSegments[ idx ];
		float distanceSqrd = this->CalculatePointSegmentDistanceSqrd(
			nearestPointOnSegment,
			*seg->mBegin, *seg->mEnd,
			from
			);

		// first point
		if ( distanceSqrd < minDistanceSqrd ) {
			nearestPoint.Init( nearestPointOnSegment );
			minDistanceSqrd = distanceSqrd;
			nearestSeg = seg;
		}
	}

	// Distance from path start
	distance = nearestSeg->mTotalLength - nearestPoint.Dist( *nearestSeg->mEnd );
	return nearestPoint;
}

ZLVec3D MOAISteerLinePath::FindPointOnPath ( float distance ) {
	this->AffirmSegments();
	if( !this->IsLoop() ) {
		distance = clamp( distance, 0.0f, this->mLength );
	} else {
		if ( distance < 0 ) {		// Backwards
			distance = this->mLength + fmod( distance, this->mLength );
		} else if ( distance > this->mLength ) {			// Forward
			distance = fmod( distance, this->mLength );
		}
	}

	// Walk through lines to see on which line we are
	// TODO: use a Tree to speed up searching?
	u32 count = this->mPoints.Size();
	u32 segIdx = 0;

	for ( u32 idx = 0; idx < count; ++idx ) {
		if( this->mSegments[ idx ].mTotalLength >= distance ) { segIdx = idx; break; }
	}

	const MOAISteerLinePathSegment& seg = this->mSegments[ segIdx ];

	float k = ( seg.mTotalLength - distance ) /	seg.mLength; //TODO: NaN?

	ZLVec3D targetPoint( *seg.mEnd );
	targetPoint.Lerp( *seg.mBegin, k );

	return targetPoint;
}

//----------------------------------------------------------------//
void MOAISteerLinePath::RegisterLuaClass ( MOAILuaState& state ) {
	MOAISteerPath::RegisterLuaClass( state );
}

void MOAISteerLinePath::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAISteerPath::RegisterLuaFuncs( state );

	luaL_Reg regTable [] = {
    { "setLoop",         _setLoop       },
    { "reservePoints",   _reservePoints },
    { "setPoint",        _setPoint      },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
