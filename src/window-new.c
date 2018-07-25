
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/font.h"
#include "../include/window.h"
#include "../include/frame.h"
#include "../include/popup.h"
#include "../include/button.h"

// title/shading on any of the four sides

void window(struct container *screen, struct winDef box)
{
	struct frameDef box2;
	struct frameDef box3;

	// box.shaded and box.titlebar should be autofilled

	box2.update=0;	
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box2.area.x=box.titlebar.x;
	box2.area.w=box.titlebar.w;
	box2.area.y=box.titlebar.y;
	box2.area.h=box.titlebar.h;

	box3.update=0;	
	box3.zoom=1;
	box3.frametype=0;

	box3.frame_colour.R=box.frame_colour.R;
	box3.frame_colour.G=box.frame_colour.G;
	box3.frame_colour.B=box.frame_colour.B;

	box3.area.x=box.area.x;
	box3.area.w=box.area.w;
	box3.area.y=box.area.y;
	box3.area.h=box.area.h;

	if ( box.bar )
	{

		FillRect(screen, box.titlebar_colour, box.titlebar, 0);
		// draw title bar if there is one
		DrawFrame(screen,box2);
		
		drawText(screen, box.text_colour, box.title_text, box.title, 1,1, 0);

		// CHECK IF WINDOW IS SHADED
		if ( box.shade )
		{
			// CHECK IF THERE IS A BORDER
			if ( box.border )
			{
				box3.area.x=box.shaded.x+2;
				box3.area.w=box.shaded.w+1;
				box3.area.y=box.shaded.y+2;
				box3.area.h=box.shaded.h+2;
			
				DrawFrame(screen,box3);
			}
		}else{
			// CHECK IF THERE IS A BORDER
			if ( box.border )
			{
				box3.area.x=box.area.x+2;
				box3.area.w=box.area.w+1;
				box3.area.y=box.area.y+2;
				box3.area.h=box.area.h+2;
	
				DrawFrame(screen,box3);

			}

			// BLIT WINDOW CONTENT TO WINDOW	
			SDL_BlitSurface(box.content.image, NULL, screen->image, &box.content.area);
		
		}
		
	}else{
		// CHECK IF THERE IS A BORDER
		if ( box.border )
			DrawFrame(screen,box3);

		// BLIT WINDOW CONTENT TO WINDOW	
		SDL_BlitSurface(box.content.image, NULL, screen->image, &box.area);
	}
	
	// CHECK WEATHER TO UPDATE
	if ( box.update )
		SDL_UpdateRects(screen->image, 1, &box.area);

}

void moveWindow(struct container screen, SDL_Event event, struct winDef *box)
{
	char popupText[10][1000]={{"To top\0"},{"Raise\0"},{"Lower\0"},{"To bottom\0"},{"(un)Shade\0"},{"close\0"}};

	if ( ! box->moving ) 
	{

		if ( mouseover(event,box->titlebar) )
			box->shade=0;
	
		if ( ! box->shade )
		{
			if ( ! mouseover(event,box->area) )
			{
				//box->shade=1;
			}
		}
	}else{
		if  ( ( event.motion.x > 0 ) && ( event.motion.x < screen.area.w ) ) 
		{

			if ( ( event.motion.y > 0 ) && ( event.motion.y < screen.area.h ) )
			{
			box->area.x=box->area.x+(event.motion.x-box->prevpos.x);
			box->area.w=box->area.w+(event.motion.x-box->prevpos.x);
			box->area.y=box->area.y+(event.motion.y-box->prevpos.y);
			box->area.h=box->area.h+(event.motion.y-box->prevpos.y);

			box->titlebar.x=box->titlebar.x+(event.motion.x-box->prevpos.x);
			box->titlebar.w=box->titlebar.w+(event.motion.x-box->prevpos.x);
			box->titlebar.y=box->titlebar.y+(event.motion.y-box->prevpos.y);
			box->titlebar.h=box->titlebar.h+(event.motion.y-box->prevpos.y);

			box->title_text.x=box->area.x+15;
			box->title_text.y=box->area.y+15;
			box->title_text.w=box->area.w-35;
			box->title_text.h=box->area.h+30;

			box->content.area.x=box->area.x+5;
			box->content.area.y=box->area.y+32;
			box->content.area.w=box->area.w-10;
			box->content.area.h=box->area.h-10;

			box->shaded.x=box->area.x;
			box->shaded.y=box->area.y;
			box->shaded.w=box->area.w;
			box->shaded.h=box->area.y+30;

			box->prevpos.x=event.motion.x;
			box->prevpos.y=event.motion.y;
			}
		}
	}

	switch( event.type ) 
	{
			case SDL_MOUSEBUTTONDOWN:
				box->focus=0;

				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					if ( ! box->moving )
					{
						if ( click(event,box->titlebar) )
						{
							box->moving=1;
							box->shade=0;

							if ( ( ( event.motion.x > 0 ) && ( event.motion.x < screen.area.w ) ) && ( ( event.motion.y > 0 ) && ( event.motion.y < screen.area.h ) ) )
							{
								box->prevpos.x=event.motion.x;
								box->prevpos.y=event.motion.y;
							}
						}

						if ( click(event,box->area) )
						{
							focus=1;
						}
					}
				}
				/*else if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					popup->area.x=event.button.x;
					popup->area.y=event.button.y;
					popup->area.w=event.button.x+popup->width;
					popup->area.h=event.button.y+popup->height;

					//buttonbox(&screen,popupText,*popup);
					popupUpdate2(event,&popup);		
				}*/
			break;

			case SDL_MOUSEBUTTONUP:
				if ( box->moving )
					box->moving=0;

				/*if ( popup->buttondown )
				{
					// run code for popup
					// raise, lower, totop, tobottom, (un)shade, close
				}*/
			break;

		}

}

void initWindow( struct winDef *box)
{
	box->titlebar.x=box->area.x+4;
	box->titlebar.y=box->area.y+4;
	box->titlebar.w=box->area.w-1;
	box->titlebar.h=box->area.y+30;

	box->title_text.x=box->area.x+15;
	box->title_text.y=box->area.y+15;
	box->title_text.w=box->area.w-35;
	box->title_text.h=box->area.h+30;

	box->content.area.x=box->area.x+5;
	box->content.area.y=box->area.y+32;
	box->content.area.w=box->area.w-box->area.x-7;
	box->content.area.h=box->area.h-box->area.y-32;

	box->shaded.x=box->area.x;
	box->shaded.y=box->area.y;
	box->shaded.w=box->area.w-1;
	box->shaded.h=box->area.y+31;

	box->content.image=SDL_CreateRGBSurface(SDL_HWSURFACE,box->area.w-box->area.x-7,box->area.h-box->area.y-32,32,0,0,0,0);
}

void resizeWindow( struct winDef *window, SDL_Rect newsize)
{
}