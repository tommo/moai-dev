// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPATHFINDER_H
#define	MOAIPATHFINDER_H

#include <moaicore/MOAILua.h>
#include <set>
using namespace std;

class MOAIGrid;
class MOAIPathGraph;
class MOAIPathTerrainDeck;

//================================================================//
// MOAIPathWeight
//================================================================//
class MOAIPathWeight {
public:

	float			mDeltaScale;
	float			mPenaltyScale;
};

typedef STLMap < int, float > ScoreMap;
typedef STLMap < int, int > ParentMap;
typedef set < int > NodeSet;

//================================================================//
// MOAIPathFinder
//================================================================//
/**	@name	MOAIPathFinder
	@text	Object for maintaining pathfinding state.
*/
class MOAIPathFinder :
	public virtual MOAILuaObject {
private:

	friend class MOAIPathGraph;

	MOAILuaSharedPtr < MOAIPathTerrainDeck > mTerrainDeck;
	MOAILuaSharedPtr < MOAIPathGraph > mGraph;

	USLeanArray < MOAIPathWeight > mWeights;
	USLeanArray < int >	mPath;

	// TODO: optimize implementation with memory pool of path states
	// and binary heap of open paths

	bool				mStarted;
	int					mCurNode;

	NodeSet				mOpen;
	NodeSet				mClosed;
	
	int					mStartNodeID;
	int					mTargetNodeID;

	ScoreMap			mGScores;
	ScoreMap			mFScores;
	ParentMap			mParentMap;

	u32					mMask;

	u32					mHeuristic;
	u32					mFlags;
	bool				mInvertedGraph;
	USIntRect			mBodyRect;

	float				mGWeight;
	float				mHWeight;

	//----------------------------------------------------------------//
	static int			_findPath					( lua_State* L );
	static int			_getGraph					( lua_State* L );
	static int			_getPathEntry				( lua_State* L );
	static int			_getPathSize				( lua_State* L );
	static int			_init						( lua_State* L );
	static int			_reserveTerrainWeights		( lua_State* L );
	static int			_setFlags					( lua_State* L );
	static int			_setGraph					( lua_State* L );
	static int			_setHeuristic				( lua_State* L );
	static int			_setInvertedGraph			( lua_State* L );
	static int			_setBodyRect				( lua_State* L );
	static int			_setTerrainDeck				( lua_State* L );
	static int			_setTerrainScale			( lua_State* L );
	static int			_setWeight					( lua_State* L );

	//----------------------------------------------------------------//
	void				BuildPath			( int nodeID );
	void				ClearVisitation		();
	void				Reset				();

public:
	
	DECL_LUA_FACTORY ( MOAIPathFinder )
	
	GET ( const USLeanArray < MOAIPathWeight >&, Weights, mWeights );
	GET ( int, TargetNodeID, mTargetNodeID );
	GET ( u32, Mask, mMask );
	GET ( u32, Heuristic, mHeuristic )
	GET ( u32, Flags, mFlags )
	GET ( bool, InvertedGraph, mInvertedGraph )
	GET ( USIntRect, BodyRect, mBodyRect )
	GET ( float, GWeight, mGWeight )
	GET ( float, HWeight, mHWeight )
	
	//----------------------------------------------------------------//
	bool		CheckMask				( u32 terrain, bool invert );
	float		ComputeTerrainCost		( float moveCost, u32 terrain0, u32 terrain1 );
	bool		FindPath				( int iterations );
	bool		IsVisited				( int nodeID );
	bool		InOpenSet				( int nodeID );
	bool		InClosedSet				( int nodeID );
	void		MoveNodeToClosedSet		( int nodeID );
	void		SetPathLengthToNode		( int nodeID, float length );
	float		GetPathLengthToNode		( int nodeID);
				MOAIPathFinder			();
				~MOAIPathFinder			();
	int			GetLowestScoreOpenNode	();
	void		AddNodeToOpenSet		( int nodeID );
	void		SetNodeScore			( int nodeID, float score);
	float		GetNodeScore			( int nodeID );
	void		SetNodeParent			( int childNodeID, int parentNodeID );
	void		RegisterLuaClass		( MOAILuaState& state );
	void		RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
