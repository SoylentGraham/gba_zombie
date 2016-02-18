#include "player.h"

#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"
#include "../core/tile_alloc.h"
#include "../core/math.h" //cos/sin
#include "../core/sprites.h"
#include "../core/animated_sprite.h"
#include "../core/keypad.h"
#include "../core/bg_handle.h"

#include "game.h"
#include "main.h"
#include "torch.h"
#include "tile_sets.h"
#include "maps.h"
#include "camera.h"


extern u16 GameUpdateFlag;

void InitPlayer( aPlayer *p, aSprite *ShadowSprite, aSprite *PlayerSprite )
{
	p->Action = 0;
	p->InputChangeFlag = 0;
	p->UpdateFlag = TORCH_ROT|PLAYER_ROT|PLAYER_MOVE ;
	p->x = 24;
	p->y = 48;

	p->DirectionBit = DIR_BIT_EO;
	p->DirectionAng = DIR_BIT_TO_DIR_ANG( p->DirectionBit );
	p->FaceAng = DIR_ANG_TO_ANG( p->DirectionAng );
	p->TorchAng = p->FaceAng ;

	p->Shadow = ShadowSprite;
	p->Sprite = PlayerSprite;

	
//	init_sprite( p->Sprite, SIZE_16, SQUARE, PLAYER_SPRITE_TILES, 0, SPR_OBJ_BG, 0, 0, 0 );

}



void GetPlayerInput( aPlayer *p )
{
	u16 OldInput = p->InputFlag;
	p->InputFlag = 0;
	p->InputChangeFlag = 0;
	
	//InputFlag has new changes
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_UP,	MOVE_BIT_UP		);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_DOWN,	MOVE_BIT_DOWN	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_LEFT,	MOVE_BIT_LEFT	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_RIGHT,	MOVE_BIT_RIGHT	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_A,		MOVE_BIT_ACT1	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_B,		MOVE_BIT_ACT2	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_L,		MOVE_BIT_ACT3	);
	UPDATE_INPUT_FLAG( p->InputFlag, KEY_R,		MOVE_BIT_ACT4	);
//	if ( KEY_UP )	p->InputFlag |= MOVE_UP;

	//InputChangeFlag denotes change in input, "flag now on"
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_UP		);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_DOWN	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_LEFT	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_RIGHT	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_ACT1	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_ACT2	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_ACT3	);
	COMPARE_UPDATE_INPUT_FLAG(	p->InputChangeFlag,	p->InputFlag,	OldInput,	MOVE_BIT_ACT4	);
//	if ( (p->InputFlag & MOVE_UP) && !(OldInput & MOVE_UP) )	p->InputChangeFlag |= MOVE_UP;
}




void PlayerMove( aPlayer *p )
{
	//save old direction 
	u16 OldDirBit = p->DirectionBit;
	u16 OldDirAng = p->DirectionAng;

	//reset current direction
	p->DirectionBit = 0;

	//set direction based on input
	if ( p->InputFlag & MOVE_BIT_UP )	p->DirectionBit |= DIR_BIT_NO; //NorthOnly + EastOnly = NorthEast
	if ( p->InputFlag & MOVE_BIT_LEFT )	p->DirectionBit |= DIR_BIT_WO;
	if ( p->InputFlag & MOVE_BIT_RIGHT )p->DirectionBit |= DIR_BIT_EO;
	if ( p->InputFlag & MOVE_BIT_DOWN )	p->DirectionBit |= DIR_BIT_SO;


	//torch input has gone on
	if ( p->InputChangeFlag & TORCH_INPUT_BIT )	
	{
		//force update
		p->UpdateFlag |= TORCH_GO_OFF;
	//	p->UpdateFlag &= TORCH_GO_ON;

		//set torch action mode to off (button is down)
		p->Action |= TORCH_IS_OFF;
		p->Action &= TORCH_IS_ON;
		p->Action = TORCH_IS_OFF;
	}

	//torch is off and player released torch input
	if ( !(p->InputFlag & TORCH_INPUT_BIT) && (p->Action & TORCH_IS_OFF) )
	{
		//turn torch back on
		p->Action |= TORCH_IS_ON;
		p->Action &= TORCH_IS_OFF;
		p->Action = TORCH_IS_ON;

		p->UpdateFlag |= TORCH_GO_ON;
	//	p->UpdateFlag &= TORCH_GO_OFF;
	}


	//no [directional] input
	if ( p->DirectionBit == 0 )
	{
		//go back to the old direction (no input == no change)
		p->DirectionBit = OldDirBit;

	} else { //there was some input
		
		//convert input to a 8directional dir
		p->DirectionAng = DIR_BIT_TO_DIR_ANG( p->DirectionBit );
		//convert 8dir dir to real angle
		p->FaceAng = DIR_ANG_TO_ANG( p->DirectionAng );
		
		//physiccly move
		p->x += DirAngChanges[ p->DirectionAng ][X] * PLAYER_MOVE_RATE;
		p->y += DirAngChanges[ p->DirectionAng ][Y] * PLAYER_MOVE_RATE;
	
		if (p->x < 0) p->x = 0;
		if (p->y < 0) p->y = 0;
		if (p->x >= MAP_W) p->x = MAP_W - 1;
		if (p->y >= MAP_H) p->y = MAP_H - 1;

		//update sprite movements
		p->UpdateFlag |= PLAYER_MOVE;
		
		//direction bit changed
		if ( p->DirectionBit != OldDirBit )	
			//updates sprite rotations
			p->UpdateFlag |= TORCH_ROT | PLAYER_ROT;
	}

	GameUpdateFlag |= TORCH_ROT;

}



void PlayerSpriteUpdate( aPlayer *p )
{
	//use the update flags to minimize the amount of things that need changing
	u16 UpdateFlag = p->UpdateFlag;
	s32 TorchAngDiff;
	//reset update flag, any changes will come into affect next time
	p->UpdateFlag = 0;


	if ( UpdateFlag & TORCH_GO_OFF )
	{
		//torch has gone off
		//sets all tiles on this bg to 0 (black)
		ClearTorchBg;
	} 
	if ( UpdateFlag & TORCH_GO_ON )
	{
		//set the torch on
		//sets the bg tiles in order from 0 > W*H
		ResetTorchBg();
	} 


	if ( UpdateFlag & TORCH_ROT || GameUpdateFlag & TORCH_ROT )
	{
		//rotate torch to new pos center of rotation is center of BG
		TorchAngDiff = AngDiff( p->FaceAng, p->TorchAng );
		if ( abs(TorchAngDiff) >= TORCH_TURN_RATE ) //else snaps to 8 dir ang
			TorchAngDiff /= TORCH_TURN_RATE;

		p->TorchAng += TorchAngDiff;
		p->TorchAng = roll_s32( p->TorchAng , 0, 360 );
		if ( p->TorchAng != p->FaceAng )
			//torch not in place yet, make it update next frame again
			p->UpdateFlag |= TORCH_ROT ;

		RotateTorch( p->TorchAng, (p->x)-CamScrollPixel(X), (p->y)-CamScrollPixel(Y) );
		//light source changed, update shadows
		GameUpdateFlag |= SHADOW_ROT ;
	}

	if ( UpdateFlag & PLAYER_ROT )
	{
		//center of rotation is center of BG
		//RotateSpr( p->Sprite, p->FaceAng );
	}

	//sprite's coord is 
	if ( UpdateFlag & PLAYER_MOVE || GameUpdateFlag & PLAYER_MOVE  )
	{
		//only updates anim etc if moved
		//UpdateSprite( p->Sprite );
		
		//move torch if player moves
		//scrollbackground( TORCH_BG, p->Sprite->Pos[X]-HALFSCREEN_W, p->Sprite->Pos[Y]-HALFSCREEN_H );
		//RotateTorch( p->TorchAng, (p->x)-CameraPixelLeft(), (p->y)-CameraPixelTop() );
		RotateTorch( p->TorchAng, (p->x)-CamScrollPixel(X), (p->y)-CamScrollPixel(Y) );
		
		//RotateTorch( p->TorchAng, 0, 0 );

		//our light source changed, force all shadows to update[later this tick]
		GameUpdateFlag |= SHADOW_MOVE ;
	}


}
