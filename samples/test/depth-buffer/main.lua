----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAIGfxDevice.setClearDepth ( true )

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
-- layer:setSortMode ( MOAILayer2D.SORT_NONE ) -- don't need layer sort
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )
gfxQuad:setUVRect ( 0, 1, 1, 0 )

prop = MOAIProp.new ()
prop:setDeck ( gfxQuad )
prop:setDepthTest ( MOAIProp.DEPTH_TEST_LESS )
prop:setColor(0,1,0,1)
layer:insertProp ( prop )

prop:setRot ( 40, 0,0)
prop:setLoc (0,0,-10)
prop:moveLoc ( 0, 0, 128, 3 )

prop1 = MOAIProp.new ()
prop1:setDeck ( gfxQuad )
prop1:setDepthTest ( MOAIProp.DEPTH_TEST_LESS )
layer:insertProp ( prop1 )

-- prop1:moveRot ( 0, 360, 0, 3 )

camera = MOAICamera2D.new ()
-- camera:setLoc ( 0, 0, camera:getFocalLength ( 320 ))
camera:setFarPlane(-1000)
camera:setNearPlane(1000)
layer:setCamera ( camera )