struct frameDef
{
	SDL_Rect area;
	
	struct colour frame_colour;
	struct colour background_colour;

	int frametype;
	int zoom;
	int resize;
	int update;
};

void DrawFrame(struct container *screen, struct frameDef box );

