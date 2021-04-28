 #include "gfxutils.h"

void 
GFX_FontPrint(SDL_Surface * dst , SDL_Surface * fbmp , 
			int gw , int gh , u8 start , 
			char * buf , u32 max_buf ,
			int x , int y )
{
	SDL_Rect rsrc , rdst ; 
	u32 fbmp_nx ; 
	int ix , iy ; 
	u32 cnt = 0; 
	char * pb = buf ;
	
	ix = x ; 
	iy = y ; 
	fbmp_nx = fbmp->w / gw ;
	
	while( cnt < max_buf && *pb != '\0' ){
		
		if(*pb == '\n'){	//Saut de ligne
			ix = x ;
			iy += gw ;
		}else{
			if(isprint(*pb)){
				rsrc.x = ( ((*pb)-start)%fbmp_nx ) * gw ; 
				rsrc.y = (((*pb)-start)/fbmp_nx) * gh;
				rsrc.w = gw ;
				rsrc.h = gh ; 
				
				rdst.x = ix ; 
				rdst.y = iy ; 
				
				SDL_BlitSurface(fbmp , &rsrc , dst , &rdst);
				ix += gw;
			}
		}
		
		++pb ; 
		++cnt; 
	}
	
}			
