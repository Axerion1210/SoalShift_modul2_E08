#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char line[100];
    int x;

    FILE *cmd = popen("pidof /home/ivan/Sisop/Praktikum2/soal5a", "r");
    fgets(line, 100, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    pclose(cmd);
    while(pid!=0){
        kill(pid, SIGKILL);
           
        cmd = popen("pidof /home/ivan/Sisop/Praktikum2/soal5a", "r");
        memset(line,0,100);            
        fgets(line, 100, cmd);
        pclose(cmd);
        pid = strtoul(line, NULL, 10);
    }
    return 0;   
}
