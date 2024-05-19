#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


//use kill -TERM PID  from another terminal to terminate program
// use ctrl+c to interrupt program or kill -INT PID from another terminal

void sig_int_handler(int sig){
    write(STDOUT_FILENO, "I handle signals\n", 30);
}


int main(){

   printf("Program running awake yet?\n");
   fflush(stdout);
   
   signal(SIGINT, sig_int_handler);
   
  
    while(1){
        
     printf("snoring loudly %d\n ", getpid());
     sleep(5);

    }



    
    return 0;
}