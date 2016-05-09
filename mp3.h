struct mp3 {
	char* artist;
	char* album;
	char* title;
	char* date;
	int song_time;
	struct mp3 *next;
	struct mp3 *previous;
};

