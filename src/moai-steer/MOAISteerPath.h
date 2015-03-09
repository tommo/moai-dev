#ifndef MOAISTEEPATH_H
#define MOAISTEEPATH_H

#include "moai-sim/headers.h"

class MOAISteerPath:
	public MOAILuaObject
{
private:
	static int _isLoop              ( lua_State* L );
	static int _getLength           ( lua_State* L );
	static int _findNearestPoint    ( lua_State* L );
	static int _findPointOnPath     ( lua_State* L );

public:
	virtual bool      IsLoop () { return false; };
	virtual float     GetLength () { return 0.0f; };
	virtual ZLVec3D   FindNearestPoint ( const ZLVec3D& from, float& distance ) { return ZLVec3D(); };
	virtual ZLVec3D   FindPointOnPath  ( float distance ) { return ZLVec3D(); };

	virtual const ZLVec3D*   GetStartPoint () { return NULL; };
	virtual const ZLVec3D*   GetEndPoint ()   { return NULL; };

	//----------------------------------------------------------------//
	DECL_LUA_FACTORY ( MOAISteerPath )

	MOAISteerPath();
	~MOAISteerPath();

	void  RegisterLuaClass ( MOAILuaState& state );
	void  RegisterLuaFuncs ( MOAILuaState& state );
};




#endif