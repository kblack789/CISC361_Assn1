#include "mp3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_SIZE 256

struct mp3 *head;
struct mp3 *tail;

int main(){

	int options;
	printf("\nWelcome to The Song Database.");

	while (options != 5) {
		options = intro();
		if (options == 1) {
			char* artist;	
			char* album;
			char* song_title;
			char* date;
			char* song_time_char;	
			int song_time;

			artist = malloc (MAX_SIZE);
			album = malloc (MAX_SIZE);
			song_title = malloc (MAX_SIZE);
			date = malloc (MAX_SIZE);
			song_time_char = malloc (MAX_SIZE);

			printf ("\nPlease enter the artist name: ");
			fgets (artist, MAX_SIZE, stdin);
		   	if ((strlen(artist)>0) && (artist[strlen (artist) - 1] == '\n'))
				artist[strlen (artist) - 1] = '\0';

			printf ("Please enter the album name: ");

			fgets (album, MAX_SIZE, stdin);
		   	if ((strlen(album)>0) && (album[strlen (album) - 1] == '\n'))
				album[strlen (album) - 1] = '\0';

			printf("Please enter the song title: ");
			fgets (song_title, MAX_SIZE, stdin);
		   	if ((strlen(song_title)>0) && (song_title[strlen (song_title) - 1] == '\n'))
				song_title[strlen (song_title) - 1] = '\0';

			printf("Please enter the date: ");
			fgets (date, MAX_SIZE, stdin);
		   	if ((strlen(date)>0) && (date[strlen (date) - 1] == '\n'))
				date[strlen (date) - 1] = '\0';


			printf("Please enter song time: ");
			fgets(song_time_char, MAX_SIZE, stdin);
			if ((strlen(song_time_char)>0) && (song_time_char[strlen (song_time_char) - 1] == '\n'))
				song_time_char[strlen (song_time_char) - 1] = '\0';
			song_time = atoi(song_time_char);

			pushItem(artist, album, song_title, date, song_time);
			
			free(artist);
			free(album);
			free(song_title);
			free(date);
			free(song_time_char);

		}
	
		else if (options == 2) {
			delete_artist();
		}
	
		else if (options == 3) {
			if (head == NULL) {
				printf("\nNo entries found\n");
			}
			else {
				printf("\nPrinting it forward:\n");
				print_forward(head);
			}
		}

		else if (options == 4) {
			if (head == NULL) {
				printf("\nNo entries found\n");
			}
			else {
				printf("\nPrinting it backward\n");
				print_backward(tail);
			}
		}
	
		else if (options == 5) {

			freeEverything(head);
			printf("\nGoodbye.\n");
			break;
		}

		else {
			printf("\nNo Valid Input\n");	
		}
	}
	return 0;
}


void freeEverything(struct mp3* p){
	struct mp3* temp;
	while (p != NULL){
		temp = p->next;
		if(head == p) 
			head = p->next;
		if(tail == p) 
			tail = p->previous;
		if(p->previous)
			p->previous->next = p->next;
		if(p->next)
			p->next->previous = p->previous;
		p->previous = p->next = NULL;
		free(p->artist);
		free(p->album);
		free(p->title);
		free(p->date);
		free(p);
		p = temp;
	}
}

void pushItem(char* artist_name, char* album_name, char* title_name, char* date_added, int seconds){
	struct mp3 *temp;
	temp = (struct mp3 *) malloc(sizeof *temp); //allocate size to memory
	char* artist1 = malloc (MAX_SIZE);	
	char* album1 = malloc (MAX_SIZE);
	char* song_title1 = malloc (MAX_SIZE);
	char* date1 = malloc (MAX_SIZE);	

	artist1 = malloc (MAX_SIZE);
	album1 = malloc (MAX_SIZE);
	song_title1 = malloc (MAX_SIZE);
	date1 = malloc (MAX_SIZE);

	memcpy(artist1, artist_name, MAX_SIZE);
	memcpy(album1, album_name, MAX_SIZE);
	memcpy(song_title1, title_name, MAX_SIZE);
	memcpy(date1, date_added, MAX_SIZE);

	temp->artist = artist1; //assign the inputs to the parts of the mp3 struct
	temp->album = album1;
	temp->title = song_title1;
	temp->date = date1;
	temp->song_time = seconds;
	temp->previous = NULL;	//add song at the head
	temp->next = head;
	if(head) 	//reassign pointers
		head->previous = temp;
	head = temp;
	if(!tail)
		tail = temp;
}


int removeItem(struct mp3* p, char* artist_name){
	struct mp3* temp;
	if (p == NULL){
		printf("\nNo enteries found\n");
		return 0;
	}
	if(p == head && p == tail){
		if(strcmp(p->artist, artist_name) == 0){
			head = NULL;
			tail = NULL;
			return 0;
		}
	}
	while (p != NULL){
		if (strcmp(p->artist, artist_name) == 0){
			temp = p->next;
			if(head == p) 
				head = p->next;
			if(tail == p) 
				tail = p->previous;
			if(p->previous)
				p->previous->next = p->next;
			if(p->next)
				p->next->previous = p->previous;
			p->previous = p->next = NULL;
			free(p->artist);
			free(p->album);
			free(p->title);
			free(p->date);
			free(p);
			p = temp;
		}
		else{
			p = p->next;
		}
	}
	printf("Deleted everything by %s", artist_name);
	return 0;
}


void delete_artist(){
	char* artist_name;
	artist_name = malloc (MAX_SIZE);

	printf("\nPlease enter the artist whose songs you wish to delete: ");
	fgets (artist_name, MAX_SIZE, stdin);
   	if ((strlen(artist_name)>0) && (artist_name[strlen (artist_name) - 1] == '\n'))
        	artist_name[strlen (artist_name) - 1] = '\0';
	//printf("Artist name entered: %s\n", artist_name);
	
	removeItem(head, artist_name);

	free(artist_name);
}

void print_payload(struct mp3 *MP3){
	if (!MP3)
		printf("NULL POINTER!\n");
	else
		printf("%s, %s, %s, %s, %d\n",MP3->artist, MP3->album, MP3->title, MP3->date, MP3->song_time);
}

void print_item(struct mp3 *MP3){
	if (!MP3)
		printf("NULL POINTER!\n");
	else {
		//printf("%p <-[%p]-> %p\n", MP3->previous, MP3, MP3->next);
		print_payload(MP3);
		printf("\n");
	}
}


void print_forward(struct mp3 *MP3){
	for(; MP3; MP3 = MP3->next)
        print_item(MP3);
}

void print_backward(struct mp3 *pItem){
	for(; pItem; pItem = pItem->previous)
        print_item(pItem);
}

int intro() {
	char* option;
	option = malloc (MAX_SIZE);
	int options;
	printf("\nPlease choose one of the following option:\n");
	printf("\t1. Add a song to the database\n\t2. Delete all songs by an artist from the database\n\t3. Print the list from beginning to end\n\t4. Print the list from end to beginning\n\t5. Exit\n");
	printf("\nPlease choose an option: ");
	fgets (option, MAX_SIZE, stdin);
   	if ((strlen(option)>0) && (option[strlen (option) - 1] == '\n'))
        	option[strlen (option) - 1] = '\0';
	options = atoi(option);
	free(option);	
	return options;
}


