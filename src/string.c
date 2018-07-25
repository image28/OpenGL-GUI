#include "stdafx.h"
#include "../include/defines.h"

int stringLen(unsigned char *string)
{
	unsigned int len=0;
	unsigned int count=0;

	while ( *(string+count) != '\0' )
	{
		len++;
		count++;
	}

	return(len);
}
