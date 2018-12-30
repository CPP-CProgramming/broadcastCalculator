#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    char *envp[] = {"USER=chan", NULL};
    char *arg[] = {"/bin/ls", "-al", NULL};

    printf("execute ls\n");
    execve("ls", arg, envp);
    perror("Execl is failed\n");
    exit(1);
}