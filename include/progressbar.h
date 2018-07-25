struct progressDef
{
	SDL_Rect area;

	struct colour frame_colour;
	struct colour bar_colour;

	char data[1000];

	int zoom;	
	int pos;
	int frame;
	int update;	
	int resize;
	int text;
};

int progress(struct container *screen, struct progressDef box);

