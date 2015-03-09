#ifndef MOAISTEELINEPATH_H
#define MOAISTEELINEPATH_H

#include "moai-steer/headers.h"
#include "moai-steer/MOAISteerPath.h"

class MOAISteerLinePathSegment
{
public:
	ZLVec3D* mBegin;
	ZLVec3D* mEnd;
	float mTotalLength;
	float mLength;

	void Init( ZLVec3D* beginPoint, ZLVec3D* endPoint, float prevLength );
};

class MOAISteerLinePath:
	public MOAISteerPath
{
private:
	static int _setLoop          ( lua_State* L );
	static int _reservePoints    ( lua_State* L );
	static int _setPoint         ( lua_State* L );

	//----------------------------------------------------------------//	
	bool mDirty;
	ZLLeanArray < ZLVec3D > mPoints;
	ZLLeanArray < float >   mSegmentLengths;
	ZLLeanArray < MOAISteerLinePathSegment >   mSegments;

	void AffirmSegments();

	float mLength;
	bool  mLoop;

	float CalculatePointSegmentDistanceSqrd ( ZLVec3D& output, const ZLVec3D& a,  const ZLVec3D& b,  const ZLVec3D& c) ;

public:

	void SetLoop ( bool loop );
	virtual bool      IsLoop ();
	virtual float     GetLength ();
	virtual ZLVec3D   FindNearestPoint  ( const ZLVec3D& from, float& distance );
	virtual ZLVec3D   FindPointOnPath   ( float distance );

	const ZLVec3D*   GetStartPoint ();
	const ZLVec3D*   GetEndPoint ()  ;


	void ReservePoints ( u32 count );
	void SetPoint      ( u32 id, const ZLVec3D& v );

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerLinePath )

	MOAISteerLinePath();
	~MOAISteerLinePath();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};




#endif