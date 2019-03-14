#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(){
    pid_t child_id;
    int status;
    chdir("/home/siung2/modul2");
    child_id = fork();
    if(child_id < 0){
        exit(EXIT_FAILURE);
    }
    if(child_id==0){
        pid_t gChild_id;
        int status2;
        gChild_id = fork();
        if(gChild_id < 0){
            exit(EXIT_FAILURE);
        }
        if(gChild_id == 0){
            //1. Gchild;
            char *argv[] = {"unzip", "campur2.zip", NULL};
            execv("/usr/bin/unzip", argv);
        }else{
            while((wait(&status2))>0);
            //2. Child;
            char *argv[] = {"touch", "daftar.txt", NULL};
            execv("/usr/bin/touch", argv);
        }

    }else{
        while((wait(&status))>0);
        //3. Parent;
        FILE *fp;
        FILE *write;
        char s[100];
        chdir("/home/siung2/modul2/campur2");
        fp = popen("ls *.txt", "r");
        if(fp==NULL)exit(EXIT_FAILURE);
        write = fopen ("../daftar.txt", "w+");
        while (fgets(s, 100, fp) != NULL){
            fprintf(write, "%s", s);
        }
         pclose(fp);
         fclose(write);
         chmod("../daftar.txt",  S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
         return 0;
    }
}


