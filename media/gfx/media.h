#ifndef MEDIA_MEDIA_H
#define MEDIA_MEDIA_H



#include "../../core/gba.h"
#include "../../core/types.h"


//palette
const u16 gfx_palette[256];

//generic tiles
const u16 font_tile_data[ 8*376 ];
const u16 font_scroll_1_tile_data[ 8*376 ];
const u16 font_scroll_2_tile_data[ 8*376 ];
const u16 font_scroll_3_tile_data[ 8*376 ];

const u16 blank_tile_data[ 8*16 ] ;

//masks
const u16 generic_mask_data[ 8*8 ];
//u8 masks
const u8 generic_mask_u8[8]; //8*y


const u16 torch_beam_tile_data[8*208];
const u16 walls_green_tile_data[8*88];


#endif
