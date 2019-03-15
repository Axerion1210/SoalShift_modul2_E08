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
        int fd[2];
        pipe(fd);

        if(fork()==0){
            close(fd[0]);
            dup2(fd[1],1);
            dup2(fd[1],2);
            close(fd[1]);
            execl("/bin/ls", "ls", "/home/siung2/modul2/campur2", (char *)NULL);
        }else{
            char buffer[10000]={0};
            read(fd[0],buffer,sizeof(buffer));
            close(fd[0]);
            close(fd[1]);
            chdir("/home/siung2/modul2/campur2");
            FILE *write;
            write = fopen ("../tes.txt", "w+");
            fprintf(write, "%s", buffer);
            fclose(write);
            FILE *text;
            text = fopen("../tes.txt", "r+");
            write = fopen ("../daftar.txt", "w+");
            char* ext;
            char* s;
            while(fgets(buffer, 200, (FILE*) text)) {
                s= buffer;

                ext=strrchr(s,'.');
                if (!strcmp(ext, ".txt\n")){

                    fprintf(write, "%s", s);

                }

            }
            remove("../tes.txt");
            chmod("../daftar.txt",  S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);


        fclose(text);
        fclose(write);
	return 0;
        }
    }
}




