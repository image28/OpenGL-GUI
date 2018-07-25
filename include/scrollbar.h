struct scrollDef
{
	SDL_Rect area;
	SDL_Rect boxarea;

	struct colour frame_colour;
	struct colour bar_colour;

	int direction;
	int position;	
	int total;
	int frame;
	int zoom;
	int resize;
	int update;
	int id;
};

int DrawScrollBar(struct container *screen, struct scrollDef box );

