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
    struct tm dt1 = *localtime(&wkt);

    struct stat filestat;
    stat("/home/ivan/Documents/makanan/makan_enak.txt",&filestat);
    struct tm dt2 = *localtime(&filestat.st_atime);

    if(dt1.tm_sec-dt2.tm_sec<=30 && dt1.tm_min==dt2.tm_min && dt1.tm_hour==dt2.tm_hour && dt1.tm_mday==dt2.tm_mday && dt1.tm_mon==dt2.tm_mon && dt1.tm_year==dt2.tm_year)
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
