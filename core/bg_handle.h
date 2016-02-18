#ifndef _CORE_BG_HANDLE_H
#define _CORE_BG_HANDLE_H


#include "gba.h"
#include "types.h"
#include "dma.h"


void FillBgU8TileMap( u8* TileAddr, u8* TileMap, u16 MapW, u16 MapH );
void FillBgU16TileMap( u16* TileAddr, u16* TileMap, u16 MapW, u16 MapH );
void FillBgU16TileMapWithU8( u16* TileAddr, u8* TileMap, u16 MapW, u16 MapH );
//void ClearTileMapU8( u8 *TileAddr, u16 MapW, u16 MapH, u8 TileN );
#define ClearTileMapU8( TileAddr, MapW, MapH, TileN ) memset( TileAddr, TileN, MapW*MapH )
void ClearTileMapU16( u16 *TileAddr, u16 MapW, u16 MapH, u8 TileN );


#endif

