/*int playCD()
{
	
}

int pauseCD()
{
}

int stopCD()
{

}

int openWav( char *file )
{

}

int startWav( char *file, int loop )
{
	
}

int pauseWav()
{

}

int stopWav( char *file )
{

}

int closeWav( char *file )
{

}*/
/*
int seekWav(char *file, int seconds, int from)
{
	// change to only seek from start .001 seconds faster
	if ( from == START )
	{
		if ( seconds < wavelength )
			wavepos=(unsigned int)seconds;
		else
			wavepos=wavelength;
	}
	else if ( from == END )
	{
		if ( seconds-wavelength < 0 )
			wavepos=wavelength-(unsigned int)seconds;
		else
			wavepos=0;
	}
	else if ( from == CURRENT )
	{
		if ( wavepos+seconds < wavelength )
			wavepos=wavepos+seconds;
		else
			wavepos=wavelength;
	}

	// maybe calculate seconds to frames/byteblocks...?

	// seek to position in file

}*/
