int numberDraw(struct container *screen, struct entryDef entry);
int numberbox(struct container *screen, struct entryDef entry, int entries,char *entryText);
int numberUpdate(struct container *screen, SDL_Event event, struct entryDef *entry);
void numberboxUpdate(struct container *screen, SDL_Event event, struct entryDef *entry, int entries,char *entryText);

