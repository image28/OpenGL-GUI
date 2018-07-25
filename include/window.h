struct winDef
{
	SDL_Rect area;
	SDL_Rect titlebar;
	SDL_Rect title_text;
	SDL_Rect prevpos;
	SDL_Rect shaded;
	struct colour colour;
	struct colour text_colour;
	struct colour background_colour;
	struct colour frame_colour;	
	struct colour titlebar_colour;
	struct container content;
	//struct buttonDef popup;
	unsigned char title[1000];
	GLuint *font;
	int lock;
	int title_side;
	int window;
	int bar;
	int shade;
	int moving;
	int border;	
	int resize;
	int resizing;
	int close;
	int iconify;
	int sticky;
	int hasfocus;
	int zoom;
	int update;
	int layer;
	int active;
	int visible;
	int id;
};


//void window(struct container *screen, struct colour colour,  SDL_Rect area,struct container *content, char name[1000], int shaded, int titlebar, int border, int close, int iconify, int zoom, int update );
void window(struct container *screen, struct winDef window);
void initWindow( struct winDef *window);
void resizeWindow( SDL_Event event, struct winDef *window);
void moveWindow(struct container screen, SDL_Event event, struct winDef *window);
int orderStack(struct winDef box[255], int *stacking,int windows);
int windowStack(struct container *screen, struct winDef box[255], int stacking[255], int windows);

