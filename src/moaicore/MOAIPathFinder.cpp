// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAIGridPathGraph.h>
#include <moaicore/MOAIPathFinder.h>
#include <moaicore/MOAIPathGraph.h>
#include <moaicore/MOAIPathTerrainDeck.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	findPath
	@text	Attempts to find an efficient path from the start node
			to the finish node. May be called incrementally.

	@in		MOAIPathFinder self
	@opt	number iterations
	@out	boolean more
*/
int MOAIPathFinder::_findPath ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )
	
	int iterations = state.GetValue < int >( 2, -1 );
	
	state.Push ( self->FindPath ( iterations ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getGraph
	@text	Returns the attached graph (if any).

	@in		MOAIPathFinder self
	@out	MOAIPathGraph graph
*/
int MOAIPathFinder::_getGraph ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )
	
	if ( self->mGraph ) {
		state.Push (( MOAIPathGraph * )self->mGraph );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getPathEntry
	@text	Returns a path entry. This is a node ID that may be
			passed back to the graph to get a location.

	@in		MOAIPathFinder self
	@in		number index
	@out	number entry
*/
int MOAIPathFinder::_getPathEntry ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "UN" )
	
	u32 index = state.GetValue < u32 >( 2, 1 ) - 1;
	
	if ( index < self->mPath.Size ()) {
	
		state.Push ( self->mPath [ index ] + 1 );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getPathSize
	@text	Returns the size of the path (in nodes).

	@in		MOAIPathFinder self
	@out	number size
*/
int MOAIPathFinder::_getPathSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )
	
	state.Push ( self->mPath.Size ());
	return 1;
}

//----------------------------------------------------------------//
/**	@name	init
	@text	Specify the ID of the start and target node.

	@in		MOAIPathFinder self
	@in		number startNodeID
	@in		number targetNodeID
	@out	nil
*/
int MOAIPathFinder::_init ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "UNN" )
	
	self->mStartNodeID = state.GetValue < int >( 2, 1 ) - 1;
	self->mTargetNodeID = state.GetValue < int >( 3, 1 ) - 1;
	
	self->Reset ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reserveTerrainWeights
	@text	Specify the size of the terrain weight vector. 

	@in		MOAIPathFinder self
	@opt	number size				Default value is 0.
	@out	nil
*/
int MOAIPathFinder::_reserveTerrainWeights ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "UN" )
	
	u32 size = state.GetValue < u32 >( 2, 0 );
	
	self->mWeights.Init ( size );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFlags
	@text	Set flags to use for pathfinding. These are graph specific
			flags provided by the graph implementation.

	@in		MOAIPathFinder self
	@opt	number heuristic
	@out	nil
*/
int MOAIPathFinder::_setFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )

	self->mFlags = state.GetValue < u32 >( 2, 0 );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setGraph
	@text	Set graph data to use for pathfinding. 

	@overload

		@in		MOAIPathFinder self
		@opt	MOAIGrid grid						Default value is nil.
		@out	nil
	
	@overload
	
		@in		MOAIPathFinder self
		@opt	MOAIGridPathGraph gridPathGraph		Default value is nil.
		@out	nil
*/
int MOAIPathFinder::_setGraph ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )

	self->mGraph.Set ( *self, 0 );

	MOAIGrid* grid = state.GetLuaObject < MOAIGrid >( 2, false );
	if ( grid ) {
		MOAIGridPathGraph* gridPathGraph = new MOAIGridPathGraph ();
		gridPathGraph->SetGrid ( grid );
		self->mGraph.Set ( *self, gridPathGraph );
		return 0;
	}
	
	MOAIGridPathGraph* gridPathGraph = state.GetLuaObject < MOAIGridPathGraph >( 2, false );
	if ( gridPathGraph ) {
		self->mGraph.Set ( *self, gridPathGraph );
		return 0;
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setHeuristic
	@text	Set heuristic to use for pathfinding. This is a const provided
			by the graph implementation being used.

	@in		MOAIPathFinder self
	@opt	number heuristic
	@out	nil
*/
int MOAIPathFinder::_setHeuristic ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )

	self->mHeuristic = state.GetValue < u32 >( 2, 0 );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setInvertedGraph
	@text	Passing true as an argument will invert the interpretation of
			grid cells when building the path

	@in		MOAIPathFinder self
	@opt	bool invert
	@out	nil
*/
int MOAIPathFinder::_setInvertedGraph ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )

	self->mInvertedGraph = state.GetValue < bool >( 2, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setBodyRect
	@text	Sets the rect to use when pathfinding

	@in		MOAIPathFinder self
	@in		xMin, yMin, xMax, yMax
	@out	nil
*/
int MOAIPathFinder::_setBodyRect ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "UNNNN" )

	self->mBodyRect = state.GetRect < int >(2);
	self->mBodyRect.Bless();

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTerrainDeck
	@text	Set terrain deck to use with graph.

	@in		MOAIPathFinder self
	@opt	MOAIPathTerrainDeck terrainDeck		Default value is nil.
	@out	nil
*/
int MOAIPathFinder::_setTerrainDeck ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )
	
	self->mTerrainDeck.Set ( *self, state.GetLuaObject < MOAIPathTerrainDeck >( 2, true ));
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTerrainScale
	@text	Set a component of the terrain scale vector.

	@in		MOAIPathFinder self
	@in		number index
	@opt	number deltaScale			Default value is 0.
	@opt	number penaltyScale			Default value is 0.
	@out	nil
*/
int MOAIPathFinder::_setTerrainScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "UNNN" )
	
	u32 index = state.GetValue < u32 >( 2, 1 ) - 1;

	if ( index < self->mWeights.Size ()) {
	
		MOAIPathWeight& weight = self->mWeights [ index ];
		weight.mDeltaScale = state.GetValue < float >( 3, 0.0f );
		weight.mPenaltyScale = state.GetValue < float >( 4, 0.0f );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setWeight
	@text	Sets weights to be applied to G and H.

	@in		MOAIPathFinder self
	@opt	number gWeight				Default value is 1.0.
	@opt	number hWeight				Default value is 1.0.
	@out	nil
*/
int MOAIPathFinder::_setWeight ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPathFinder, "U" )
	
	self->mGWeight = state.GetValue < float >( 2, 1.0f );
	self->mHWeight = state.GetValue < float >( 3, 1.0f );
	
	return 0;
}

//================================================================//
// MOAIPathFinder
//================================================================//

//----------------------------------------------------------------//
void MOAIPathFinder::BuildPath ( int nodeID ) {
	u32 size = 1;
	int curNodeID;

	for (  curNodeID = nodeID; curNodeID != this->mStartNodeID; curNodeID = this->mParentMap[curNodeID] , ++size );

	this->mPath.Init ( size );
	for (  curNodeID = nodeID; size > 0; curNodeID = this->mParentMap[curNodeID] ) {
		this->mPath [ --size ] = curNodeID;
	}
	
	this->ClearVisitation ();
}

//----------------------------------------------------------------//
void MOAIPathFinder::ClearVisitation () {
	this->mOpen.clear();
	this->mClosed.clear();
	this->mGScores.clear();
	this->mFScores.clear();
	this->mParentMap.clear();
}

//----------------------------------------------------------------//
void MOAIPathFinder::MoveNodeToClosedSet ( int nodeID ) {
	NodeSet::iterator openIt;

	openIt = mOpen.find( nodeID );

	if(openIt != mOpen.end()) {
		mOpen.erase(openIt);
	}

	mClosed.insert( nodeID );
}


//----------------------------------------------------------------//
bool MOAIPathFinder::CheckMask ( u32 terrain, bool invert) {

	if(!invert || this->mTerrainDeck) {
		if ( !terrain || ( terrain & MOAITileFlags::HIDDEN )) return false;
	} else {
		if(invert && terrain) return false;
	}

	if ( this->mTerrainDeck ) {
		return this->mMask & this->mTerrainDeck->GetMask ( terrain & MOAITileFlags::CODE_MASK ) ? true : false;
	}
	return true;
}

//----------------------------------------------------------------//
float MOAIPathFinder::ComputeTerrainCost ( float moveCost, u32 terrain0, u32 terrain1 ) {

	if ( !this->mTerrainDeck ) return 0.0f;

	if ( terrain0 & MOAITileFlags::HIDDEN ) return 0.0f;
	if ( terrain1 & MOAITileFlags::HIDDEN ) return 0.0f;

	u32 total = MIN ( this->mTerrainDeck->GetVectorSize (), this->mWeights.Size ());
	
	float* v0 = this->mTerrainDeck->GetVector ( terrain0 & MOAITileFlags::CODE_MASK );
	float* v1 = this->mTerrainDeck->GetVector ( terrain1 & MOAITileFlags::CODE_MASK );
	
	float terrainCost = 0.0f;
	for ( u32 i = 0; i < total; ++i ) {
		
		const MOAIPathWeight& weight = this->mWeights [ i ];
		
		float c0 = v0 [ i ];
		float c1 = v1 [ i ];
		
		float delta = ( c1 - c0 ) * weight.mDeltaScale;
		float penalty = ( c1 + c0 ) * 0.5f * weight.mPenaltyScale;
		
		terrainCost += ( moveCost * delta ) + ( moveCost * penalty );
	}
	return terrainCost;
}

//----------------------------------------------------------------//
bool MOAIPathFinder::FindPath ( int iterations ) {
	
	if ( !this->mStarted ) {
		this->SetPathLengthToNode( this->mStartNodeID, 0.0f );
		this->SetNodeScore( this->mStartNodeID, 0.0f );
		this->AddNodeToOpenSet( this->mStartNodeID );
		this->mStarted = true;
	}
	
	bool noIterations = iterations <= 0;
	
	for ( ; this->mOpen.size() && (( iterations > 0 ) || noIterations ); iterations-- ) {
		
		this->mCurNode = this->GetLowestScoreOpenNode();

		this->MoveNodeToClosedSet ( this->mCurNode );
		
		if ( this->mCurNode == this->mTargetNodeID ) {
			this->BuildPath ( this->mCurNode );
			return false;
		}
		this->mGraph->PushNeighbors ( *this, this->mCurNode );
	}
	return this->mOpen.size() ? true : false;
}

//----------------------------------------------------------------//
bool MOAIPathFinder::IsVisited ( int nodeID ) {
	return InOpenSet(nodeID) || InClosedSet(nodeID);
}

//----------------------------------------------------------------//
bool MOAIPathFinder::InOpenSet( int nodeID ) {
	return mOpen.find(nodeID) != mOpen.end();
}

//----------------------------------------------------------------//
bool MOAIPathFinder::InClosedSet( int nodeID ) {
	return mClosed.find(nodeID) != mClosed.end();
}

//----------------------------------------------------------------//
float MOAIPathFinder::GetPathLengthToNode( int nodeID) {
	if(this->mGScores.find(nodeID) == this->mGScores.end()) {
		return FLT_MAX;
	}
	return this->mGScores[nodeID];
}

//----------------------------------------------------------------//
void MOAIPathFinder::SetPathLengthToNode( int nodeID, float length ) {
	this->mGScores[nodeID] = length;
}

//----------------------------------------------------------------//
MOAIPathFinder::MOAIPathFinder () :
	mStartNodeID ( 0 ),
	mTargetNodeID ( 0 ),
	mStarted ( false ),
	mMask ( 0xffffffff ),
	mHeuristic ( 0 ),
	mInvertedGraph( false),
	mFlags ( 0 ),
	mGWeight ( 1.0f ),
	mHWeight ( 1.0f ) {
	
	RTTI_SINGLE ( MOAILuaObject )

	this->mBodyRect.Init ( 0, 0, 0, 0 );
}

//----------------------------------------------------------------//
MOAIPathFinder::~MOAIPathFinder () {

	this->ClearVisitation ();
	
	this->mGraph.Set ( *this, 0 );
	this->mTerrainDeck.Set ( *this, 0 );
}

//----------------------------------------------------------------//
int MOAIPathFinder::GetLowestScoreOpenNode() {
	NodeSet::iterator it, best;

	for(it = mOpen.begin(), best = it; it != mOpen.end(); it++)
	{
		if(this->GetNodeScore(*it) < this->GetNodeScore(*best)) {
			best = it;
		}
	}

	return *best;
}

void MOAIPathFinder::AddNodeToOpenSet( int nodeID )
{
	this->mOpen.insert( nodeID );
}

void MOAIPathFinder::SetNodeScore( int nodeID, float score) {
	this->mFScores[ nodeID ] = score;
}

float MOAIPathFinder::GetNodeScore( int nodeID ) {
	if(this->mFScores.find(nodeID) == this->mFScores.end()) {
			return FLT_MAX;
		}
		return this->mFScores[nodeID];
}

void MOAIPathFinder::SetNodeParent( int childNodeID, int parentNodeID ) {
	this->mParentMap[childNodeID] = parentNodeID;
}

//----------------------------------------------------------------//
void MOAIPathFinder::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIPathFinder::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "findPath",					_findPath },
		{ "getGraph",					_getGraph },
		{ "getPathEntry",				_getPathEntry },
		{ "getPathSize",				_getPathSize },
		{ "init",						_init },
		{ "reserveTerrainWeights",		_reserveTerrainWeights },
		{ "setFlags",					_setFlags },
		{ "setGraph",					_setGraph },
		{ "setHeuristic",				_setHeuristic },
		{ "setInvertedGraph",			_setInvertedGraph},
		{ "setBodyRect",				_setBodyRect},
		{ "setTerrainDeck",				_setTerrainDeck },
		{ "setTerrainScale",			_setTerrainScale },
		{ "setWeight",					_setWeight },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIPathFinder::Reset () {

	this->mStarted = false;
	this->mPath.Clear ();

	this->ClearVisitation ();
}
