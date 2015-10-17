#include "MOAITBNode.h"

//----------------------------------------------------------------//
// TODO: doxygen
int MOAITBNode::_getName ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBNode, "U" )
	state.Push( self->mInternalNode->GetName() );
	return 1;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAITBNode::_getValue ( lua_State* L ) {
	MOAI_LUA_SETUP( MOAITBNode, "US" )
	// cc8* request = lua_tostring( state, 2 );
	// TBValue& value = state->GetValue();
	// switch( value.GetType() ) {

	// }
	//TODO
	return 0;
}

// //----------------------------------------------------------------//
// // TODO: doxygen
// int MOAITBNode::_readData ( lua_State* L ) {
// 	MOAI_LUA_SETUP( MOAITBNode, "US" )
// 	cc8* input = lua_tostring( state, 2 );
// 	bool additive = state.GetValue< bool >( 3, false );
// 	self->mInternalNode->ReadData(
// 		input,
// 		additive? TB_NODE_READ_FLAGS_APPEND : TB_NODE_READ_FLAGS_NONE
// 	);
// 	return 1;
// }


//================================================================//
// MOAITBNode
//================================================================//

//----------------------------------------------------------------//
MOAITBNode::MOAITBNode () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
	this->mInternalNode = new TBNode();
}

//----------------------------------------------------------------//
MOAITBNode::~MOAITBNode () {
	delete this->mInternalNode;
}

//----------------------------------------------------------------//
void MOAITBNode::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED( state );
}

void MOAITBNode::RegisterLuaFuncs ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{ "getName",			_getName  },
		{ "getValue",			_getValue },
		// { "readData",			_readData },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
