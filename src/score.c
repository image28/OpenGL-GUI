#ifdef __APPLE__
	#include <SDL.h>
	#include <OpenGL/gl.h>
#else
//	#if SDL_VERSION_ATLEAST(2,0,0)
		/* SDL 2.0 code */
		#include <SDL.h>
	//#else
		/* SDL 1.2 code */
	//	#include <SDL/SDL.h>
	//#endif
	#include <GLES/gl.h>
#endif
#include "../include/container.h"
#include "../include/draw.h"
#include "../include/score.h"


int newAwardFile(int levels, struct goals *award)
{
	FILE *output;
	int d=0;
	int e=0;
    char filename[1024];
	
#ifdef _WIN32
	output=fopen(".awards","wb");
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.awards");
    
    system("mkdir ~/.silverspeed");
    output=fopen(filename,"wb");
#endif
    
	for(d=0;d<levels+1;d++)
	{
		fwrite(&award[d],1,sizeof(goals),output);
	}

	fclose(output);
}

int resetAwards(struct goals *award)
{
    int d=0;
    int e=0;
    int l=0;
    
    for ( d=0;d<13;d++)
    {
        for(e=0;e<3;e++)
        {
            for(l=0;l<4;l++)
            {
                award[d].awards[e][l]=0;
            }
        }
    }
    
}

int mergeAwards(struct goals *gameAward, struct goals *finalAward, int level, int difficulty)
{
    int d=0;
    
    for(d=0;d<4;d++)
    {
        if ( gameAward[level].awards[difficulty][d] == 1 )
        {
            finalAward[level].awards[difficulty][d]=1;
        
        }
    }
    
}

int saveAwards(int levels, struct goals *award)
{
	FILE *output;
	int d=0;
    char filename[1024];

#ifdef _WIN32
    strcpy(filename,".awards");

	if ( ( output=fopen(filename,"wb") ) == NULL )
	{
		printf("Could not save awards file\n");
		exit(-4);
	}
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.awards");
    
	if ( ( output=fopen(filename,"wb") ) == NULL )
	{
		printf("Could not save awards file\n");
		exit(-4);
	}
#endif

	for(d=0;d<levels+1;d++)
	{
 
		fwrite(&award[d],1,sizeof(goals),output);
	}

	fclose(output);
}

int loadAwards(int levels, struct goals *award)
{
	FILE *input;
	int d=0;
    char filename[1024];

#ifdef _WIN32
    strcpy(filename,".awards");

	if ( ( input=fopen(filename,"rb") ) == NULL )
	{
        printf("Adding an awards file %s\n", filename);
		newAwardFile(levels, award);
		if ( ( input=fopen(filename,"rb") ) == NULL )
		{
			printf("Could not create awards file\n");
			exit(-4);
		}
	}
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.awards");
    
	if ( ( input=fopen(filename,"rb") ) == NULL )
	{
        printf("Adding an awards file %s\n", filename);
		newAwardFile(levels, award);
		if ( ( input=fopen(filename,"rb") ) == NULL )
		{
			printf("Could not create awards file\n");
			exit(-4);
		}
	}
#endif 
    
	for(d=0;d<levels+1;d++)
	{
		fread(&award[d],1,sizeof(goals),input);
	}

	fclose(input);
}



int newHighScoreFile(struct hstable *score)
{
    FILE *output;
    int d=0;
    int e=0;
    char filename[1024];
 
#ifdef _WIN32
    output=fopen(".highscores","wb");
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.highscores");
 
    system("mkdir ~/.silverspeed");
    output=fopen(filename,"wb");
#endif
 
	strcpy(score[9].name,"CKM");
	score[9].score=100;

	for(d=9;d>0;d--)
	{
		strcpy(score[d-1].name,"CKM\0");
		score[d-1].score=score[d].score*2;
	}

	for(d=0;d<10;d++)
	{
		fwrite(&score[d],1,sizeof(hstable),output);
	}

	fclose(output);
}

int loadHighScore(struct hstable *score)
{
	FILE *input;
	int d=0;
    char filename[1024];
    
#ifdef _WIN32
    if ( ( input=fopen(".highscores","rb") ) == NULL )
	{
        printf("Adding an highscores file %s\n", filename);
		newHighScoreFile(score);
		if ( ( input=fopen(".highscores","rb") ) == NULL )
		{
			printf("Could not create highscores file\n");
			exit(-4);
		}
	}
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.highscores");
    
	if ( ( input=fopen(filename,"rb") ) == NULL )
	{
        printf("Adding an highscores file %s\n", filename);
		newHighScoreFile(score);
		if ( ( input=fopen(filename,"rb") ) == NULL )
		{
			printf("Could not create highscores file\n");
			exit(-4);
		}
	}
#endif 

	for(d=0;d<10;d++)
	{
		fread(&score[d],1,sizeof(hstable),input);
	}

	fclose(input);

}

int saveHighScore(struct hstable *score)
{
	FILE *output;
	int d=0;
    char filename[1024];
    
#ifdef _WIN32
    strcpy(filename,".highscores");
    
	if ( ( output=fopen(filename,"wb") ) == NULL )
	{
		printf("Could not save highscores file\n");
		exit(-4);
	}
#else
    strcpy(filename,getenv("HOME"));
    strcat(filename,"/.silverspeed/.highscores");
    
	if ( ( output=fopen(filename,"wb") ) == NULL )
	{
		printf("Could not save highscores file\n");
		exit(-4);
	}
#endif

	for(d=0;d<10;d++)
	{
		fwrite(&score[d],1,sizeof(hstable),output);
	}

	fclose(output);

}

 
int levelComplete(struct container *screen, int *pos, int *count, int level, int difficulty, struct goals *complete, int money, int lives, int kills, int startLives, int enemiesTotal, GLuint *textures, int *texW, int *texH, int *texW2, int *texH2, GLuint *fontTexture, int *fontW, int *fontH, int *fontW2, int *fontH2)
{

	int curTime=0;
    int killsFinal=0;
	char killsText[128];
	char cashText[128];
	char livesText[128];

	// draw screen background
	draw(screen,0,textures,screen->area.w/2-*(texW)/2-10,screen->area.h/2-*(texH)/2,*(texW),*(texH),*(texW2),*(texH2));
	

	switch(*(pos))
	{
		// Kills count
		case 0:

            if ( *(count) < kills )
            {
                *(count)=*(count)+1;
                killsFinal=((float)100/(float)enemiesTotal)**(count);
                
            }else{
                killsFinal=((float)100/(float)enemiesTotal)*kills;
                *(count)=0;
                *(pos)=*(pos)+1;
            }
           
			
			money=0;
			lives=0;
		break;

		// Money Collected
		case 1:
			
			if ( *(count) < money )
			{
				if ( *(count)+100 == money )
				{ 
					*(count)=*(count)+100;
				}else{
					*(count)=*(count)+200;
				}
				money=*(count);
			}else{
				*(count)=0;
				*(pos)=*(pos)+1;
			}

			killsFinal=((float)100/(float)enemiesTotal)*kills;
			lives=0;

		break;
	
		// Lives Lost
		case 2:
			if ( startLives > lives )
			{
				if ( *(count) < startLives-lives )
				{
					*(count)=*(count)+1;
					lives=*(count);
				}else{
					*(count)=0;
					*(pos)=*(pos)+1;
				}
			}else{
				if ( *(count) < lives )
				{
					*(count)=*(count)+1;
					lives=*(count);
				}else{
					*(count)=0;
					*(pos)=*(pos)+1;
				}
			}	

			killsFinal=((float)100/(float)enemiesTotal)*kills;

		break;

        case 3:
            killsFinal=((float)100/(float)enemiesTotal)*kills;
        break;
            
            
		// Score count complete
		default:
			

			killsFinal=((float)100/(float)enemiesTotal)*kills;

	
		break;
	}

    // draw slots for awards
    draw(screen,11,textures,750,screen->area.h/2-*(texH)/2+200,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
    draw(screen,11,textures,750,screen->area.h/2-*(texH)/2+300,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
    draw(screen,11,textures,750,screen->area.h/2-*(texH)/2+400,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
    draw(screen,11,textures,750,screen->area.h/2-*(texH)/2+500,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
    
    // Kills
	draw(screen,1,textures,screen->area.w/2-*(texW)/2+200,screen->area.h/2-*(texH)/2+160,*(texW+1),*(texH+1),*(texW2+1),*(texH2+1));
	sprintf(killsText,"%d",killsFinal);
	putText(screen, killsText,fontTexture,screen->area.w/2-*(texW)/2+100+*(texW+1),screen->area.h/2-*(texH)/2+205,fontW,fontH,fontW2,fontH2);
   
    if ( *(pos) > 0 )
    {
        if ( complete[level].awards[difficulty][0] == 1 )
        {
            // draw award
            draw(screen,6,textures,750,screen->area.h/2-*(texH)/2+200,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
            
        }
    }
    
    // Cash
	draw(screen,2,textures,screen->area.w/2-*(texW)/2+200,screen->area.h/2-*(texH)/2+260,*(texW+2),*(texH+2),*(texW2+2),*(texH2+2));
	sprintf(cashText,"%d",money);
	putText(screen, cashText,fontTexture,screen->area.w/2-*(texW)/2+120+*(texW+1),screen->area.h/2-*(texH)/2+305,fontW,fontH,fontW2,fontH2);
    
 
    if ( *(pos) > 1 )
    {
        if ( complete[level].awards[difficulty][1] == 1 )
        {
            // draw award
            draw(screen,7,textures,750,screen->area.h/2-*(texH)/2+300,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
            
        }
    }
    
    // Lives
	draw(screen,3,textures,screen->area.w/2-*(texW)/2+200,screen->area.h/2-*(texH)/2+360,*(texW+3),*(texH+3),*(texW2+3),*(texH2+3));
	sprintf(livesText,"%d",lives);
	putText(screen, livesText,fontTexture,screen->area.w/2-*(texW)/2+120+*(texW+1),screen->area.h/2-*(texH)/2+405,fontW,fontH,fontW2,fontH2);

    //perfect score
    draw(screen,5,textures,screen->area.w/2-*(texW)/2+185,screen->area.h/2-*(texH)/2+478,*(texW+5),*(texH+5),*(texW2+5),*(texH2+5));
    if ( *(pos) > 2 )
    {
        if ( complete[level].awards[difficulty][2] == 1 )
        {
            // draw award
            draw(screen,8,textures,750,screen->area.h/2-*(texH)/2+400,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
            
        }
        
        if ( complete[level].awards[difficulty][3] == 1 )
        {
            // draw perfect score text
            // draw award
           draw(screen,9,textures,750,screen->area.h/2-*(texH)/2+500,*(texW+6),*(texH+6),*(texW2+6),*(texH2+6));
            
        }
        
        
    }
    
    
}


