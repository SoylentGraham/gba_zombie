project "zombie" readme (wordwrap)
=========================
this is the latest "demo" ive created (after the hockey game if your reading this before the gbadev.org competition)

basically im going through a lot of ideas for my next game, and this was one based on a mix of ideas -mainly- from alien breed by team17 (the orignal on the PC -and amiga im told, but i never saw this ver-) and luigis mansion which im really enjoying on my gamecube (i tottally recommend one and im pretty sure theres gonna be a lot of "classic" games on this, eg: super monkey ball)


basics
==================
move around with the D Pad, A holds off the torch, and on release turns it back on (luigis mansion style). theres nothing special about this demo really, but the main code is much improved over ferk and thought a lot of people might be interested in it

techy stuff
=================
all this is, is a mode2 demo, with a rotated BG with a big hole in it, in which the rotated bg is semi transparent, giving a "everything dark except the torch beam" effect.
like in the "ferk" demo layer 0 is a hud with some text output, and layer 1 (prioritised to layer 3 under the torch) is a map of tiles. (created using anth's -#gbadev- wonderful mapping tool)

if you want to compile this rather than nick bits out of it have a look on www.ferk.co.uk theres a quick guide there

theres a few changes from "ferk" for those that had a look at it

- the whole code is split into core/* and game/*, core stuff being, sprite, animation, bg, tile allocation and lots of other generic stuff. the game stuff (oddly enough) is game specific code. although most of the time, any new stuff that i need to intergrate into the core engine gets stuck into here. and eventually gets all sorted out (usually on the next game :)

- the dynamic tile reloading (my own complicated convention of reloading tiles from the map, into the tile map on screen making a potentially infinate sized map) has been speeded up and now uses DMA to copy

- the camera is controlled more seperatly and much improved over the ferk engine

- the input system is improved for more of a game system

most of these features all came from hockey, but thats not out yet :)


finally...
==============
any source i put up on my site is free. no charges. gratis. if you make a game or decent demo out of it, id like to know, purely cos im nosy.

feel free to ask about any specific parts of my code, or how/why i did this/that. you can ask me to make a game for you, but it aint gonna happen :]

thanks to anth for his wonderful mapping tool, and everyone else on #gbadev

graham@ferk.co.uk <---- me
www.ferk.co.uk <---- check back for updates on my sources, or any new demos/sources etc
www.gbadev.org <---- go here, daily.
#gbadev on efnet <---- go here just as often :)



--fatgraham






