#include "maps.h"
#include "game.h"
#include "../media/map/map_data.h"
#include "../core/gba.h"
#include "../core/types.h"
#include "../core/tile_alloc.h"




#define LEVEL_COUNT 1
extern const u16 LevelTileMap1[ MEDIA_MAP_W * MEDIA_MAP_W ];


u8 CurrentLevel=0;




const u16* MapTileAddresses[ LEVEL_COUNT ] = {
	LevelTileMap1,
};




void LoadLevelRow( u8 ScreenCol, u8 ScreenRow, u8 LevelCol, u8 LevelRow )
{
	if ((32-ScreenCol)>0) 
		FillBgU16TileMap( &tile_map[ FLOOR_BG ][ScreenCol+(ScreenRow*32)], &MapTileAddresses[CurrentLevel][LevelCol +(LevelRow*64)], (32-ScreenCol)*2, 1 );
	if (ScreenCol>0)	
		FillBgU16TileMap( &tile_map[ FLOOR_BG ][(ScreenRow*32)], &MapTileAddresses[CurrentLevel][LevelCol+(32-ScreenCol) +(LevelRow*64)], (ScreenCol)*2, 1 );

/*	for ( x=ScreenCol; x<32; x++)
	{
		s_x = x;
		tx = LevelCol+(x)-ScreenCol;//0
		tile_map[ FLOOR_BG ][ XY_ARRAY(s_x,s_y,32) ] =	MapTileAddresses[CurrentLevel][ XY_ARRAY(tx,LevelRow+y,64) ];
	}

	for ( x=0; x<ScreenCol; x++)
	{
		s_x = x ;
		tx = LevelCol+(x)+(32-ScreenCol);
		tile_map[ FLOOR_BG ][ XY_ARRAY(s_x,s_y,32) ] =	MapTileAddresses[CurrentLevel][ XY_ARRAY(tx,LevelRow+y,64) ];
	}
*/


	tile_map[ FLOOR_BG ][ XY_ARRAY(ROLL_SCREEN_NUMBER( ScreenCol + 31 ),ScreenRow,32) ] =
		MapTileAddresses[CurrentLevel][ XY_ARRAY(LevelCol-1,LevelRow,64) ];

}

void LoadLevelColumn( u8 ScreenCol, u8 ScreenRow, u8 LevelCol, u8 LevelRow )
{
	/*	u16 sy;
	u16 ty;
	ty = LevelRow;
	for ( sy=ScreenRow; sy<32; sy++)
	{
		tile_map[ FLOOR_BG ][ScreenCol+(sy*32)] = MapTileAddresses[CurrentLevel][LevelCol+(ty*64)];
		ty++;
	}
	for ( sy=0; sy<ScreenRow; sy++)
	{
		tile_map[ FLOOR_BG ][ScreenCol+(sy*32)] = MapTileAddresses[CurrentLevel][LevelCol+(ty*64)];
		ty++;
	}	*/
	s32 x,y;
	u16 s_x,s_y;
	s_x = ScreenCol;
	//col
	x=0;
	for ( y=0; y<FULL_TILE_H; y++)
	{
		s_y = ROLL_SCREEN_NUMBER( ScreenRow + y ) ;

		tile_map[ FLOOR_BG ][ XY_ARRAY(s_x,s_y,32) ] =
			MapTileAddresses[CurrentLevel][ XY_ARRAY(LevelCol+x,LevelRow+y,64) ];
	}	
	s_y = ROLL_SCREEN_NUMBER( ScreenRow + 31 ) ;
	y=-1;
	tile_map[ FLOOR_BG ][ XY_ARRAY(s_x,s_y,32) ] =
		MapTileAddresses[CurrentLevel][ XY_ARRAY(LevelCol+x,LevelRow+y,64) ];

	//	FillBgU16TileMap( &tile_map[ FLOOR_BG ][ScreenCol+(ScreenRow*32)], &MapTileAddresses[Level][LevelCol +(LevelRow*64)], 32*2, 1 );
}

void LoadLevel( u8 Level )
{
	u16 x,y;
	CurrentLevel = Level;
//	FillBgU16TileMap( tile_map[ FLOOR_BG ], MapTileAddresses[Level], MEDIA_MAP_W, MEDIA_MAP_H );

	//top left

	for (y=0;y<32;y++)
//		FillBgU16TileMap( &tile_map[ FLOOR_BG ][y*32], &MapTileAddresses[CurrentLevel][y*64], 32*2, 1 );
		LoadLevelRow( 0, y, 0, y );

}


