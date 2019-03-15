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
        //printf("%s", buffer);
        write = fopen ("../daftar.txt", "w+");
        char* ext;
        char* s;
        while(fgets(buffer, 200, (FILE*) text)) {
            s= buffer;
            //printf("%s", s);
            ext=strrchr(s,'.');
            if (!strcmp(ext, ".txt\n")){
                //printf("%s", s);
                fprintf(write, "%s", s);

            }
            //int ext=strrchr(buffer,'.');
            //if(ext && !strcmp(ext, ".txt")){ // jika mengandung ext
            //printf("%s\n", buffer);}
        }
        remove("../tes.txt");
	chmod("../daftar.txt",  S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);


    fclose(text);
    fclose(write);
    }
    return 0;
}
