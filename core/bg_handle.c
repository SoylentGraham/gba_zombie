#include "bg_handle.h"
#include "gba.h"
#include "types.h"





void FillBgU8TileMap( u8* TileAddr, u8* TileMap, u16 MapW, u16 MapH )
{
	u16 a;
	//for loop until DMA copying works
	for (a=0;a<MapH*MapW;a++) 
		TileAddr[ a ] = TileMap[ a ];
}


void FillBgU16TileMap( u16* TileAddr, u16* TileMap, u16 MapW, u16 MapH )
{
	u16 a;
	//for loop until DMA copying works
	//for (a=0;a<MapH*(MapW/2);a++) 
	//	TileAddr[ a ] = TileMap[ a ];
	DMACopyU16( TileMap, TileAddr, (MapW/2), MapH );
}

void FillBgU16TileMapWithU8( u16* TileAddr, u8* TileMap, u16 MapW, u16 MapH )
{
	u16 a16,a8;
	u16 Tile;

	a16=0;
	//for loop until DMA copying works
	for (a8=0; a8<MapH*MapW; a8++) 
	{
		if ( a8 & 1 )
		{
			Tile |= (TileMap[ a8 ]<<8) ;
			TileAddr[ a16 ] = Tile;
			a16++;
		} else {
			Tile = (TileMap[ a8 ]) ;
		}

		a8++;
	}

}



void ClearTileMapU16( u16 *TileAddr, u16 MapW, u16 MapH, u8 TileN )
{
	//write two skip one
	memset( TileAddr, TileN, (MapW)*MapH );
}







