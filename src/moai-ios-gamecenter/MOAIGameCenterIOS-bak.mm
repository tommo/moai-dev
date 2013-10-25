// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#import <moai-ios/headers.h>
#import <moai-ios-gamecenter/MOAIGameCenterIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	authenticatePlayer
	@text	Makes sure GameCenter is supported and an account is 
			logged in. If none are logged in, this will prompt the 
			user to log in. This must be called before any other 
			MOAIGameCenterIOS functions.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_authenticatePlayer ( lua_State* L ) {
	
	MOAILuaState state ( L );
		MOAIGameCenterIOS::Get ().mAuthenticationCallback.SetStrongRef ( state, 1 );
	// Check for presence of GKLocalPlayer class.
    BOOL localPlayerClassAvailable = ( NSClassFromString ( @"GKLocalPlayer" )) != nil;
		
	// The device must be running iOS 4.1 or later.
    NSString *reqSysVer = @"4.1";
    NSString *currSysVer = [[ UIDevice currentDevice ] systemVersion ];
    BOOL osVersionSupported = ([ currSysVer compare:reqSysVer options:NSNumericSearch ] != NSOrderedAscending );
    if ( localPlayerClassAvailable && osVersionSupported ) {
		
		// If GameCenter is available, attempt to authenticate the local player
		GKLocalPlayer *localPlayer = [ GKLocalPlayer localPlayer ];
		[ localPlayer authenticateWithCompletionHandler: ^( NSError *error ) {
			
			if ( [ error code ] == GKErrorNotSupported || [ error  code ] == GKErrorGameUnrecognized ) {
				
				MOAIGameCenterIOS::Get ().mIsGameCenterSupported = FALSE;
			}
			else if ([ GKLocalPlayer localPlayer ].isAuthenticated) {
				
				MOAIGameCenterIOS::Get ().mLocalPlayer = localPlayer;
				MOAIGameCenterIOS::Get ().mIsGameCenterSupported = TRUE;	
				MOAIGameCenterIOS::Get ().GetAchievements ();						
			}
			MOAIGameCenterIOS::Get ().CallAuthenticationCallback(error);
		 }];
	}	
	
	return 0;
}

// int MOAIGameCenterIOS::_setAuthenticationCallback ( lua_State *L) {
	
// 	MOAILuaState state (L);
// 	MOAIGameCenterIOS::Get ().mAuthenticationCallback.SetStrongRef ( state, 1 );
// 	return 0;

// }


int MOAIGameCenterIOS::_getAchievements ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}

	MOAILuaState state ( L );

	lua_newtable( state );

	NSMutableDictionary* dict =MOAIGameCenterIOS::Get ().mAchievementsDictionary;
	for(NSString* key in dict) {
		GKAchievement* achievement = [ dict objectForKey:key ]	;
		lua_pushstring(state, [achievement.identifier UTF8String]);
		lua_pushnumber(state, achievement.percentComplete);
		lua_settable(state, -3);
	}
	
	return 1;
}


//----------------------------------------------------------------//
/**	@name	getPlayerAlias
	@text	Returns the user visible player name string from GameCenter.

	@in 	nil
	@out 	string	alias
 */
int MOAIGameCenterIOS::_getPlayerAlias ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* alias = [ MOAIGameCenterIOS::Get ().mLocalPlayer.alias UTF8String ];
	lua_pushstring ( state, alias );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getScores
	@text	Returns the top ten scores of everyone for all-time. 
			Optionally specify a leaderboard, player scope, time scope 
			and range. If no leaderboard was specified, this will 
			return scores from the default leaderboard.
	
	@opt	string		category
	@opt	number		playerScope
	@opt	number		timeScope
	@opt	number		startRange
	@opt	number		endRange
	@out	table		scores
*/
int MOAIGameCenterIOS::_getScores ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}

	MOAILuaState state ( L );
		
	cc8* category = state.GetValue < cc8* >( 1, NULL );
	int playerScope = state.GetValue < int >( 2, PLAYERSCOPE_GLOBAL );
	int timeScope = state.GetValue < int >( 3, TIMESCOPE_ALLTIME );
	int startRange = state.GetValue < int >( 4, 1 );
	int endRange = state.GetValue < int >( 5, 10 );

	GKLeaderboard *leaderboardRequest = [[ GKLeaderboard alloc] init ];
    if ( leaderboardRequest != nil ) {
	
		if ( category ) {
			
			leaderboardRequest.category = [ NSString stringWithUTF8String:category];
		}
		
        leaderboardRequest.playerScope = playerScope;
        leaderboardRequest.timeScope = timeScope;
        leaderboardRequest.range = NSMakeRange ( startRange, endRange );
        [ leaderboardRequest loadScoresWithCompletionHandler: ^( NSArray *scores, NSError *error ) {
		
            if ( error != nil ) {
	
				printf ( "Error in getting leaderboard scores: %d\n", [ error code ]);
            }
            if ( scores != nil ) {
	
				MOAIGameCenterIOS::Get ().CallScoresCallback ( scores );
            }
		}];
    }
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	isSupported
	@text	Returns whether or not GameCenter is supported on the 
			current device.
			
	@in		nil
	@out	bool	isSupported
*/
int MOAIGameCenterIOS::_isSupported ( lua_State* L ) {
	
	MOAILuaState state ( L );

	lua_pushboolean ( state, MOAIGameCenterIOS::Get ().mIsGameCenterSupported );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	reportAchievementProgress
	@text	Reports an achievement progress to GameCenter.
			
	@in		string	identifier
	@in		number	percentComplete
	@out	nil
*/
int MOAIGameCenterIOS::_reportAchievementProgress ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}
	
	MOAILuaState state ( L );

	cc8* identifier = lua_tostring ( state, 1 );
	float percent =  ( float )lua_tonumber ( state, 2 );
		
	MOAIGameCenterIOS::Get ().ReportAchievementProgress ( identifier, percent );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reportScore
	@text	Reports a score to a desired leaderboard on GameCenter.
			
	@in		number	score
	@in		string	category
	@out	nil
*/
int MOAIGameCenterIOS::_reportScore ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}
	
	MOAILuaState state ( L );

	s64 score =  ( s64 )lua_tonumber ( state, 1 );
	cc8* category = lua_tostring ( state, 2 );
		
	MOAIGameCenterIOS::Get ().ReportScore ( score, category );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setGetScoresCallabck
	@text	Sets the function to be called upon a successful '
			getScores () call.
			
	@in		function	getScoresCallback
	@out	nil
*/
int MOAIGameCenterIOS::_setGetScoresCallback ( lua_State* L ) {
	
	MOAILuaState state ( L );

	MOAIGameCenterIOS::Get ().mGetScoresCallback.SetRef ( state, 1 );
		
	return 0;
}

int MOAIGameCenterIOS::_setReportCompletionCallback ( lua_State* L ) {
	
	MOAILuaState state ( L );

	MOAIGameCenterIOS::Get ().mReportCompletionCallback.SetStrongRef ( state, 1 );
		
	return 0;
}

int MOAIGameCenterIOS::_setAchievementReadyCallback ( lua_State* L ) {
	
	MOAILuaState state ( L );

	MOAIGameCenterIOS::Get ().mAchievementReadyCallback.SetStrongRef ( state, 1 );
		
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDefaultAchievments
	@text	Displays the default achievements view.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_showDefaultAchievements ( lua_State* L ) {
	
	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];	
	
	GKAchievementViewController *achievements = [[ GKAchievementViewController alloc ] init ];
    if (achievements != NULL) {
	
        achievements.achievementDelegate = MOAIGameCenterIOS::Get ().mAchievementDelegate;
		if  ( rootVC != nil ) {
			
			[ rootVC presentModalViewController: achievements animated: YES ];
		}
    }

	[ achievements release ];
		
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDefaultLeaderboard
	@text	Displays the default leaderboard view.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_showDefaultLeaderboard ( lua_State* L ) {
	
	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];	
	GKLeaderboardViewController *leaderboardController = [[ GKLeaderboardViewController alloc ] init ];
    if ( leaderboardController != nil ) {	
	
        leaderboardController.leaderboardDelegate = MOAIGameCenterIOS::Get ().mLeaderboardDelegate;
		if ( rootVC != nil ) {
			[ leaderboardController popViewControllerAnimated:NO ];
			[ rootVC presentModalViewController: leaderboardController animated: YES ];
		}
    }

	[ leaderboardController release ];
		
	return 0;
}


int MOAIGameCenterIOS::_showLeaderboard ( lua_State* L ) {
	
	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];	
	GKLeaderboardViewController *leaderboardController = [[ GKLeaderboardViewController alloc ] init ];
    if ( leaderboardController != nil ) {	
		
		leaderboardController.category = [ NSString stringWithUTF8String:lua_tostring(state,1)]  ;
        leaderboardController.leaderboardDelegate = MOAIGameCenterIOS::Get ().mLeaderboardDelegate;
		if ( rootVC != nil ) {
			[ rootVC presentModalViewController: leaderboardController animated: YES ];
		}
    }

	[ leaderboardController release ];
		
	return 0;
}

//================================================================//
// MOAIGameCenterIOS
//================================================================//

//----------------------------------------------------------------//
MOAIGameCenterIOS::MOAIGameCenterIOS () :
	mIsGameCenterSupported ( false ) {

	RTTI_SINGLE ( MOAILuaObject )		
	
	mLeaderboardDelegate = [ MOAIGameCenterIOSLeaderboardDelegate alloc ];
	mAchievementDelegate = [ MOAIGameCenterIOSAchievementDelegate alloc ];
	mAchievementsDictionary = [[ NSMutableDictionary alloc ] init ];
}

//----------------------------------------------------------------//
MOAIGameCenterIOS::~MOAIGameCenterIOS () {
	
	[ mAchievementDelegate release ];
	[ mLeaderboardDelegate release ];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "TIMESCOPE_TODAY",		( u32 )TIMESCOPE_TODAY );
	state.SetField ( -1, "TIMESCOPE_WEEK",		( u32 )TIMESCOPE_WEEK );
	state.SetField ( -1, "TIMESCOPE_ALLTIME",	( u32 )TIMESCOPE_ALLTIME );
	
	state.SetField ( -1, "PLAYERSCOPE_GLOBAL",	( u32 )PLAYERSCOPE_GLOBAL );
	state.SetField ( -1, "PLAYERSCOPE_FRIENDS",	( u32 )PLAYERSCOPE_FRIENDS );
	
	luaL_Reg regTable [] = {
		{ "authenticatePlayer",			_authenticatePlayer },
		{ "getPlayerAlias",					_getPlayerAlias },
		{ "getAchievements",					_getAchievements },
		{ "getScores",				_getScores },
		{ "isSupported",				_isSupported },
		{ "reportAchievementProgress",	_reportAchievementProgress },
		{ "reportScore",				_reportScore },
		{ "setGetScoresCallback",		_setGetScoresCallback },
		{ "setReportCompletionCallback",		_setReportCompletionCallback },
		{ "setAchievementReadyCallback",		_setAchievementReadyCallback },
		{ "showDefaultAchievements",	_showDefaultAchievements },
		{ "showDefaultLeaderboard",		_showDefaultLeaderboard },
		{ "showLeaderboard",		_showLeaderboard },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::CallScoresCallback ( NSArray* scores ) {

	if ( mGetScoresCallback && [ scores count ] > 0 ) {
	
		MOAIScopedLuaState state = mGetScoresCallback.GetSelf ();
		lua_newtable ( state );
		
		for ( id score in scores ) {
		
			lua_pushstring( state, "formattedValue");
			lua_pushstring ( state, [[ score formattedValue ] UTF8String ]);
			lua_settable ( state, -3 );			
			
			lua_pushstring( state, "playerId");
			lua_pushstring ( state, [[ score playerID ] UTF8String ]);
			lua_settable ( state, -3 );
			
			lua_pushstring( state, "category");
			lua_pushstring ( state, [[ score category ] UTF8String ]);
			lua_settable ( state, -3 );
						
			lua_pushstring( state, "rank");
			lua_pushnumber ( state, [ score rank ] );
			lua_settable ( state, -3 );
			
			lua_pushstring( state, "date");
			[[ score date ] toLua:state ];
			lua_settable ( state, -3 );
		}
		
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::CallReportScoreCompletionCallback ( NSError* error ) {

	if ( mReportCompletionCallback ) {
	
		MOAIScopedLuaState state = mReportCompletionCallback.GetSelf ();

		lua_pushstring(state,"leaderboard");

		if(error != nil){
			lua_pushnumber(state, [error code]);
			state.DebugCall ( 2, 0 );
		}
		else{
			state.DebugCall(1,0);
		}

	}
}


//----------------------------------------------------------------//
void MOAIGameCenterIOS::CallReportAchievementCompletionCallback ( NSError* error ) {

	if ( mReportCompletionCallback ) {
	
		MOAIScopedLuaState state = mReportCompletionCallback.GetSelf ();
		
		lua_pushstring(state,"achievement");

		if(error != nil){
			lua_pushnumber(state, [error code]);
			state.DebugCall ( 2, 0 );
		}
		else{
			state.DebugCall(1,0);
		}

	}
}

void MOAIGameCenterIOS::CallAchievementReadyCallback ( NSError* error ) {

	if ( mAchievementReadyCallback ) {
	
		MOAIScopedLuaState state = mAchievementReadyCallback.GetSelf ();

		if(error != nil){
			lua_pushnumber(state, [error code]);
			state.DebugCall ( 1, 0 );
		}
		else{
			state.DebugCall(0,0);
		}

	}
}

void MOAIGameCenterIOS::CallAuthenticationCallback(NSError* error){
	if( mAuthenticationCallback ){
		MOAIScopedLuaState state = mAuthenticationCallback.GetSelf ();

		if(error != nil){
			lua_pushnumber(state, [error code]);
			state.DebugCall ( 1, 0 );
		}
		else{			
			state.DebugCall(0,0);
		}
	}
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::CreateAchievementDictionary ( NSArray* achievements ) {
	for ( GKAchievement* achievement in achievements ) {		
		[ mAchievementsDictionary setObject: achievement forKey: achievement.identifier ];
	}
}

//----------------------------------------------------------------//
GKAchievement* MOAIGameCenterIOS::GetAchievementFromDictionary ( cc8* identifier ) {
	
	GKAchievement* achievement = [ mAchievementsDictionary objectForKey:[ NSString stringWithUTF8String:identifier ]];
	
    if ( achievement == nil ) {
	
        achievement = [[[ GKAchievement alloc ] initWithIdentifier:[ NSString stringWithUTF8String:identifier ]] autorelease ];
        [ mAchievementsDictionary setObject:achievement forKey:achievement.identifier  ];
    }
	
    return [[ achievement retain ] autorelease ];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::GetAchievements () {
	
	[ GKAchievement loadAchievementsWithCompletionHandler:^( NSArray* achievements, NSError* error ) {
	
		if ( error == nil ) {
					
			CreateAchievementDictionary ( achievements );
		}

		CallAchievementReadyCallback(error);
	}];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::ReportAchievementProgress ( cc8* identifier, float percent ) {

	GKAchievement *achievement = GetAchievementFromDictionary ( identifier );
	
    if ( achievement != nil && achievement.percentComplete < percent ) {
		
		if ( !achievement.isCompleted ) {
			
			achievement.percentComplete = percent;
			
			[ achievement reportAchievementWithCompletionHandler: ^(NSError *error) {
				MOAIGameCenterIOS::Get ().CallReportAchievementCompletionCallback ( error );
				if ( error != nil )
				{
					printf ( "Error in achievement reporting: %d", [ error code ]);
					// TODO: Save off achievement for later if network error
				}
			}];
		}
	}
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::ReportScore ( s64 score, cc8* category ) {

	GKScore *scoreReporter = [[[ GKScore alloc ] initWithCategory:[ NSString stringWithUTF8String:category ]] autorelease ];
	
	if ( scoreReporter ) {
	
		scoreReporter.value = score;
		
		[ scoreReporter reportScoreWithCompletionHandler: ^( NSError *error ) {
			MOAIGameCenterIOS::Get ().CallReportScoreCompletionCallback ( error );
			if ( error != nil ) {
				
				printf ( "Error in score reporting: %d", [ error code ]);
				// TODO: Save off score for later if network error
			}
		}];
	}
}

//================================================================//
// MOAIGameCenterIOSLeaderboardDelegate
//================================================================//
@implementation MOAIGameCenterIOSLeaderboardDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MOAIGameCenterIOSLeaderboardDelegate
	//================================================================//
	
	- ( void ) leaderboardViewControllerDidFinish:( GKLeaderboardViewController* ) viewController {
		
		UNUSED ( viewController );
	
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		if ( rootVC ) {
			
			[ rootVC dismissModalViewControllerAnimated:YES ];
		}
	}
@end

//================================================================//
// MOAIGameCenterIOSAchievementDelegate
//================================================================//
@implementation MOAIGameCenterIOSAchievementDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MOAIGameCenterIOSAchievementDelegate
	//================================================================//
	
	- ( void ) achievementViewControllerDidFinish:( GKAchievementViewController* ) viewController {
		
		UNUSED ( viewController );
	
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		if ( rootVC ) {
			
			[ rootVC dismissModalViewControllerAnimated:YES ];
		}
	}
@end