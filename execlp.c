#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

//This file is going to put the init process to test by finishing the parent process before the child process

int main(){
    if(fork < 0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    else if(fork()==0){
     sleep(2);
//create new process with  an exec() function
    printf("child process created with PID:%d\n",getpid());
    sleep(120);
    execlp("cat","cat", "/home/stephen/mek.txt", NULL);
    exit(EXIT_SUCCESS);
    
      }
    else{
    printf("parent process created with PID:%d\n",getpid());
    sleep(30);
    printf("parent process with PID:%d\n exiting\n",getpid());
    exit(EXIT_SUCCESS);

    }
    
      return 0;
}