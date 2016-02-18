#ifndef GAME_TORCH_H
#define GAME_TORCH_H



#include "main.h"
#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"




#define TORCH_BEAM_W 8
#define TORCH_BEAM_H 9




#define ClearTorchBg FillBgU16TileMap( tile_map[TORCH_BG], (u16*)BlankMap, 64, 64 )
//#define HideTorchBg	ClearTileMapU8( tile_map[ BG(TORCH_BG) ], 64, 64, BG_TILE( BG(TORCH_BG), TORCH_BEAM_TILES)+8 );
//#define RotateTorch(Angle,ScrollX,ScrollY )	RotateBg2( Angle, 128-8+(ScrollX), 80+(ScrollY), 1<<8, 0, 0 );
#define RotateTorch(Angle,ScrollX,ScrollY )	RotateBg2( Angle, (ScrollX), (ScrollY), 1<<8, 0, 0 );
void ResetTorchBg(void);





#endif

