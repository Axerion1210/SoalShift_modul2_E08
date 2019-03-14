#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

struct dirent *de;
DIR *dr;
char* ext;
char *add = "_grey.png";
char oldName[1000];
char newName[1000];
char * path= "/home/siung2/modul2/";
char* s;


int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/siung2/modul2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);



  while(1) {
    // main program here
    //pointer for directory entry

	//opendir() returns a pointer of DIR type.
	dr = opendir(".");

	if (dr == NULL) //opendir returns NULL if couldn't open dir
	{
        printf("Could not open current directory");
        return 0;
	}


	while ((de = readdir(dr)) != NULL){
        //printf("%s\n", de->d_name);
        s = de->d_name;
        ext=strrchr(s,'.');
        if(ext && !strcmp(ext, ".png")){ // jika mengandung ext
            int x= ext-s;
            memset(oldName, 0, strlen(oldName));
            memset(newName, 0, strlen(newName));
            strncpy(oldName,s,x);
            strcat(newName,"/home/siung2/modul2/gambar/");
            strcat(newName,oldName);
            strcat(newName,add);
            rename(s,newName);
        }
    }

    closedir(dr);



    sleep(1);
  }

  exit(EXIT_SUCCESS);
}
