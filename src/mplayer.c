// Parts of code from the xmms-mplayer plugin, unsure if they will
// work crossplatform yet
/*
int openMplayer()
{
	int pipe_ret=pipe(mplayer_pipe); // ? does windows have this

	mplayer_debugf("starting mplayer\n");

	if(file_info)
		g_free(file_info);

	file_info = mplayer_read_file_info(filename);

	mplayer_debugf("Settings\n----------------\nCaption: %s\nLength: %i\nabr: %i\nbitrate %i\nnch :%i\n\n",
			mplayer_current_info->caption,
			mplayer_current_info->length * 1000,
			mplayer_current_info->abr,
			mplayer_current_info->rate,
			mplayer_current_info->nch);
	
	if (mplayer_current_cfg){
		g_free(mplayer_current_cfg->extra);
		g_free(mplayer_current_cfg);
	}

	mplayer_current_cfg=mplayer_read_cfg();

	// set temp filename
	strcpy(mplayer_fifoname,"tmp/mplayer-audio");

	mkfifo(mplayer_fifoname,0600); // ? does windows have this

	mplayer_ip->output->open_audio(FMT_S16_LE,
			mplayer_current_info->rate,
			mplayer_current_info->nch);

	if (mplayer_playing==1)
		mplayer_debugf("Duplicate call!! -- Panic \n");
	else 
		mplayer_playing=1;

	ret = pthread_create(&mplayer_tid, NULL, mplayer_play_loop, arg);

}

int playMplayer(char *file, )
{
	

}

int stopMplayer()
{
	mplayer_playing=0;
		
	mplayer_ip->output->close_audio();

	if ( write(mplayer_pipe[1],"quit\n",5) == 5 )
	{
		mplayer_debugf("exit\n");
	}
		
	ret = pthread_join(mplayer_tid, NULL);

}

int pauseMplayer()
{
	write(mplayer_pipe[1],"pause\n",6);
}

int seekMplayer()
{
	char buff[16];
	if(mplayer_playing){
		sprintf(buff,"seek %i\n",(t - mplayer_current_time));
		write(mplayer_pipe[1],buff,strlen(buff));
	}
}

int closeMplayer()
{
	if (mplayer_playing) mplayer_stop();
	if (mplayer_fifoname){
		remove(mplayer_fifoname);
		g_free(mplayer_fifoname);
		mplayer_fifoname=NULL;
	}
}
*/