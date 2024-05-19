#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

/* 

compile and run
Then send this process signals by executing:
kill -INT pid or ctrl-C to send a SIGINT
Kill -CONT pid  OR  CTRL-z fg will send a SIGCONT

*/


//signal handler for SIGALRM
void sig_alarm_handler(int sig){
   printf("BEEP, signal number %d\n", sig);
   fflush(stdout);
   alarm(5); //schedule another alarm after 5 seconds
}

//signal handler for SIGCONT
void sig_cont_handler(int sig){
    printf("in sigcont handler function, signal number %d\n", sig);
    fflush(stdout);
}


//signal handler for SIGINT
void sig_int_handler(int sig){
    printf("in sigint handler function, signal number %d...exiting\n", sig);
    fflush(stdout); 
    exit(0);
}


int main(){
//Register signal handlers
if(signal(SIGCONT, sig_cont_handler)==SIG_ERR){
    printf("Error call to signal, SIGCONT\n");
    exit(1);
}

if(signal(SIGINT, sig_int_handler)==SIG_ERR){
    printf("Error call to signal, SIGINT\n");
    exit(1);
}


if(signal(SIGALRM, sig_alarm_handler)==SIG_ERR){
    printf("Error call to signal, SIGALRM\n");
    exit(1);
}

printf("kill -CONT %d to send SIGCONT\n", getpid());

alarm(5); //sets an initial alarm to run after 5 seconds. sends first sigalarm in 5 seconds
//enters an infinite loop

//core functionality of the general program is within this while loop, every other thing is an interrupt. 
// The while loop allows for continous execution until a signal interrupt

while(1){
    //normal running program before interrupt. We can do any asynchronous work here while waiting for first alarm
    //to trigger signal after 5 seconds, not compulsory its pause
    pause(); //wait for a signal to happen. Sleep until a signal is received
}


}

/*------Overall Process---
1. The  program starts and registers signal handlers
2. It sets an initial alarm for 5 seconds
3. The program enters a loop waiting for signals 
4. After 5 seconds a SIGALRM signal is delivered
5. The sig_alarm-handler is called, it prints a message, schedules another alarm for 5 seconds and returns
 control to pause
6. The program continues waiting for signals
7. if SIGINT is received, the sig_int_handler is called, a message is printed and program exits








*/