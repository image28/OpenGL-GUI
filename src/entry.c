
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/window.h"
#include "../include/entry.h"
#include "../include/frame.h"

int entryWinSet(struct winDef window, struct entryDef entry, SDL_Event *event);
int entryWinUnSet(struct winDef window, struct entryDef entry, SDL_Event *event);

#define TEXTWIDTH 10
#define MAXCHARS 20
#define TEXTHEIGHT 10

int entryDraw(struct container *screen, struct entryDef entry)
{
	SDL_Rect temp;
	struct colour blinkcolour;
	struct frameDef box2;

	blinkcolour.R=0;
	blinkcolour.G=0;
	blinkcolour.B=0;

	int x;
	int y;
	int d;
	int e;
	int f;

	box2.update=0;
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=entry.frame_colour.R;
	box2.frame_colour.G=entry.frame_colour.G;
	box2.frame_colour.B=entry.frame_colour.B;

	box2.area.x=entry.area.x;
	box2.area.y=entry.area.y;
	box2.area.w=entry.area.w;
	box2.area.h=entry.area.h;

	temp.h=entry.area.y+TEXTHEIGHT+10;
	temp.w=entry.area.x+(MAXCHARS*TEXTWIDTH)+10;

	//ClearSurface(screen->image,area,0);

	// Draw Frame
	if ( entry.border )
		DrawFrame(screen, box2);

	temp.x=entry.area.x+5;
	temp.y=entry.area.y+5;
	temp.w=entry.area.w-5;
	temp.h=entry.area.h-5;

	// Draw all text 
	for ( f=0 ; f < strlen(entry.data); f++ )
	{
			if ( f < entry.maxlength )
			{
				// draw a character 
				putText(screen, &*(entry.data + f), entry.font,temp.x,temp.y,temp.w,temp.h);

				// next character
				temp.x=temp.x+(TEXTWIDTH+2); //entry.area.x+5+((TEXTWIDTH+2)*(f+1));
			}

			if ( *(entry.data+f) == 13 )
			{
				if ( temp.y+12 < entry.area.h )
				{
					temp.y=temp.y+12;
					temp.h=temp.h+12;
					temp.x=entry.area.x+5;
					temp.w=entry.area.x+17;	
				}

				//entry.maxlength = ((entry.area.w/12)*(entry.area.h/12))-(entry.area.w-(f-(f/(entry.area.w/12)));
			}

			// next line 
			if ( (temp.x+12) > entry.area.w )
			{
				if ( entry.wrap )
				{
					if ( temp.y+12 < entry.area.h )
					{
						temp.y=temp.y+12;
						temp.h=temp.h+12;
						temp.x=entry.area.x+5;
						temp.w=entry.area.x+17;
					}else{ 
						entry.maxlength=f;
					}
				}else{
					entry.maxlength=f;
				}
			}

	}

	entry.area.h=entry.area.h+10;

	// update surface
	if ( entry.update )
		SDL_UpdateTexture(screen->image, 1, &entry.area,NULL);
}

int entrybox(struct container *screen, struct entryDef entry, int entries, char *entryText)
{
	int count=0;
	char text[1000];
	int d=0;
	int h;

	h=entry.area.h-entry.area.y;

	while ( count < entries )
	{
		for(d=count*entry.maxlength; d < ((count*entry.maxlength)+entry.maxlength); d++)
		{
			entry.data[d-(count*entry.maxlength)]=*(entryText+d);
		}entry.data[d]='\0';

		entryDraw(screen,entry);
		count++;

		entry.area.y=entry.area.y+h;
		entry.area.h=entry.area.h+h;
	}

	if ( entry.update )
		SDL_UpdateTexture(screen->image, 1, &entry.area,NULL);
}

int entryWinSet(struct winDef window, struct entryDef entry, SDL_Event *event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if ( 0 )//click(event,addArea(window.content.area,entry.area)) )
		{
			event->button.x = event->button.x+window.content.area.x;
			event->button.y = event->button.y+window.content.area.y;

			event->motion.x = event->motion.x+window.content.area.x;
			event->motion.y = event->motion.y+window.content.area.y;
		} 
	}
}

int entryWinUnSet(struct winDef window, struct entryDef entry, SDL_Event *event)
{
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if ( click(event,entry.area) )
		{
			event->button.x = event->button.x-window.content.area.x;
			event->button.y = event->button.y-window.content.area.y;

			event->motion.x = event->motion.x-+window.content.area.x;
			event->motion.y = event->motion.y-window.content.area.y;
		} 
	}
}

int entryUpdate(struct container *screen,SDL_Event event, struct entryDef *entry)
{
	int d=0;
	int e=0;

	entry->length=strlen(entry->data);
	
	
	if ( event.type == SDL_MOUSEBUTTONDOWN )
	{
		entry->hasfocus=0;

		if ( click(event,entry->area) ) // have to check if inside a window here
		{
			entry->hasfocus=1;
		}
	}
	

	if ( entry->hasfocus > 0 )
	{
	switch( event.type ) 
	{
		case SDL_KEYDOWN:
			entry->keydown=1;
		break;

		case SDL_KEYUP:
			if ( entry->keydown )
			{
				switch( event.key.keysym.sym )
				{
					case SDLK_HOME:
						entry->pos=0;
					break;
	
					case SDLK_END:
						entry->pos=entry->length;
					break;

					// delete
					case SDLK_DELETE:	
						if ( entry->pos < strlen(entry->data) )
						{
							if ( *(entry->data+0) != '\0' )
							{
								for(d=entry->pos; d < entry->length; d++)
								{
									e=d+1;
									*(entry->data+d)=*(entry->data+e);
								}

								*(entry->data+entry->length)='\0';

								entry->length--;
							}
						}
					break;

					// backspace
					case SDLK_BACKSPACE:
						if ( entry->pos > 0 )
						{
							for(d=entry->pos; d < strlen(entry->data); d++)
							{
								e=d-1;
								*(entry->data+e)=*(entry->data+d);
							}

							e=entry->length-1;
							*(entry->data+e)='\0';

							entry->length--;	
							entry->pos--;
						}					
					break;

					// arrow left
					case SDLK_LEFT:
						if ( entry->pos > 0 )
							entry->pos--;
					break;

					// arrow right
					case SDLK_RIGHT:
						if ( entry->pos < strlen(entry->data) )
							entry->pos++;
					break;
						
					case SDLK_TAB:
						if ( entry->hasfocus > 1 )
						{
							entry->hasfocus++;
							entry->pos=0;
						}
					break;

						// (a-z,A-Z,0-9)
					default:
						if ( entry->length < entry->maxlength)
						{
							for(d=entry->length; d >= entry->pos+1; d--)
								*(entry->data+d)=*(entry->data+d-1);

							*(entry->data+entry->pos)=event.key.keysym.sym;
							*(entry->data+(strlen(entry->data)+1))='\0';

							entry->pos++;
							entry->length++;
						}

							
					break;

				}

				entry->keydown=0;
			}	
		break;

	}

	}

	//entryDraw(screen,entry);
}

void entryboxUpdate(struct container *screen, SDL_Event event, struct entryDef *entry, int entries, char *entryText)
{
	
	int h=0;
	int count2=0;
	int d=0;

	h=entry->area.h-entry->area.y;

	while ( count2 < entries )
	{
		if ( event.type == SDL_MOUSEBUTTONDOWN )
		{
			if ( click(event,entry->area) )
			{
				entry->hasfocus=count2+2;
				entry->pos=0;
			}
			
		}

		if ( entry->hasfocus == count2+2 )
		{
			
			for(d=count2*entry->maxlength; d < ((count2*entry->maxlength)+entry->maxlength); d++)
			{
				entry->data[d-(count2*entry->maxlength)]=*(entryText+d);
			}entry->data[d]='\0';

			entry->length=strlen(entry->data);

			entryUpdate(screen,event,entry);

			for(d=count2*entry->maxlength; d < ((count2*entry->maxlength)+entry->maxlength); d++)
			{
				*(entryText+d)=entry->data[d-(count2*entry->maxlength)];
			}
		}

		entry->area.y=entry->area.y+h;
		entry->area.h=entry->area.h+h;

		count2++;
	}

	entry->area.y=entry->area.y-(entries*h);
	entry->area.h=entry->area.h-(entries*h);
	
	if ( entry->update )
		SDL_UpdateTexture(screen->image, 1, &entry->area,NULL);
}

