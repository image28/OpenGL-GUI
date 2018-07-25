struct entryDef
{
	SDL_Rect area;

	struct colour text_colour;
	struct colour background_colour;
	struct colour frame_colour;	

	GLuint *font;
	unsigned char data[1000];

	int id;
	int keydown;
	int border;
	int hasfocus;
	int zoom;
	int update;
	int length;
	int pos;
	int resize;
	int maxlength;
	int wrap;
	int blink;

	// ENTRYBOX ONLY
	int entrybox;

	int entries;
	char *entry_text;
};

int entryDraw(struct container *screen, struct entryDef entry);
int entrybox(struct container *screen, struct entryDef entry, int entries,char *entryText);
int entryUpdate(struct container *screen, SDL_Event event, struct entryDef *entry);
void entryboxUpdate(struct container *screen, SDL_Event event, struct entryDef *entry, int entries,char *entryText);
int entryWinSet(struct winDef window, struct entryDef entry, SDL_Event *event);
