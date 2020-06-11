#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFLEN 100
int main(){
    char wgetOY[BUFFLEN] = "wget https://people.cs.nctu.edu.tw/~yrhuang/Y.c -O /var/X/Y.c";
    char wgetPY[BUFFLEN] = "wget https://people.cs.nctu.edu.tw/~yrhuang/Y.c -P /var/X/";
    char buildY[BUFFLEN] = "gcc /var/X/Y.c -o /var/X/Y";
    char installY[BUFFLEN] = "install -D /var/X/Y /var/Y/Y";
    char executeY[BUFFLEN] = "/var/Y/Y";
    pid_t pid;
    setuid(0);
    if( access( "/var/X/Y.c", F_OK ) != -1 ) {
        if(system(wgetOY) == 0){
            printf("\nRetrive the source code of Program Y to /var/X/ success.\n");
        }
        else{
            printf("\nFail to retrive the souce code of Program Y to /var/X/.\n");
        }
    } else {
        if(system(wgetPY) == 0){
            printf("\nRetrive the source code of Program Y to /var/X/ success.\n");
        }
        else{
            printf("\nFail to retrive the souce code of Program Y to /var/X/.\n");
        }
    }
    if(system(buildY) == 0){
        printf("\nBuild Program Y under /var/X/ success.\n");
    }
    else{
        printf("\nFail to build Program Y under /var/X/.\n");
    }
    if(system(installY) == 0){
        printf("\nInstall Program Y under /var/Y/ success.\n");
    }
    else{
        printf("\nFail to install Program Y under /var/Y/.\n");
    }
    pid = fork();
    if(pid == 0){
        if(system(executeY) == 0){
            printf("\nExecute Program Y under /var/Y/ success.\n");
        }
        else{
            printf("\nFail to execute Program Y under /var/Y/.\n");
        }
    }
    else if(pid > 0){
        wait(NULL);
    }
    return 0;
}

