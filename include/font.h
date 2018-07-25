#define TEXTHEIGHT 11
#define TEXTWIDTH 10

struct labelDef 
{
	SDL_Rect area;

	char text[1000];

	struct colour frame_colour;
	struct colour text_colour;
	struct colour background_colour;

	int zoom;
	int update;
	int resize;
	int justify;
	int truncate;
};

int loadfont();
int drawLetter(struct container *screen, struct colour colour,SDL_Rect area, int letter, int zoom, int update);
int drawText(struct container *screen, struct colour colour, SDL_Rect area, char *text, int zoom, int truncate, int update);


int alphabet(struct container *screen, struct colour colour, SDL_Rect area, int zoom, int update);
