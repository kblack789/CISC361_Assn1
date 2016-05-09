#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
	char *owrite;
	owrite = malloc(64);
	int i,f1,f2;
	char *file1,*file2,buf[2];
	file1=argv[1];
	file2=argv[2];

	if (argv[1] == NULL || argv[2] == NULL || argv[3] != NULL) {
		printf("\nIncorrect amount of arguments. Goodbye.\n\n");
		free(owrite);
		return 0;
	}

	if (access(file1, F_OK) != -1){
		if (access(file2, F_OK) != -1){
			printf("\nWould you like to overwrite this file? Y or N: ");
			fgets(owrite, 64, stdin);
			
			if (*owrite == 'Y') {
				printf("overwritten\n");
				f1=open(file1,O_RDONLY,0777);
				f2=creat(file2,0777);
				while(i=read(f1,buf,1)>0){
					write(f2,buf,1);
				}
				
			}
			else if (strcmp(owrite, "N") == 0){
				printf("Will not overwrite or copy file");
			}
		}
		else if (access(file2, F_OK) == -1){
			f1=open(file1,O_RDONLY,0777);
			f2=creat(file2,0777);
			while(i=read(f1,buf,1)>0){
				write(f2,buf,1);
			}
		}
	}
	else if (access(file1, F_OK) == -1) {
		printf("\nSource file does not exist. Goodbye.\n\n");
		free(owrite);
		return 0;
	}

	//printf("\nfile1=%s file2=%s\n\n",file1,file2);
	close(f1);
	close(f2);
	free(owrite);
}
