#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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

  if ((chdir("/home/ivan/Sisop/Praktikum2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

int x=0;
char filedir[200]; 

  while(1) {
    struct stat st = {0};

    if (stat("/home/ivan/log", &st) == -1) {
        mkdir("/home/ivan/log", 0777);
    }

    if(x%30==0){
      time_t now = (unsigned)time(NULL);
      struct tm cur = *localtime(&now);
      sprintf(filedir,"/home/ivan/log/%02d:%02d:%04d-%02d:%02d",cur.tm_mday,cur.tm_mon+1,cur.tm_year+1900,cur.tm_hour,cur.tm_min);
      mkdir(filedir,0777);
    }
    x++;
    
    char ch, dfile[100];
    FILE *source, *target;    

    char sfile[100] = "/var/log/syslog";
    sprintf(dfile,"%s/log%d.log",filedir,x);

    source = fopen(sfile,"r");
    target = fopen(dfile,"w");

    while ((ch = fgetc(source)) != EOF)
      fputc(ch,target);

    fclose(source);
    fclose(target);

    sleep(60);
  }

  exit(EXIT_SUCCESS);
}
