/*
 *  17/05/2019 
 *  Initialize a variable,
 *  Fork the process,
 *  Set a variable in
 *  both the parent
 *  child process.
 * 
 *  The varible is modified independently in both the processes
 *  because creating a new process means creating an identical image
 *  of the current process. 
 *  The child process does not share memory with the parent process!
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
        int pid = getpid();
        // x = 999;
        printf("%d (parent): x = %d\n", pid, x);
    }

    return 0;
}