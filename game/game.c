#include "game.h"

#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"
#include "../core/tile_alloc.h"
#include "../core/math.h" //cos/sin
#include "../core/sprites.h"
#include "../core/animated_sprite.h"
#include "../core/keypad.h"
#include "../core/font.h"
#include "../core/collisions.h"

#include "main.h"
#include "torch.h"
#include "tile_sets.h"
#include "player.h"
#include "maps.h"



//where lightning flash comes in
const u32 WindowPos[2] = {	0,	20<<8,	};
//priorities
const u8 BgOrder[3] = { 0,	3,	1,	};



s32 ang,ScrollX,ScrollY;
aPlayer Player;
u16 GameUpdateFlag;

#define TEXTBG_SIZE_256x256 0x0
#define TEXTBG_SIZE_256x512 0x8000
#define TEXTBG_SIZE_512x256 0x4000
#define TEXTBG_SIZE_512x512 0xC000

#define ROTBG_SIZE_128x128 0x0
#define ROTBG_SIZE_256x256 0x4000
#define ROTBG_SIZE_512x512 0x8000
#define ROTBG_SIZE_1024x1024 0xC000
#define ROTBG_WRAP (1<<13)

void LevelInit(void)
{
	hide_all_backgrounds;
	set_mode(1, BG0_ENABLE | BG1_ENABLE | BG2_ENABLE ,1);

	//hud HUD_BG
	REG_BG0CNT = CHAR_BLOCK_REGISTER(0) | TEXTBG_SIZE_256x256 | BG_PRIORITY(BgOrder[HUD_BG])   | SCREEN_BLOCK_REGISTER(0) | BG_MOSAIC | BG_COLOR_256(1) ;
	//floor LEVEL_BG
	REG_BG1CNT = CHAR_BLOCK_REGISTER(1) | TEXTBG_SIZE_256x256 | BG_PRIORITY(BgOrder[FLOOR_BG]) | SCREEN_BLOCK_REGISTER(1) | BG_MOSAIC | BG_COLOR_256(1)  ;
	//rot bg TORCH_BG
	REG_BG2CNT = CHAR_BLOCK_REGISTER(2) | ROTBG_SIZE_512x512  | BG_PRIORITY(BgOrder[TORCH_BG]) | SCREEN_BLOCK_REGISTER(2) | BG_COLOR_256(1) | ROTBG_WRAP  ;

	load_tile_palette(0);
	clear_current_tiledata( BG(HUD_BG) );
	clear_current_tiledata( BG(FLOOR_BG) );
	clear_current_tiledata( BG(TORCH_BG) );
	clear_current_tiledata( OBJ );

	load_tile_set(	BG(HUD_BG),	BLANK_TILES);
	load_tile_set(	BG(HUD_BG),	FONT_TILES);

//	load_tile_set(	BG(FLOOR_BG),	BLANK_TILES );
	load_tile_set(	BG(FLOOR_BG),	WALLS_GREEN_TILES );
	load_tile_set(	BG(FLOOR_BG),	FONT_TILES );

	load_tile_set(	BG(TORCH_BG),	TORCH_BEAM_TILES);
	load_tile_set(	BG(TORCH_BG),	FONT_TILES);

	set_text_boundries( 0, VISIBLE_TILE_H-1, 0, VISIBLE_TILE_W );
//	clear_tile_map( BG_TILE( BG(HUD_BG),	BLANK_TILES), HUD_BG);

	LoadLevel( 0 );

	GameUpdateFlag = TORCH_ROT ;

	ResetTorchBg();
	InitPlayer( &Player, 0, 0 );
	BindCam( &Player.x, &Player.y );
}



u32 GameTick=0;
s32 xscr,yscr;

void GameLoop(void)
{
	start_frame();
	UpdateCamera( false );
	/*
	if (KEY_B)		ang = roll_s32( ang-7, 0, 360);
	if (KEY_A)		ang = roll_s32( ang+7, 0, 360);
	if (KEY_UP)		ScrollY -= 1;
	if (KEY_DOWN)	ScrollY += 1;
	if (KEY_LEFT)	ScrollX -= 1;
	if (KEY_RIGHT)	ScrollX += 1;

	draw_text(0,2,0,"%4d",ang);
	draw_text(0,3,0,"%4d",ScrollX);
	draw_text(0,4,0,"%4d",ScrollY);

	RotateBg2( ang, 120+ScrollX, 80+ScrollY, 1<<8, 0, 0 );

	if (KEY_UP)		yscr -= 1;
	if (KEY_DOWN)	yscr += 1;
	if (KEY_LEFT)	xscr -= 1;
	if (KEY_RIGHT)	xscr += 1;

	scrollbackground( xscr, yscr, FLOOR_BG );
*/
	GetPlayerInput( &Player );
	PlayerMove( &Player );
	PlayerSpriteUpdate( &Player );

	draw_text(0,2,0,"%4d", Player.TorchAng );
	draw_text(0,3,0,"%9d", Player.x );
	draw_text(0,4,0,"%9d", Player.y );

	draw_text(0,6,0,"%4d", CameraPixelLeft() );
	draw_text(0,7,0,"%4d", CameraPixelTop() );
			
			


	GameTick++;
	draw_text(0,18,0,"%d", GameTick );

	//clear flags
	GameUpdateFlag = 0;

	end_frame();
}


