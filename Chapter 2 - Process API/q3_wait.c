/*
 * 17/05/2019 
 * 
 * Fork the process,
 * wait for child to finish execution.
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv) {
    int x = 100;
    
    int rc = fork();

    if ( rc < 0) {
        fprintf(stderr, "fork failed!\n");
        exit(1);
    }
    else if (rc == 0) { // Child Routine
        int pid = getpid(); 
        x = 120;
        printf("%d (child): x = %d\n", pid, x);
    }
    else{ // Parent Routine
        // WAIT FOR CHILD TO FINISH EXECUTION.
        int rc_wait = wait(NULL);
    
        int pid = getpid();
        // x = 999;
        printf("%d (parent): x = %d\n", pid, x);
    }

    return 0;
}