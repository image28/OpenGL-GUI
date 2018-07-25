struct gridDef
{
	SDL_Rect area;
	
	struct colour frame_colour;
	struct colour grid_colour;
	
	int xdivide;
	int ydivide;
	int lines;
	int frame;
	int zoom;
	int resize;
	int update;
	int id;

};

int drawGrid(struct container *screen, struct gridDef box);


