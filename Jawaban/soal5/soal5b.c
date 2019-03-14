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
    FILE *cmd = popen("pidof /home/ivan/Sisop/Praktikum2/soal5", "r");

    fgets(line, 100, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    
    kill(pid, SIGKILL);

    pclose(cmd);
}
