#ifndef GAME_MAPS_H
#define GAME_MAPS_H


#include "../core/gba.h"
#include "../core/types.h"
#include "../media/map/map_data.h"


#define MAP_W (MAP_TILE_W*TILE_W)
#define MAP_H (MAP_TILE_H*TILE_H)
//#define MAP_TILE_W 32
//#define MAP_TILE_H 32
#define MAP_TILE_W (MEDIA_MAP_W)
#define MAP_TILE_H (MEDIA_MAP_H)


void LoadLevel( u8 Level );
void LoadLevelRow( u8 ScreenCol, u8 ScreenRow, u8 LevelCol, u8 LevelRow );
void LoadLevelColumn( u8 ScreenCol, u8 ScreenRow, u8 LevelCol, u8 LevelRow );



#endif

