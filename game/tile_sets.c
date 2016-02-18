#include "tile_sets.h"
#include "../media/gfx/media.h"
//#include "../core/sprites.h"



extern u16 *oam_data;

#define TILE_DATA_SIZE( tile_obj ) ( sizeof(tile_obj) / (sizeof(u16)*64) )

const u8 tile_set_lengths[TILE_TYPE_COUNT] = {
	TILE_DATA_SIZE(	blank_tile_data ),
	TILE_DATA_SIZE(	font_tile_data ),
	TILE_DATA_SIZE(	font_scroll_1_tile_data ),
	TILE_DATA_SIZE(	font_scroll_2_tile_data ),
	TILE_DATA_SIZE(	font_scroll_3_tile_data ),
	TILE_DATA_SIZE(	torch_beam_tile_data ),
	TILE_DATA_SIZE(	walls_green_tile_data ),
	
};


const u16 *tile_set_data_addr[TILE_TYPE_COUNT] ={
	blank_tile_data,
	font_tile_data,
	font_scroll_1_tile_data,
	font_scroll_2_tile_data,
	font_scroll_3_tile_data,
	torch_beam_tile_data,
	walls_green_tile_data,
};



u16 *tile_data_addr[1 + 4] = {
	((u16*)(0x6010000)), 
	(u16*)CHAR_BASE_BLOCK(0),
	(u16*)CHAR_BASE_BLOCK(1),
	(u16*)CHAR_BASE_BLOCK(2),
	(u16*)CHAR_BASE_BLOCK(3),
	//REG_TILE_BASE + (0x4000 * 1),
//	((u16*) (REG_TILE_BASE + 0x4000)), 
};


const u16 *tile_palette_data_addr[2] ={
	gfx_palette, gfx_palette,
};


u16 *tile_palette_addr[2] = {
	((u16*)0x5000200), ((u16*)(REG_PALETTE_BASE)), 
};
