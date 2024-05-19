#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//using wait() to retrieve child process termination status here
int main(){
 pid_t pid = fork();

if(pid==-1){
    perror("fork fail");
    exit(EXIT_FAILURE);
}

else if (pid == 0)
{
    /* child process*//* condition */
    printf("child process PID: %d\n", getpid());
   // sleep(2); //simulate some work
   int x =2 ;
   int y = 5;
   int result = x + y;
   printf("%d\n", result);
    exit(0); //child process terminates here
}

else{
    //delay parent process, child  finishes running, enters zombie state
    sleep(120);
    int status;
    //wait returns process id of child whose state has changed to zombie state at this point
    pid_t child_pid = wait(&status);
 
    if(child_pid==-1){ //wait() failure ; if there are no child processes or interrupted by signal handler
        perror("wait failed");
        exit(EXIT_FAILURE); 
    }
    if(WIFEXITED(status)){
        printf("child process %d exited with status %d\n", child_pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
            printf("Child process %d was killed by signal %d\n", child_pid, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Child process %d was stopped by signal %d\n", child_pid, WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("Child process %d was resumed\n", child_pid);
        }
    }

    return 0;
}
