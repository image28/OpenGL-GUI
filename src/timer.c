//#if SDL_VERSION_ATLEAST(2,0,0)
	/* SDL 2.0 code */
#include "stdafx.h"
#include <SDL\SDL.h>

//#else
	/* SDL 1.2 code */
//	#include <SDL/SDL.h>
//#endif

int get_ticks(int startTicks)
{
	//Return the current time minus the start time
	return SDL_GetTicks() - startTicks;
}
