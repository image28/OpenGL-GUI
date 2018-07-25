
#include "stdafx.h"


/*
int textarea(struct container *screen, struct colour colour, SDL_Rect area, int xscroll, int yscroll)
{
	// Varables
	FILE *test;
	int linesOnScreen=0;
	int linesTotal=0;
	int linesVisibleStart=0;
	int linesVisibleEnd=0;
	int charsVisibleStart=0;
	int charsVisibleEnd=0;

	// File opening
	if ( ( test=fopen("test.txt","r") ) == NULL ); exit(-2);

	// draw the frame
	DrawFrame(screen,colour,area);

	// add space between frame and console text
	area.w=area.w-5;
	area.h=area.h-5;
	area.x=area.x+5;
	area.y=area.y+5;

	// draw the scrollbars

	// add space between scrollbars and console text
	area.h=(area.h-SCROLLBARHEIGHT)-5;
	area.w=(area.w-SCROLLBARWIDTH)-5;

	// read in how many lines there are total
	// read in the max charsacross in the file and setup the horz. scroll

	// calculate how many lines you can fit on a screen
	linesOnScreen=area.h-area.y/(TEXTHIGHT+2);
	// calculate which lines are visible on the screen
	linesVisibleStart=(linesTotal-linesOnScreen)-yscroll;
	linesVisibleEnd=linesTotal-yscroll;
	// calculate which chars are visible on the screen
	charsVisibleStart=xscroll;
	charsVisibleEnd=TEXTWIDTH+2+xscroll; // FIX THIS

	// draw the text to the surface

	fseek(test,linesVisibleStart*1000,SEEK_SET);

	for(d=linesVisibleStart; d < linesVisibleEnd; d++)
	{
		//fseek(test,d*1000+charsVisibleStart,SEEK_SET);
		fread(&line,1,1000,test);
		for(e=charsVisibleStart; e < charsVisibleEnd; e++)
		{
			// FIX THIS LINE
			DrawChar(screen,colour,area.x+((e-charsVisibleStart)*12),area.y+((d-linesVisibleStart)*12),letter); 
		}
	}

	// 

	fclose(test);
}
*/

