#ifndef GAME_GAME_H
#define GAME_GAME_H



#include "main.h"
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




//game vars
//MAP_W/H in map.h


//update flag bits - for individual player updates, or applies to all if set on GameUpdate
#define SHADOW_MOVE		BIT00 //shadows need moving
#define SHADOW_ROT		BIT01 //light source moved, comparison angle needs updating
#define LEVEL_FULLYLIT	BIT02 //gets rid of blankd tiles
#define LEVEL_NORMLIT	BIT03 //back to regular -blanked if not in LOS- tile layout
#define TORCH_GO_OFF	BIT04 //torch has been switched off
#define TORCH_GO_ON		BIT05 //torch switched back on
#define TORCH_ROT		BIT06 //torch direction changed
#define PLAYER_ROT		BIT07 //player direction changed
#define PLAYER_MOVE		BIT08 //player sprites need moving


//physical addresses of BG's
#define HUD_BG			0
#define TORCH_BG		2 //rotated one
#define UNUSED_BG		3 //non existant in mode1
#define FLOOR_BG		1

#define SPR_HUD_BG		0 //over hud
#define SPR_TORCH_BG	1 //over torch
#define SPR_OBJ_BG		2 //over level, over player shadows
#define SPR_SHADOW_BG	3 //over floor, under objs


extern const u32 WindowPos[2];
extern const u8 BgOrder[3];






void LevelInit(void);
void GameLoop(void);






#endif

