#ifndef GAME_TILE_SETS_H
#define GAME_TILE_SETS_H


#include "../core/gba.h"




enum {
	BLANK_TILES=0,
	FONT_TILES,
	FONT_SCROLL_1_TILES,
	FONT_SCROLL_2_TILES,
	FONT_SCROLL_3_TILES,
	TORCH_BEAM_TILES,
	WALLS_GREEN_TILES,

	TILE_TYPE_COUNT,
};

extern const u16 *tile_set_data_addr[TILE_TYPE_COUNT];



#define CAR_TILES 0
#define ROAD_TILES 0
#define BUILDING_TILES 0
#define SHADOW_TILES 0
#define SPOTLIGHT_TILES 0




#endif

