#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sig_child_handler(int sig){
    int status;
    pid_t pid;

    //add loop to reap all terminated child processes
   while ((pid = waitpid(-1, &status, WNOHANG))>0)
   {
    printf("child process %d terminated\n", pid);
  
   }
   
}


int main(){
    //Register SIGCHLD handler
    if(signal(SIGCHLD, sig_child_handler)==SIG_ERR){
        perror("SIGNAL FAILED");
        exit(1);
    
}

//make child process
pid_t pid = fork();

if(pid == -1){
    perror("fork failed");
    exit(1);
}

else if(pid == 0){
    printf("child process with PID:%d created\n", getpid());
    sleep(4);
    printf("child process with PID:%d exiting....\n", getpid());
    exit(0);
}

else{
   printf("parent process with PID:%d running\n", getpid()); 
   
}while (1) {
            // Use pause to wait for signals
            pause();

            // Check if the specific child process has terminated
            if (waitpid(pid, NULL, WNOHANG) == pid) {
                break;  // Break the loop if the child has terminated
            }
        }
return 0;

}