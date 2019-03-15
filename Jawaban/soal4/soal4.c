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

  int x = 1;

  while(1) {
    time_t wkt = (unsigned)time(NULL);

    struct stat filestat;
    stat("/home/ivan/Documents/makanan/makan_enak.txt",&filestat);

    if((int)difftime(wkt,filestat.st_atime)<=30)
    {
      char filename[200];
      sprintf(filename,"/home/ivan/Documents/makanan/makan_sehat%d.txt",x);
      FILE *fPoint;
      fPoint = fopen(filename, "a");
      fclose(fPoint);
      x++;
    }

    sleep(5);
  }

  exit(EXIT_SUCCESS);
}
