/*
 * 17/05/2019 
 * 
 * Fork the process,
 * use wait in the child.
 * 
 * the wait returns instantly as the child has no child itself
 * and continues normal execution
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv) {
    int x = 100;
    
    int rc_1 = fork();

    if ( rc < 0) {
        fprintf(stderr, "fork failed!\n");
        exit(1);
    }
    else if (rc == 0) { // Child Routine
        int rc_wait_child = wait(NULL);
    
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