#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/path.h"

int genorateDrops(int *drops, int *seed, int *seedDefault, int difficulty, int collisions, int *dropX, int *dropY, int *type ,int *enemyX, int *enemyY, int *enemyType, int *collide, int *enemyHits )
{
	int random=0;
	int d=0;

	for(d=*(drops);d<collisions+*(drops);d++)
	{

		*(dropX+d)=*(enemyX+*(collide+(d-*(drops))))+20;
		*(dropY+d)=*(enemyY+*(collide+(d-*(drops))))+20;

		srand(time(0));
		if ( seed == 0 )
		{
			random=0;
		}else{
			random=rand()%*(seed);
		}

		if ( *(seed) >= 10 )
		{
			*(seed)=*(seed)-1;
               		*(type+d)=*(enemyType+*(collide+(d-*(drops))))+1;
 
		}else{
			if ( random == 0 )
			{

				*(seed)=*(seedDefault+difficulty);
				*(type+d)=0;
			}else{
				*(type+d)=*(enemyType+*(collide+(d-*(drops))))+1;
				*(seed)=*(seed)-1;
			}
		}
		
	}

	*(drops)=*(drops)+collisions;
return(0);
}

int genorateEnemies(int *count, int *seed, int *seedDefault, int difficulty, int *type, int typeTotal, int backTotal, int *hits, int *hitsDefault,int *enemyX, int *enemyY, int *enemyW, int pos, int level)
{
	int random=0;
    int interval=0;
    
	//srand(time(0));
	// given level and time
		// set enemy to be genorated type

	if ( typeTotal == 3 )
	{
		interval=2;
	}else if ( typeTotal == 4 )
	{
		interval=2;
	}else{
		interval=3;
	}
	    
	if ( pos < backTotal/interval )
	{
		*(type+*(count))=0;
	}

	if ( pos >= backTotal/interval )
	{
		*(type+*(count))=2;
	}

	if (( interval == 3 ) && ( pos > (backTotal/interval)*2 ))
	{
		*(type+*(count))=4;
	}

	// genorate a random number between 0 and X
		// if 0 minus 1 from type
	if ( *(type+*(count)) < typeTotal-1 )
	{
		random=(rand()+*(count))%3;
		if ( ! random )
		{
			*(type+*(count))=*(type+*(count))+1;
		}
	}else if ( typeTotal == 3 )
	{
		if ( *(type+*(count)) == 2 )
		{
			random=(rand()+*(count))%3;
			if ( ! random )
			{
				*(type+*(count))=1;
			}
		} 
	}else if ( typeTotal == 5 )
	{
		if ( *(type+*(count)) == 4 )
		{
			random=(rand()+*(count))%3;
			if ( ! random )
			{
				*(type+*(count))=3;
			}
		}
	}

	if ( *(type+*(count)) >= typeTotal )
	{
		//printf("ARRR\n");
		*(type+*(count))=typeTotal-1;
	}

	// pass the given enemies type seed to random
	if ( *(seed+difficulty) == 0 )
	{
		random=0;
	}else{
		random=(rand()+*(count))%*(seed+difficulty);
	}

	if ( *(count) > 0 )
	{
		if ( *(enemyX+*(count)-1) < 960-*(enemyW+*(count)-1) )
		{	
			if ( random == 0 )
			{
				*(seed+difficulty)=*(seedDefault+difficulty);
				*(enemyY+*(count))=rand()%648;
				*(enemyX+*(count))=1024;
				*(hits+*(count))=*(hitsDefault+*(type+*(count))); // load value for enemy type from config file
				// if type equal zero hits equal one, if type equal one hits equal two, etc...
				*(count)=*(count)+1;
			}else{
				*(seed+difficulty)=*(seed+difficulty)-5;
				if ( *(seed+difficulty) < 0 )
					*(seed+difficulty)=0;
			}
		}
	}else{
		if ( random == 0 )
		{
			*(seed+difficulty)=*(seedDefault+difficulty);
			*(enemyY+*(count))=rand()%648;
			*(enemyX+*(count))=1024;
			*(hits+*(count))=*(hitsDefault+*(type+*(count)));
			// if type equal zero hits equal one, if type equal one hits equal two, etc...
			*(count)=*(count)+1;
		}else{
			*(seed+difficulty)=*(seed+difficulty)-5;
			if ( *(seed+difficulty) < 0 )
				*(seed+difficulty)=0;
		}
	}
	return(0);
}

int genorateEnemyBullets(int *count, int enemyCount, int *seed, int *seedDefault, int difficulty, int *enemyX, int *enemyY, int enemyW, int enemyH, struct coords *area)
{
	long random=0;
	int d=0;



	for(d=0;d<enemyCount;d++)
	{
		srand(time(0));
		random=rand()%*(seed);

		if ( *(count) > 0 )
		{
			if ( random == 0 )
			{
				if ( *(seed) < 50 )
				{
					if ( ( *( enemyX+d) > 0 ) && ( *(enemyX+d)+enemyW < 1024 ) )
					{
						if ( difficulty == 0 )
						{
							*(seed)=*(seedDefault);
						}else if ( difficulty == 1 )
						{
							*(seed)=*(seedDefault+1);
						}else{
							*(seed)=*(seedDefault+2);
						}
						area[*(count)].y=*(enemyY+d)+(enemyH/2);
						area[*(count)].x=*(enemyX+d)+(enemyW/2);
						*(count)=*(count)+1;
					}
				}
			}else{
				*(seed)=*(seed)-1;
			}
		}else{
			if ( random == 0 )
			{
				if ( *(seed) < 50 )
				{
					if ( ( *( enemyX+d) > 0 ) && ( *(enemyX+d)+enemyW < 1024 ) )
					{
						if ( difficulty == 0 )
						{
							*(seed)=*(seedDefault);
						}else if ( difficulty == 1 )
						{
							*(seed)=*(seedDefault+1);
						}else{
							*(seed)=*(seedDefault+2);
						}
						area[*(count)].y=*(enemyY+d)+(enemyH/2);
						area[*(count)].x=*(enemyX+d)+(enemyW/2);
						*(count)=*(count)+1;
					}
				}
			}else{
				*(seed)=*(seed)-1;
			}
		}
	}
	return(0);
}

