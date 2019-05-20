/*
 * 17/05/2019 
 * 
 * Open a file,
 * get a file descriptior, 
 * Fork the process,
 * Write to the file from child and parent.
 * 
 * The child process inherits a copy of the file descriptor,
 * Thus, both the child and parent can simultaneously write to the file.
 * Closing the fd in the child closes it only for the child,
 * the parent is unaffected by the childs processes action.
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv) {
    FILE* test_file = fopen("TEST_FILE", "w");
    
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed!\n");
        exit(1);
    }
    else if (rc == 0) { // Child Routine
        int pid = getpid(); 
        fprintf(test_file, "test data from child\n");
        printf("%d (child)\n", pid);
    }
    else{ // Parent Routine
        int rc_wait = wait(NULL);
        int pid = getpid();
        fprintf(test_file, "test data from parent\n");
        printf("%d (parent)\n", pid);
    }

    return 0;
}