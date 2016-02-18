#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include "main.h"


#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"
#include "../core/sprites.h"



//player action/status flags
#define TORCH_IS_OFF	BIT(0) //torch is off
#define TORCH_IS_ON		BIT(1) //torch is on


// key, flag, move flag
#define UPDATE_INPUT_FLAG(f,k,m) 	if ( k ) f |= m
// compflag, newer flag, old flag, move flag
#define COMPARE_UPDATE_INPUT_FLAG(cf,nf,of,m)	if ( ((nf) & (m)) && !((of) & (m)) )	cf |= (m)
#define TORCH_INPUT_BIT (MOVE_BIT_ACT1)


//values
#define PLAYER_MOVE_RATE	4
#define TORCH_TURN_RATE		4




typedef struct {
	u16	InputFlag;		//input on
	u16	InputChangeFlag;//input x is now on
	u16	UpdateFlag;		//flags for sprite update
	u16	DirectionBit;	//bit of directional input
	u8	DirectionAng;	//0->8
	s32 FaceAng;		//0->360
	s32 TorchAng;		//independant from faceang for transition
	u16	Action;			//current player actions (non-directional)
	s32	x;				//position>>8
	s32	y;				//y pos >>8
	aSprite* Sprite;	//sprite addr
	aSprite* Shadow;	//sprite shadow addr
} aPlayer;






#endif
