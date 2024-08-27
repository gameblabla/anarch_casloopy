/**
  @file main_32x.c

  This is an 32X implementation of the game front end. It can be used to
  compile a native executable or a transpiled JS browser version with
  emscripten.

  This frontend is not strictly minimal, it could be reduced a lot. If you want
  a learning example of frontend, look at another, simpler one, e.g. terminal.

  To compile with emscripten run:

  emcc ./main_sdl.c -s USE_SDL=2 -O3 --shell-file HTMLshell.html -o game.html

  by Miloslav Ciz (drummyfish), 2019

  Released under CC0 1.0 (https://creativecommons.org/publicdomain/zero/1.0/)
  plus a waiver of all other intellectual property. The goal of this work is to
  be and remain completely in the public domain forever, available for any use
  whatsoever.
*/
volatile void (*BiosVsync)(void) = (void (*)(void))0x6A5A;

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__)
  #define SFG_OS_IS_MALWARE 1
#endif

// #define SFG_START_LEVEL 1
// #define SFG_QUICK_WIN 1
// #define SFG_IMMORTAL 1
// #define SFG_ALL_LEVELS 1
// #define SFG_UNLOCK_DOOR 1
// #define SFG_REVEAL_MAP 1
// #define SFG_INFINITE_AMMO 1
// #define SFG_TIME_MULTIPLIER 512
// #define SFG_CPU_LOAD(percent) printf("CPU load: %d%\n",percent);
// #define GAME_LQ

// lower quality
#define SFG_FPS 20
#define SFG_RAYCASTING_SUBSAMPLE 3
//#define SFG_RESOLUTION_SCALEDOWN 2
#define SFG_DIMINISH_SPRITES 0
#define SFG_DITHERED_SHADOW 0
#define SFG_BACKGROUND_BLUR 0
#define SFG_RAYCASTING_MAX_STEPS 15
#define SFG_RAYCASTING_MAX_HITS 5
#define SFG_RAYCASTING_VISIBILITY_MAX_HITS 6
#define SFG_CAN_EXIT 0
#define SFG_DRAW_LEVEL_BACKGROUND 1

/*
  SDL is easier to play thanks to nice controls so make the player take full
  damage to make it a bit harder.
*/
#define SFG_PLAYER_DAMAGE_MULTIPLIER 1024

#define SDL_MUSIC_VOLUME 16

#define SDL_ANALOG_DIVIDER 1024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "loopy.h"
#include <stddef.h>
#include <string.h>

#include "game_constants.h"
#include "shared_objects.h"

#if 1
#define SFG_SCREEN_RESOLUTION_X 128
#define SFG_SCREEN_RESOLUTION_Y 112
#define SFG_RESOLUTION_SCALEDOWN 1
uint32_t framebuffer[(256*240)/4];
static inline void SFG_setPixel(int32_t x, int32_t y, int32_t colorIndex)
{
    // Calculate the index into the framebuffer, accounting for the spacing
    //uint32_t index = ((y << 1) * SFG_SCREEN_RESOLUTION_X) + x;
    int32_t index = (y << 8) + x;
    int32_t c = (uint32_t)((colorIndex << 8) | colorIndex);
    
    // Write the color index to the framebuffer for two consecutive lines
    ((int16_t*)framebuffer)[index] = c;
    ((int16_t*)framebuffer)[index + SFG_SCREEN_RESOLUTION_X] = c;
}
#endif


#include "game.h"
#include "sounds.h"

uint32_t ticks = 0;

//vu8 *framebuffer = (vu8* ) &MARS_FRAMEBUFFER;
//#define framebuffer VDP_BITMAP_VRAM2_8

/*
* Check the current SEGA Controllers for inputs, update player, direction
* , speed, and action accordingly.
*/
void handle_input()
{

}
/*
void SFG_clearScreen(uint8_t color)
{
	Hw32xScreenClear();
}*/

// now implement the Anarch API functions (SFG_*)

uint32_t SFG_getTimeMs()
{
  return ticks * 100;
}

void SFG_save(uint8_t data[SFG_SAVE_SIZE])
{
  /*FILE *f = fopen(SFG_SAVE_FILE_PATH,"wb");

  puts("SDL: opening and writing save file");

  if (f == NULL)
  {
    puts("SDL: could not open the file!");
    return;
  }

  fwrite(data,1,SFG_SAVE_SIZE,f);

  fclose(f);*/
}

uint8_t SFG_load(uint8_t data[SFG_SAVE_SIZE])
{/*
#ifndef __EMSCRIPTEN__
  FILE *f = fopen(SFG_SAVE_FILE_PATH,"rb");

  puts("SDL: opening and reading save file");

  if (f == NULL)
  {
    puts("SDL: no save file to open");
  }
  else
  {
    fread(data,1,SFG_SAVE_SIZE,f);
    fclose(f);
  }

  return 1;
#else
  // no saving for web version
  return 0;
#endif*/
}

void SFG_sleepMs(uint16_t timeMs)
{/*
#ifndef __EMSCRIPTEN__
  usleep(timeMs * 1000);
#endif*/
}



void SFG_getMouseOffset(int16_t *x, int16_t *y)
{
/*
#ifndef __EMSCRIPTEN__

#if !defined(__WIIU__)
  if (mouseMoved)
  {
    int mX, mY;

    SDL_GetMouseState(&mX,&mY);

    *x = mX - SFG_SCREEN_RESOLUTION_X / 2;
    *y = mY - SFG_SCREEN_RESOLUTION_Y / 2;

    SDL_WarpMouseInWindow(window,
      SFG_SCREEN_RESOLUTION_X / 2, SFG_SCREEN_RESOLUTION_Y / 2);
  }
#endif
  if (sdlController != NULL)
  {
    *x +=
      (SDL_GameControllerGetAxis(sdlController,SDL_CONTROLLER_AXIS_RIGHTX) + 
      SDL_GameControllerGetAxis(sdlController,SDL_CONTROLLER_AXIS_LEFTX)) /
      SDL_ANALOG_DIVIDER;

    *y +=
      (SDL_GameControllerGetAxis(sdlController,SDL_CONTROLLER_AXIS_RIGHTY) + 
      SDL_GameControllerGetAxis(sdlController,SDL_CONTROLLER_AXIS_LEFTY)) /
      SDL_ANALOG_DIVIDER;
  }
#endif
*/
}

void SFG_processEvent(uint8_t event, uint8_t data)
{
}


//Controller Buttons
#define P1_A 0x0100
#define P1_B 0x0800
#define P1_C 0x0400
#define P1_D 0x0200
#define P1_UP 0x0001
#define P1_DOWN 0x0002
#define P1_LEFT 0x0004
#define P1_RIGHT 0x0008
#define P1_DET 0x0001
#define P1_START 0x0002
#define P1_TL 0x0004
#define P1_TR 0x0008

uint32_t oldpad1, oldpad0;
uint32_t newpad1, newpad0;

int8_t SFG_keyPressed(uint8_t key)
{

	#define b(x) (newpad0 & P1_ ## x )
	#define b1(x) (newpad1 & P1_ ## x )
	switch (key)
	{
		case SFG_KEY_UP: return b1(UP); break;
		case SFG_KEY_RIGHT: 
		  return b1(RIGHT); break;
		case SFG_KEY_DOWN: 
		  return b1(DOWN); break;
		case SFG_KEY_LEFT: return b1(LEFT); break;
		case SFG_KEY_A: return b(TR); break;
		case SFG_KEY_B: return b(B); break;
		/*case SFG_KEY_C: return b(YELLOW); break;*/
		case SFG_KEY_JUMP: return b(C); break;
		/*case SFG_KEY_STRAFE_LEFT: return b(TL); break;
		case SFG_KEY_STRAFE_RIGHT: return b(TR); break;*/
		
		//case SFG_KEY_MAP: return b(MINUS); break;
		
		case SFG_KEY_CYCLE_WEAPON: return b(D); break;
		case SFG_KEY_MENU: return b(START); break;
	   /* case SFG_KEY_NEXT_WEAPON:
		  if (b(ZR))
			return 1;
		  else
		  return 0;
		  break;*/

		default: return 0; break;
	}

  #undef b
}
  
int running = 1;

static inline void *memcpy32(void* dest, const void * src, size_t n){
	uint32_t *d = dest;
	const uint32_t *s = src;
	
	for(; n; n--){
		*d++ = *s++;
	}
	return dest;
}

void *memcpy(void* dest, const void * src, size_t n){
	uint8_t *d = dest;
	const uint8_t *s = src;
	
	for(; n; n--){
		*d++ = *s++;
	}
	return dest;
}

void *memset8(void *dest, int c, size_t n){
	unsigned char *s = dest;
    for (; n; n--, s++) *s = c;
	return dest;
}

void *memset32(void *dest, int c, size_t n){
	uint32_t *s = dest;
    for (; n; n--, s++) *s = c;
	return dest;
}

void mainLoopIteration()
{

	if (!SFG_mainLoopBody())
		running = 0;

    // Store the previous frame's input state
    oldpad1 = newpad1;
    oldpad0 = newpad0;

    // Update the current input state
    newpad1 = IO_CONTROLLER1;
    newpad0 = IO_CONTROLLER0;
	
	memcpy32(VDP_BITMAP_VRAM2, framebuffer, (256*224)/4);

	
	ticks++;
}

uint8_t musicOn = 0;
// ^ this has to be init to 0 (not 1), else a few samples get played at start

/*
uint16_t audioBuff[SFG_SFX_SAMPLE_COUNT];
uint16_t audioPos = 0; // audio position for the next audio buffer fill
uint32_t audioUpdateFrame = 0; // game frame at which audio buffer fill happened

static inline int16_t mixSamples(int16_t sample1, int16_t sample2)
{
  return sample1 + sample2;
}


void audioFillCallback(void *userdata, uint8_t *s, int l)
{
  uint16_t *s16 = (uint16_t *) s;

  for (int i = 0; i < l / 2; ++i)
  {
    s16[i] = musicOn ?
      mixSamples(audioBuff[audioPos], SDL_MUSIC_VOLUME *
      (SFG_getNextMusicSample() - SFG_musicTrackAverages[SFG_MusicState.track]))
      : audioBuff[audioPos];

    audioBuff[audioPos] = 0;
    audioPos = (audioPos < SFG_SFX_SAMPLE_COUNT - 1) ? (audioPos + 1) : 0;
  }

  audioUpdateFrame = SFG_game.frame;
}
*/

void SFG_setMusic(uint8_t value)
{
  switch (value)
  {
    case SFG_MUSIC_TURN_ON: musicOn = 1; break;
    case SFG_MUSIC_TURN_OFF: musicOn = 0; break;
    case SFG_MUSIC_NEXT: SFG_nextMusicTrack(); break;
    default: break;
  }
}

void SFG_playSound(uint8_t soundIndex, uint8_t volume)
{
	/*
  uint16_t pos = (audioPos +
    ((SFG_game.frame - audioUpdateFrame) * SFG_MS_PER_FRAME * 8)) %
    SFG_SFX_SAMPLE_COUNT;

  uint16_t volumeScale = 1 << (volume / 37);

  for (int i = 0; i < SFG_SFX_SAMPLE_COUNT; ++i)
  {
    audioBuff[pos] = mixSamples(audioBuff[pos], 
      (128 - SFG_GET_SFX_SAMPLE(soundIndex,i)) * volumeScale);

    pos = (pos < SFG_SFX_SAMPLE_COUNT - 1) ? (pos + 1) : 0;
  }*/
}

void handleSignal(int signal)
{
  running = 0;
}

void Set_Pal(const uint8_t* topal) {
    // Initialize tempPalette to black
    int a = 0;
    for(unsigned int i = 0; i < 768; i+=3) {
        VDP_PALETTE[a] = color(topal[i]/8,topal[i+1]/8,topal[i+2]/8); // Assuming RGB color format, black
        a++;
    }
}




extern uint16_t terrain[];
const uint8_t cur_pal[768] = {0,0,0,2,3,2,11,13,11,37,33,32,76,78,76,130,132,130,202,211,202,
255,255,255,2,1,1,11,3,2,32,8,8,58,15,14,106,28,26,157,46,44,
237,69,67,255,108,106,2,2,1,14,8,4,32,19,8,67,39,17,106,69,26,
157,103,51,237,151,76,255,203,106,2,4,1,11,13,2,26,33,8,51,64,14,
85,103,32,143,165,44,202,237,76,255,255,118,1,4,1,6,13,2,11,36,8,
22,64,14,44,103,26,67,158,44,95,237,67,143,255,118,1,4,1,4,13,6,
8,33,14,17,64,32,32,103,51,44,158,85,67,237,118,118,255,171,1,4,4,
4,13,11,11,31,26,17,64,58,37,97,95,51,158,157,76,237,237,118,255,255,
1,1,2,4,6,11,8,13,32,14,28,58,32,53,95,51,82,157,76,119,237,
118,165,255,1,1,2,4,3,14,11,8,32,22,15,58,37,28,95,58,46,157,
85,64,237,130,108,255,2,1,4,8,3,14,26,8,32,51,15,58,85,28,106,
130,49,157,186,69,219,255,114,255,4,1,1,14,3,8,32,8,17,58,15,37,
106,28,67,157,46,95,237,69,157,255,108,202,6,0,0,17,0,0,37,0,1,
85,0,1,130,1,1,186,3,4,255,5,6,255,17,22,6,2,0,17,6,1,
37,15,1,76,28,1,130,46,1,186,69,6,255,103,6,255,132,22,2,7,0,
11,19,0,26,42,1,51,82,1,85,132,1,130,187,6,186,255,6,219,255,22,
0,7,0,1,19,0,2,42,1,2,82,1,11,132,1,17,187,4,26,255,8,
44,255,17,0,7,1,0,19,2,1,42,6,1,78,14,2,132,22,6,187,37,
2,255,51,17,255,85,0,7,6,0,19,17,0,42,44,1,78,76,4,125,118,
2,187,186,8,255,255,26,255,255,0,1,6,0,3,17,1,7,37,1,12,76,
4,26,118,1,36,186,8,53,255,17,82,255,1,0,6,1,0,17,1,1,37,
4,1,76,6,2,130,14,4,186,22,7,255,37,19,255,2,0,6,11,0,17,
26,0,44,44,1,85,85,1,130,118,5,186,171,7,255,202,19,255,6,0,1,
17,0,6,37,0,14,85,1,26,130,1,51,186,3,67,255,5,106,255,19,130,
6,0,0,17,0,0,37,0,0,67,0,0,118,0,0,171,1,0,237,1,0,
255,0,0,6,1,0,17,2,0,37,7,0,67,12,0,118,23,0,171,33,0,
237,49,0,255,69,1,4,7,0,14,19,0,32,39,0,51,73,0,95,119,0,
143,180,0,202,246,0,255,255,0,1,7,0,1,19,0,2,39,0,6,73,0,
8,119,0,8,180,0,17,246,0,32,255,1,1,7,0,0,19,0,0,39,0,
1,73,0,1,114,0,0,172,1,0,246,1,0,255,2,0,7,1,0,19,8,
0,39,14,0,73,26,0,114,44,0,172,67,0,246,106,0,255,130,0,2,6,
0,7,17,0,15,37,0,28,67,0,46,118,1,73,157,0,108,237,4,138,255,
0,0,6,0,0,17,1,0,37,0,1,67,1,1,118,0,2,171,1,2,237,
0,6,255,1,0,4,1,0,17,1,0,37,4,0,67,4,1,118,8,0,171,
14,0,237,17,1,255,6,0,6,11,0,22,26,0,37,51,0,76,85,0,118,
130,0,171,186,0,237,237,0,255,6,0,1,17,0,2,37,0,8,67,0,14,
118,0,22,171,0,37,237,1,51,255,1,67};

int main(int argc, char *argv[])
{
	maskInterrupts(0) ;

	// Don't forget to set control bit
	VDP_MODE = 0b00010000;
	
    //Screen display mode
    VDP_DISPMODE = 0x00;

    //Set bitmap render mode to 4bit 512x512
    //0x0 sets bitmap render mode to 8bit 256x256, along with a second 256x bitmap underneath.
    VDP_BM_CTRL = 0x0001;

    //Backdrop A/B refers to the "screen buffer"
    //Backdrop refers to solid fill color for each.
    VDP_BACKDROP_A = color(0,0,0);
    VDP_BACKDROP_B = color(0,0,31);
    
    //Color PRIO enables/disables the A/B screens
    VDP_COLORPRIO = 0b01000000;

    // Which bg/obj/bm layers to show
    VDP_LAYER_CTRL = 0b1010101001000110;
    VDP_OBJ_CTRL = 0b000000100000000;
    VDP_BG_CTRL = 0b0000000000001111;
	
	//These establish the bitmaps to cover the screen so that I can just blit the to the screen how I want adjust if you're using smaller bitmaps
	//Set X/Y Screen of the bitmap sprite
	VDP_BMn_SCREENX[0] = 0;
	VDP_BMn_SCREENY[0] = 0;

	//Width/Height of bitmap sprite
	VDP_BMn_WIDTH[0] = 255;
	VDP_BMn_HEIGHT[0] = 511;

	// Set X/Y Screen of the bitmap sprite
	/*VDP_BMn_SCREENX[1] = 0;
	VDP_BMn_SCREENY[1] = 0;

	// Width/Height of bitmap sprite
	VDP_BMn_WIDTH[1] = 255;
	VDP_BMn_HEIGHT[1] = 255;	*/

	Set_Pal(cur_pal);
	memset32(VDP_BITMAP_VRAM2, 0x0, (256*224)/4);
	
	SFG_init();
  
	running = 1;

	while (running)
	{
		mainLoopIteration();
		BiosVsync();
		
	}

  return 0;
}
