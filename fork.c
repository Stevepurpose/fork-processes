#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

int main(){
    pid_t c_pid = fork();
    int status;

    if(c_pid == -1){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
  else if(c_pid == 0){  
    //child process
    printf("child process  with PID : %d created\n", getpid()); int x =2 ;
   int y = 5;
   int result = x + y;
   printf("%d\n", result);

     while(1);
     //didn't exit, its in a continous loop
   }


else{
    sleep(60);
    kill(c_pid, SIGKILL); //child process killed here
     //wait for the first child process currently in zombie mode and reap it
      
    sleep(50);
 if(waitpid(c_pid, &status, 0)==-1){ //wait() failure ; if there are no child processes or interrupted by signal handler 
    //or options error
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }
    
    if(WIFEXITED(status)){
        printf("child process %d exited with status %d\n",c_pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
            printf("child process %d was killed by signal %d\n", c_pid, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("child process %d was stopped by signal %d\n", c_pid, WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("Child process %d was resumed\n", c_pid);
        }





printf("Parent process with Id :%d is exiting\n", getpid());

}

    return 0;
}