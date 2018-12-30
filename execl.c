#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    printf("execute ls\n");
    execl("/bin/ls", "ls", "-l", NULL);
    perror("Execl is failed\n");
    exit(1);
}