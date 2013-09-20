//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-core/host.h>
#import <moai-iphone/AKU-iphone.h>

#include <moai-sim/headers.h>
#include <moai-sim/host.h>
#include <moai-util/host.h>

#import "MoaiAppDelegate.h"
#import "LocationObserver.h"
#import "MoaiVC.h"
#import "MoaiView.h"

#if MOAI_WITH_BOX2D
	#include <moai-box2d/host.h>
#endif

#if MOAI_WITH_CHIPMUNK
	#include <moai-chipmunk/host.h>
#endif

//================================================================//
// AppDelegate
//================================================================//
@implementation MoaiAppDelegate

	@synthesize window = mWindow;
	@synthesize rootViewController = mMoaiVC;

	//----------------------------------------------------------------//
	-( void ) dealloc {

		[ mMoaiVC release ];
		[ mMoaiView release ];
		[ mWindow release ];
		[ super dealloc ];
	}

	//================================================================//
	#pragma mark -
	#pragma mark Protocol UIApplicationDelegate
	//================================================================//	

	//----------------------------------------------------------------//
	-( void ) application:( UIApplication* )application didFailToRegisterForRemoteNotificationsWithError:( NSError* )error {
	
		AKUNotifyRemoteNotificationRegistrationComplete ( nil );
	}

	//----------------------------------------------------------------//
	-( BOOL ) application:( UIApplication* )application didFinishLaunchingWithOptions:( NSDictionary* )launchOptions {
		
		[ application setStatusBarHidden:true ];
		
		mMoaiView = [[ MoaiView alloc ] initWithFrame:[ UIScreen mainScreen ].bounds ];
        

		[ mMoaiView setUserInteractionEnabled:YES ];
		[ mMoaiView setMultipleTouchEnabled:YES ];
		[ mMoaiView setOpaque:YES ];
		[ mMoaiView setAlpha:1.0f ];

		mMoaiVC = [[ MoaiVC alloc ]	init ];
		[ mMoaiVC setView:mMoaiView ];
		
		mWindow = [[ UIWindow alloc ] initWithFrame:[ UIScreen mainScreen ].bounds ];
		[ mWindow setUserInteractionEnabled:YES ];
		[ mWindow setMultipleTouchEnabled:YES ];
		[ mWindow setOpaque:YES ];
		[ mWindow setAlpha:1.0f ];
		[ mWindow addSubview:mMoaiView ];
		[ mWindow setRootViewController:mMoaiVC ];
		[ mWindow makeKeyAndVisible ];
        
		[ mMoaiView moaiInit:application ];
		
		// select product folder
		NSString* luaFolder = [[[ NSBundle mainBundle ] resourcePath ] stringByAppendingString:@"/content" ];
		AKUSetWorkingDirectory ([ luaFolder UTF8String ]);
		
		UIInterfaceOrientation orientation= [[UIApplication sharedApplication] statusBarOrientation];
//		[mMoaiVC updateOrientation:orientation];
        if((orientation == UIInterfaceOrientationLandscapeLeft ) || ( orientation == UIInterfaceOrientationLandscapeRight)){
            AKUSetOrientation ( AKU_ORIENTATION_LANDSCAPE );
			NSLog(@"Landscape");
        }else{
            AKUSetOrientation ( AKU_ORIENTATION_PORTRAIT );
			NSLog(@"Portrait");
        }

		// run scripts
		[ mMoaiView run:@"main.l2" ];
		
        // check to see if the app was lanuched from a remote notification
        NSDictionary* pushBundle = [ launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey ];
        if ( pushBundle != NULL ) {
            
            AKUNotifyRemoteNotificationReceived ( pushBundle );
        }
		
		// return
		return true;
	}

		
	//----------------------------------------------------------------//
	-( void ) application:( UIApplication* )application didReceiveRemoteNotification:( NSDictionary* )pushBundle {
		
		AKUNotifyRemoteNotificationReceived ( pushBundle );
	}
	
	//----------------------------------------------------------------//
	-( void ) application:( UIApplication* )application didRegisterForRemoteNotificationsWithDeviceToken:( NSData* )deviceToken {
	
		AKUNotifyRemoteNotificationRegistrationComplete ( deviceToken );
	}
	
	//----------------------------------------------------------------//
	-( void ) applicationDidBecomeActive:( UIApplication* )application {
	
		// restart moai view
		[ mMoaiView pause:NO ];
	}
	
	//----------------------------------------------------------------//
	-( void ) applicationDidEnterBackground:( UIApplication* )application {
        AKUAppWillEndSession();
	}
	
	//----------------------------------------------------------------//
	-( void ) applicationWillEnterForeground:( UIApplication* )application {
        AKUAppDidStartSession(true);
	}
	
	//----------------------------------------------------------------//
	-( void ) applicationWillResignActive:( UIApplication* )application {
        
		// pause moai view
		[ mMoaiView pause:YES ];
	}
	
	//----------------------------------------------------------------//
	-( void ) applicationWillTerminate :( UIApplication* )application {
        #if MOAI_WITH_BOX2D
            AKUFinalizeBox2D ();
        #endif

        #if MOAI_WITH_CHIPMUNK
            AKUFinalizeChipmunk ();
        #endif

        AKUFinalizeUtil ();
        AKUFinalizeSim ();
		AKUFinalize ();
	}

	//----------------------------------------------------------------//
	#if __IPHONE_OS_VERSION_MIN_REQUIRED > __IPHONE_4_1
		
		//----------------------------------------------------------------//
		// For iOS 4.2+ support
		-( BOOL )application:( UIApplication* )application openURL:( NSURL* )url sourceApplication:( NSString* )sourceApplication annotation:( id )annotation {

			AKUAppOpenFromURL ( url );
			return YES;
		}
	
	#else

		//----------------------------------------------------------------//
		-( BOOL )application :( UIApplication* )application handleOpenURL :( NSURL* )url {

			AKUAppOpenFromURL(url);
			return YES;
		}

	#endif

@end
