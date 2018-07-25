struct checkDef
{
	SDL_Rect area;
	
	struct colour text_colour;
	struct colour frame_colour;
	struct colour box_colour;
	struct colour x_colour;

	GLuint *font;
	char text[1000];

	int frame;
	int justified;
	int themed;
	int clicked;
	int resize;
	int zoom;
	int update;
	int id;

	// CHECK/OPTION BOX ONLY
	struct colour border_colour;

	int checkbox;

	int selected[255];
	int options;
	int border;
	int direction;

};

int check(struct container *screen, struct checkDef box, char text[1000], int selected);
int checkbox(struct container *screen, char text[10][10], struct checkDef box);
void checkboxUpdate(SDL_Event event, struct checkDef *box);
void checkUpdate(SDL_Event event, struct checkDef *box);


