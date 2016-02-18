#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H



#include "../core/gba.h"



#define TINY_SCROLL_AMOUNT TILE_W
#define CAM_TRANS_RATE 4




extern s32 CamScrollTinyPixel[2];
extern s32 CamScrollTile[2];
//pixels scrolled
#define CamScrollPixel(xy) ((CamScrollTile[xy]*TILE_W)+CamScrollTinyPixel[xy])

extern s32 CamCurrent[2];
extern s32 *CamBind[2];

#define LEFT_BOUND 0
#define RIGHT_BOUND (MAP_W)
#define TOP_BOUND 0
#define BOTTOM_BOUND (MAP_H)
#define LEFT_CAM_OFFSET (-(VISIBLE_SCREEN_W/2))
#define RIGHT_CAM_OFFSET (VISIBLE_SCREEN_W)
#define TOP_CAM_OFFSET (-(VISIBLE_SCREEN_H/2))
#define BOTTOM_CAM_OFFSET (VISIBLE_SCREEN_H)

s32 CameraPixelLeft(void);
s32 CameraPixelTop(void);
#define CameraTileLeft (CameraPixelLeft/TILE_W)
#define CameraTileTop (CameraPixelTop/TILE_H)

s32 MapOnScreenX( s32 x );
s32 MapOnScreenY( s32 y );
u8 MapObjVisibleX( s32 x, s32 w );
u8 MapObjVisibleY( s32 y, s32 h );

void BindCam( s32* BindX, s32* BindY );
void UpdateCamera( u8 NoTransition );





#endif

