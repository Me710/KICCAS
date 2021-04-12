#ifndef __GFXUTILS_H__
#define __GFXUTILS_H__
#include "stdinc.h"
#include <SDL/SDL.h>

void GFX_FontPrint(SDL_Surface * dst , SDL_Surface * fbmp , 
			int glyph_w, int glyph_h, u8 start , 
			char * buf , u32 max_buf , 
			int x , int y);
			
#endif //__GFXUTILS_H__
