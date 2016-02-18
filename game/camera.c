#include "camera.h"

#include "../core/gba.h"
#include "../core/types.h"
#include "maps.h"
#include "game.h"


//pixels scrolled in register (0->TILE_W)
s32 CamScrollTinyPixel[2] = {0,0};
//screen tiles scrolled
s32 CamScrollTile[2] = {0,0};

//current map coord
s32 CamCurrent[2] = {0,0};
//corrds we update from
s32 *CamBind[2] = { &CamCurrent[X],&CamCurrent[Y] };


//returns far left pixel coord
s32 CameraPixelLeft(void)
{
	s32 x;
	x = (CamCurrent[X]) + LEFT_CAM_OFFSET;

	if ( x < LEFT_BOUND )	
		return LEFT_BOUND;
	if ( x+RIGHT_CAM_OFFSET > RIGHT_BOUND )
		return (RIGHT_BOUND - RIGHT_CAM_OFFSET);

	return x;
}

//returns top most pixel on screen
s32 CameraPixelTop(void)
{
	s32 y;
	y = (CamCurrent[Y]) + TOP_CAM_OFFSET;

	if ( y < TOP_BOUND ) 
		return TOP_BOUND;
	if ( y+BOTTOM_CAM_OFFSET > BOTTOM_BOUND )	
		return BOTTOM_BOUND - BOTTOM_CAM_OFFSET;

	return y;
}


//returns pixels' coord in relation to the screen
s32 MapOnScreenX( s32 x ) 
{
	return x-CamScrollPixel(X);
}

s32 MapOnScreenY( s32 y ) 
{
	return y-CamScrollPixel(Y);
}

//is any part ofthis object visible?
u8 MapObjVisibleX( s32 x, s32 w )
{
	if ( MapOnScreenX(x) >= 240 )		return false;
	if ( MapOnScreenX(x)+w < 0 )		return false;
	return true;
}
u8 MapObjVisibleY( s32 y, s32 h )
{
	if ( MapOnScreenY(y) >= 160 )		return false;
	if ( MapOnScreenY(y)+h < 0 )		return false;
	return true;
}


void BindCam( s32* BindX, s32* BindY )
{
	CamBind[X] = BindX;
	CamBind[Y] = BindY;
	CamCurrent[X] = *CamBind[X];
	CamCurrent[Y] = *CamBind[Y];
}

s32 camsave[2];

void UpdateCamera( u8 NoTransition )
{
	s32 CamWas[2];

	//no bind, no change
	if (!CamBind[X] || !CamBind[Y] ) return;

	CamWas[X] =- CameraPixelLeft();
	CamWas[Y] =- CameraPixelTop();
	
	CamCurrent[X] += ( *CamBind[X] - CamCurrent[X] ) / CAM_TRANS_RATE;
	CamCurrent[Y] += ( *CamBind[Y] - CamCurrent[Y] ) / CAM_TRANS_RATE;

	CamScrollTinyPixel[X] += CamWas[X]+CameraPixelLeft() ;
	CamScrollTinyPixel[Y] += CamWas[Y]+CameraPixelTop() ;

	while ( CamScrollTinyPixel[X] < 0 )
	{
		CamScrollTile[X]--;	//gone left a tile
		CamScrollTinyPixel[X] += TINY_SCROLL_AMOUNT ; //remove the tile jump
		//refill tile next previous tile to the left
		LoadLevelColumn( ROLL_SCREEN_NUMBER(CamScrollTile[X]-1) , ROLL_SCREEN_NUMBER(CamScrollTile[Y]) , CamScrollTile[X]-1, CamScrollTile[Y] );
	}

	while (CamScrollTinyPixel[X]>=TINY_SCROLL_AMOUNT)
	{
		//gone right a tile
		CamScrollTile[X]++;
		CamScrollTinyPixel[X] -= TINY_SCROLL_AMOUNT;
		//refill tile next tile to the right with the next
		LoadLevelColumn( ROLL_SCREEN_NUMBER(CamScrollTile[X]+30) , ROLL_SCREEN_NUMBER(CamScrollTile[Y]) , CamScrollTile[X]+30, CamScrollTile[Y] );
	}

	while ( CamScrollTinyPixel[Y] < 0 )
	{
		//gone up a tile
		CamScrollTile[Y]--;
		CamScrollTinyPixel[Y] += TINY_SCROLL_AMOUNT;
		//refill tile next tile to the left for wrapping
		LoadLevelRow( ROLL_SCREEN_NUMBER(CamScrollTile[X]) , ROLL_SCREEN_NUMBER(CamScrollTile[Y]-1) , CamScrollTile[X], CamScrollTile[Y]-1 );
	}


	while (CamScrollTinyPixel[Y]>=TINY_SCROLL_AMOUNT)
	{
		//gone down a tile
		CamScrollTile[Y]++;
		CamScrollTinyPixel[Y] -= TINY_SCROLL_AMOUNT;
		//refill tile next tile to the right for wrapping
		LoadLevelRow( ROLL_SCREEN_NUMBER(CamScrollTile[X]) , ROLL_SCREEN_NUMBER(CamScrollTile[Y]+30) , CamScrollTile[X], CamScrollTile[Y]+30 );
	}

	scrollbackground( CamScrollPixel(X), CamScrollPixel(Y), FLOOR_BG );
}
