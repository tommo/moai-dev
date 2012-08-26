#!/bin/bash

#================================================================#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#================================================================#

#----------------------------------------------------------------#
# path to Android SDK folder (on Windows, you MUST use forward 
# slashes as directory separators, e.g. C:/android-sdk)
#----------------------------------------------------------------#

	android_sdk_root="/Users/tommo/dev/android-sdk-macosx"

#----------------------------------------------------------------#
# space-delimited list of source lua directories to add to the 
# application bundle and corresponding destination directories in 
# the assets directory of the bundle
#----------------------------------------------------------------#

	src_dirs=( "/Users/tommo/prj/moai/spell/lua" "../../src/lua-modules" )
	# src_dirs=( "../../samples/android/app-accelerometer" "../../src/lua-modules" )
	dest_dirs=(	"lua" "lua/lua-modules" )

#----------------------------------------------------------------#
# debug & release settings
# you must define key store data in order to build for release
#----------------------------------------------------------------#

	debug=false
	key_store="/Users/tommo/tommozhou.keystore"
	key_alias="tommo.zhou"
	key_store_password="gogogo"
	key_alias_password="gogogo"