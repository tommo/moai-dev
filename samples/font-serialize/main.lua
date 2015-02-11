----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

-- build the font
-- charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-'
-- charcodes=charcodes..'ビジネスソリューション打倒小猪静'
charcodes='！度ペ长ルロ !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~在大到こ带程为主失模次欢链元锁义素の奇所游单子录よ全教そ学うへー式金ン条典譯潜来治兽チ初最传经イ获戏师エ统种里于合回量起崛分热上线咒完对ス黄球个力有一角徒独连殩语得。ト成的开落迎记首'
text = 'よ全教そ学うへー'

font = MOAIFont.new ()
font:load ( 'TakaoPGothic.ttf' )
-- font:preloadGlyphs ( charcodes, 8 )
-- font:preloadGlyphs ( charcodes, 12 )
-- font:preloadGlyphs ( charcodes, 16 )
-- font:preloadGlyphs ( charcodes, 24 )
font:preloadGlyphs ( charcodes, 32 )
-- font:preloadGlyphs ( charcodes, 42 )
-- font:preloadGlyphs ( charcodes, 56 )
-- font:preloadGlyphs ( charcodes, 64 )
-- font:preloadGlyphs ( charcodes, 72 )
-- font:preloadGlyphs ( charcodes, 76 )

-- yank out the font image
image = font:getImage ()
image:writePNG ( 'font.png' )

-- serialize out to a file
file = io.open ( 'font.lua', 'w' )
file:write ( MOAISerializer.serializeToString ( font ))
file:close ()

-- nothing up our sleeve...
image = nil
font = nil
file = nil

MOAISim.forceGarbageCollection ()

-- load and show the font
MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

-- read the font in from the file
file = io.open ( 'font.lua', 'r' )
font = loadstring ( file:read ( '*all' ))()
file:close ()

-- load the font image back in
image = MOAIImage.new ()
image:load ( 'font.png', 0 )

-- set the font image
font:setCache ()
font:setReader ()
font:setImage ( image )

-- font now ready for use
textbox = MOAITextBox.new ()
textbox:setString ( text )
textbox:setFont ( font )
textbox:setTextSize ( 32 )
textbox:setRect ( -150, -230, 150, 230 )
textbox:setYFlip ( true )
layer:insertProp ( textbox )
