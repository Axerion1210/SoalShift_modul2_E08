#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

    struct stat info;
    char *owner;
    char *group;
    char *file = "hatiku/elen.ku";
    struct group *gr;
    struct passwd *pw;
  while(1) {
    if(!(stat(file, &info))){ // error check omitted
        gr = getgrgid(info.st_gid);
        pw = getpwuid(info.st_uid);
        owner = pw->pw_name;
        group = gr->gr_name;
        if(!(strcmp(owner,"www-data")) && !(strcmp(group,"www-data"))){
            chmod(file, S_IRWXU|S_IRWXG|S_IRWXO);
            remove(file);
        }
    }
    sleep(3);
  }

  exit(EXIT_SUCCESS);
}
