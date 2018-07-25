#ifdef __APPLE__
	#include <SDL\SDL_mixer.h>
#else
	#include <SDL\SDL_mixer.h>
#endif

int playSFX(Mix_Chunk *sound, int *channels);
