#ifndef GAME_MAIN_H
#define GAME_MAIN_H



#include "../core/gba.h"



extern const u16 BlankMap[ 64*64 ];


#define DRAW_FPS 1


//staringmonkeys timer defines
#define REG_TM0D       *(volatile u16*)0x4000100		//Timer 1 Data
#define REG_TM0CNT     *(volatile u16*)0x4000102		//Timer 1 Control
#define REG_TM1D       *(volatile u16*)0x4000104		//Timer 2 Data
#define REG_TM1CNT     *(volatile u16*)0x4000106		//Timer 2 Control
#define REG_TM2D       *(volatile u16*)0x4000108		//Timer 3 Data
#define REG_TM2CNT     *(volatile u16*)0x400010A		//Timer 3 Control
#define REG_TM3D       *(volatile u16*)0x400010C		//Timer 4 Data
#define REG_TM3CNT     *(volatile u16*)0x400010E		//Timer 4 Control
/////////////////Bits////////////////
#define BIT00 1
#define BIT01 2
#define BIT02 4
#define BIT03 8
#define BIT04 16
#define BIT05 32
#define BIT06 64
#define BIT07 128
#define BIT08 256
#define BIT09 512
#define BIT10 1024
#define BIT11 2048
#define BIT12 4096
#define BIT13 8192
#define BIT14 16384
#define BIT15 32768
///////////////////Definitions////////////////////
#define FREQUENCY_0		0x00
#define FREQUENCY_64	BIT00
#define FREQUENCY_256	BIT01
#define FREQUENCY_1024	BIT00 | BIT01

#define TIMER_CASCADE	BIT02
#define TIMER_IRQ		BIT06
#define TIMER_ENABLE	BIT07


#define REG_INTERUPT   *(volatile u32*)0x3007FFC		//Interrupt Register






#define BIT(n) (1<<n)

//input bits
#define MOVE_BIT_UP		BIT00 //bits to store input
#define MOVE_BIT_DOWN	BIT01
#define MOVE_BIT_LEFT	BIT02
#define MOVE_BIT_RIGHT	BIT03
#define MOVE_BIT_ACT1	BIT04
#define MOVE_BIT_ACT2	BIT05
#define MOVE_BIT_ACT3	BIT06
#define MOVE_BIT_ACT4	BIT07

//dirs bits
#define DIR_BIT_NO		BIT00 //bits to store directions
#define DIR_BIT_SO		BIT01
#define DIR_BIT_EO		BIT02
#define DIR_BIT_WO		BIT03
#define DIR_BIT_NE		( DIR_BIT_NO | DIR_BIT_EO )
#define DIR_BIT_SE		( DIR_BIT_SO | DIR_BIT_EO )
#define DIR_BIT_NW		( DIR_BIT_NO | DIR_BIT_WO )
#define DIR_BIT_SW		( DIR_BIT_SO | DIR_BIT_WO )

//limited angle dirs
#define DIR_ANG_NO		0 //directions from 0 to 8
#define DIR_ANG_NE		1
#define DIR_ANG_EO		2
#define DIR_ANG_SE		3
#define DIR_ANG_SO		4
#define DIR_ANG_SW		5
#define DIR_ANG_WO		6
#define DIR_ANG_NW		7
#define DIR_ANG_COUNT	8

#define DIR_ANG_GAP ( 360/DIR_ANG_COUNT )



extern const s8 DirAngChanges[ DIR_ANG_COUNT ][2];
extern const u16 DirAngAsAng[ DIR_ANG_COUNT ];
extern const u16 DirAngAsDirBit[ DIR_ANG_COUNT ];
extern const u8 DirBitAsDirAng[ 16 ];



//directional conversions
#define DIR_BIT_TO_DIR_ANG(db)	( DirBitAsDirAng[db] )
#define DIR_ANG_TO_DIR_BIT(da)	( DirAngAsDirBit[da] )
#define DIR_ANG_TO_ANG(da)		( DirAngAsAng[da] ) // ds*DIR_ANG_GAP
#define ANG_TO_DIR_ANG(a)		( a/DIR_ANG_GAP )
#define DIR_BIT_TO_ANG(db)		( DIR_ANG_TO_ANG( DIR_BIT_TO_DIR_ANG(db) ) )
#define ANG_TO_DIR_BIT(a)		( DIR_ANG_TO_DIR_BIT( ANG_TO_DIR_ANG(a) ) )












void init_interrupt(void);
void IRQHandler(void);
inline void start_frame(void);
inline void end_frame(void);
s32 AngDiff( u16 ang_a, u16 ang_b );




#endif
