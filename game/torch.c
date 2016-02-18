#include "torch.h"
#include "tile_sets.h"
#include "game.h"

#include "../core/dma.h"


extern const u16 TorchBeamMap[64 * 64];
extern const u8 MiniTorchBeamMap[ TORCH_BEAM_W * TORCH_BEAM_H ];

#define TORCH_BG_W 512
#define ROTBG_TILE_W (TORCH_BG_TILE_W/2)
#define TORCH_BG_TILE_W (TORCH_BG_W/8)


void ResetTorchBg(void)
{
	
	s32 x,y,a;
	u16 Tile;

/*
	if(0) //small array copy
	{
		ClearTorchBg;

		for (y=0;y<TORCH_BEAM_H;y++)
		{
			for (x=0;x<TORCH_BEAM_W/2;x++)
			{
				if ( x&1 )
				{
					Tile |= ( BG_TILE( BG(TORCH_BG), TORCH_BEAM_TILES) + MiniTorchBeamMap[ XY_ARRAY( x+TORCH_BEAM_W/2,y,TORCH_BEAM_W) ] ) <<8 ;
					tile_map[TORCH_BG][ XY_ARRAY( (x-1)/2,TORCH_BG_TILE_W-TORCH_BEAM_W+y,ROTBG_TILE_W ) ] = Tile;
				}
				else
					Tile = BG_TILE( BG(TORCH_BG), TORCH_BEAM_TILES) + MiniTorchBeamMap[ XY_ARRAY(x+TORCH_BEAM_W/2,y,TORCH_BEAM_W) ] ;
			}
			for (x=0;x<TORCH_BEAM_W/2;x++)
			{
				if ( x&1 )
				{
					Tile |= ( BG_TILE( BG(TORCH_BG), TORCH_BEAM_TILES) + MiniTorchBeamMap[ XY_ARRAY( x ,y,TORCH_BEAM_W) ] ) <<8 ;
					tile_map[TORCH_BG][ XY_ARRAY( (ROTBG_TILE_W+2)-(TORCH_BEAM_W/2) + ((x-1)/2),TORCH_BG_TILE_W-TORCH_BEAM_W+y,ROTBG_TILE_W ) ] = Tile;
				}
				else
					Tile = BG_TILE( BG(TORCH_BG), TORCH_BEAM_TILES) + MiniTorchBeamMap[ XY_ARRAY( x ,y,TORCH_BEAM_W) ] ;
			}
		}
	}
*/

	FillBgU16TileMap( tile_map[TORCH_BG], TorchBeamMap, 64, 64 );
	
	REG_BLDMOD = TARGET_TOP_BG2 | TARGET_LOW_BG1 | TARGET_LOW_OBJ | BLEND_NEG;
	REG_COLEV = BLEND_LEVEL(8);
}

