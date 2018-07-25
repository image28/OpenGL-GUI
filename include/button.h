#define MAXLEN 1000
#define MAXBTN 10

struct buttonDef
{
	SDL_Rect area;

	struct colour frame_colour;
	struct colour text_colour;
	struct colour background_colour;	

	GLuint *font;
	char text[1000];
	char *image;

	int frame;
	int justified;
	int zoom;
	int update;
	int hasimage;
	int hastext;
	int resize;
	int id;

	// BUTTONBOX ONLY
	int buttonbox;

	int border;
	int buttondown;
	int direction;
	int buttons;
	int selected[255];
	int buttonnum;
	int width;
	int height;
	int blank;
};

int click(SDL_Event event , SDL_Rect area);
int mouseover(SDL_Event event, SDL_Rect area);
int button(struct container *screen, struct buttonDef box, char text[1000], int selected);
int buttonbox(struct container *screen, char text[MAXBTN][MAXLEN], struct buttonDef box);

