#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"
#include "../core/tile_alloc.h"
#include "../core/math.h" //cos/sin
#include "../core/sprites.h"
#include "../core/animated_sprite.h"
#include "../core/keypad.h"
#include "../core/font.h"
#include "../core/collisions.h"

#include "main.h"
#include "game.h"
#include "tile_sets.h"

u32 fps_counter,game_fps;



int AgbMain(void)
{
	return main();
}

void init_interrupt(void)
{
	//Do Interrupt Setup
	REG_IME = 0x00;						// Disable interrupts 
	REG_INTERUPT = (u32)IRQHandler;		// Set interrupt proc address (IRQHandler) 
	REG_IE |= BIT00 | BIT05;			// Enable V-Blank and Timer 2 IRQs
	REG_DISPSTAT |= BIT03;				// Enable Display V-Blank IRQ also. 
	REG_IME = BIT00;					// Enable interrupts 

	//Enable timers
	REG_TM2CNT = FREQUENCY_256 | TIMER_IRQ | TIMER_ENABLE;
}



void RotateBg2( u16 Angle, s32 CenterX, s32 CenterY, u16 Zoom, u16 ScrollX, u16 ScrollY )
{
	CenterX = (CenterX * Zoom)>>8;
    CenterY = (CenterY * Zoom)>>8;

	REG_BG2X = ( (ScrollX<<8) - CenterY *SIN[Angle] - CenterX * COS[Angle] );
    REG_BG2Y = ( (ScrollY<<8) - CenterY *COS[Angle] + CenterX * SIN[Angle] );

    REG_BG2PA = (COS[Angle] * Zoom)>>8; //cos&sin are LUTs that are .8 fixed numbers
    REG_BG2PB = (SIN[Angle] * Zoom)>>8; //zoom is also fixed
    REG_BG2PC = (-SIN[Angle] * Zoom)>>8;
    REG_BG2PD = (COS[Angle] * Zoom)>>8;
}






int main(void)
{
	//required init code
	hide_all_backgrounds;
	init_interrupt();

	LevelInit();
	while (1)
		GameLoop();
}







///////////////////IRQHandler//////////////////
void IRQHandler(void)
{
	u16 Int_Flag; 

	REG_IME = 0x00;			// Disable interrupts 
	Int_Flag = REG_IF;		// Read the interrupt flags

	//If Timer IRQ, then output the current FPS and zero it out
	if((REG_IF & BIT05) == BIT05)
	{
		//WriteNum(0, 30, 0, 1, framesPerSecond, 0);
		game_fps = fps_counter;
		fps_counter = 0;
	}

	REG_IF = Int_Flag;		// Write back the interrupt flags 
	REG_IME = BIT00;		// Re-Enable interrupts 
	
}




inline void start_frame(void)
{
	//wait_for_vblank();
	wait_for_end_of_vblank();

	//update fps on-screen
	if ( DRAW_FPS )
		draw_text( VISIBLE_TILE_W-7,0,0,"fps%4d",game_fps);
}

inline void end_frame(void)
{
	process_anims();
	update_sprites();
	fps_counter++;

	wait_for_vblank();
	//wait_for_end_of_vblank();
	
}



// ** conversions ** 
//convert a DIR_BIT* to a DIR_ANG*
const u8 DirBitAsDirAng[ 16 ] = {
	DIR_ANG_NO,	// N/A
	DIR_ANG_NO,
	DIR_ANG_SO,
	DIR_ANG_NO,	// NS
	DIR_ANG_EO,
	DIR_ANG_NE,
	DIR_ANG_SE,
	DIR_ANG_SE,	// NSE
	DIR_ANG_WO,
	DIR_ANG_NW,
	DIR_ANG_SW,
	DIR_ANG_NO,	// NSW
	DIR_ANG_EO,	// EW
	DIR_ANG_NE,	// NEW
	DIR_ANG_SE,	// SEW
	DIR_ANG_NO,	// NSEW
};

const u16 DirAngAsDirBit[ DIR_ANG_COUNT ] = {
	DIR_BIT_NO ,
	DIR_BIT_NE ,
	DIR_BIT_EO ,
	DIR_BIT_SE ,
	DIR_BIT_SO ,
	DIR_BIT_SW ,
	DIR_BIT_WO ,
	DIR_BIT_NW ,
};

const u16 DirAngAsAng[ DIR_ANG_COUNT ] = {
	0 * DIR_ANG_GAP,
	1 * DIR_ANG_GAP,
	2 * DIR_ANG_GAP,
	3 * DIR_ANG_GAP,
	4 * DIR_ANG_GAP,
	5 * DIR_ANG_GAP,
	6 * DIR_ANG_GAP,
	7 * DIR_ANG_GAP,
};

const s8 DirAngChanges[ DIR_ANG_COUNT ][2] = {
	 0,	-1,	//NO
	 1,	-1,	//NE
	 1,	 0,	//EO
	 1,	 1,	//SE
	 0,	 1,	//SO
	-1,	 1,	//SW
	-1,	 0,	//WO
	-1,	-1,	//NW
};


//returns number from -180 to 180
s32 AngDiff( u16 ang_a, u16 ang_b )
{
	s32 s_ang[2];
	s32 diff;
	
	diff = ang_a - ang_b;

	while(diff > 180 )
		diff -= 360;
	while(diff < -180 )
		diff += 360;

	return diff;
}


