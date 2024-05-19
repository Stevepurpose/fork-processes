#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
      //pid_t p = fork();


    if(fork() > 0){
        printf("before sleep\n");
        //deliberately delaying the parent process so that the child process
        // can finish running and enter zombie mode
        // when the parent process eventually terminates, the child process is inherited by the init process
        // The init process eventually  calls wait() to clean up the zombies.
        sleep(120);
        printf("I am a parent");
    }

    else if(fork()==0){

//create new process with  an exec() function
    printf("child process created\n");
    execl("/bin/cat","cat", "/mek.txt", NULL);
     exit(EXIT_SUCCESS);
    //enter zombie mode since parent process is still running at this point and didn't call wait
      }
    
      return 0;
}