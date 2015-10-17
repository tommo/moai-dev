#ifndef MOAITBNODE_H
#define MOAITBNODE_H

#include <moai-core/headers.h>
#include "tb_node_tree.h"

using namespace tb;
//================================================================//
// MOAITBNode
//================================================================//
// TODO: doxygen
class MOAITBNode :
	public MOAILuaObject{
private:
		//----------------------------------------------------------------//
		static int		_getName			( lua_State* L );
		static int		_getValue			( lua_State* L );
		// static int		_readData			( lua_State* L );

		TBNode* mInternalNode;

public:
	
	GET( TBNode*, Internal, mInternalNode )

	DECL_LUA_FACTORY ( MOAITBNode )

	//----------------------------------------------------------------//
					MOAITBNode			();
					~MOAITBNode			();
	void    RegisterLuaClass ( MOAILuaState& state );
	void    RegisterLuaFuncs ( MOAILuaState& state );
};

#endif
