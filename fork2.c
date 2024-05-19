#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


//This file examines the creation of two child processes

int main(){
    pid_t pid1, pid2;
    int status;
//create the first child process
   pid1 = fork();
   
   if(pid1<0){
     perror("fork failed for child 1");
     exit(EXIT_FAILURE);
   }
    
   else if(pid1 == 0){
     //first child process
     printf("first child process with PID: %d is running\n", getpid());
     sleep(10);
    printf("first child process with PID: %d is exiting\n", getpid()); 
    exit(EXIT_SUCCESS);
   }
    
//create the second child process
   pid2 = fork();

   if(pid2<0){
     perror("fork failed for child 2");
     exit(EXIT_FAILURE);
   }
    
   else if(pid2 == 0){
     //first child process
     printf("Second child process with PID: %d is running\n", getpid());
     sleep(18);
    printf("Second child process with PID: %d is exiting\n", getpid()); 
    exit(EXIT_SUCCESS);
   }

 
 //wait for the first child process currently in zombie mode and reap it
       sleep(60);
    if(waitpid(pid1, &status, 0)==-1){ //wait() failure ; if there are no child processes or interrupted by signal handler 
    //or options error
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }
    else{
    if(WIFEXITED(status)){
        printf("First child process %d exited with status %d\n",pid1, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
            printf("First child process %d was killed by signal %d\n", pid1, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("First child process %d was stopped by signal %d\n", pid1, WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("First Child process %d was resumed\n", pid1);
        }
    }

//wait for the second child process currently in zombie mode and reap it
       sleep(75);
    if(waitpid(pid2, &status, 0)==-1){ //wait() failure ; if there are no child processes or interrupted by signal handler 
    //or options error
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }
    else{
    if(WIFEXITED(status)){
        printf("Second child process %d exited with status %d\n",pid2, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
            printf("Second child process %d was killed by signal %d\n", pid2, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Second child process %d was stopped by signal %d\n", pid2, WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("Second child process %d was resumed\n", pid2);
        }
    }
    printf("Parent child process with PID: %d is exiting\n", getpid()); //parent process closing
return 0;
}