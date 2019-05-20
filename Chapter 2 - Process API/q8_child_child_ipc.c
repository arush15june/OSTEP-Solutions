/*
 * 17/05/2019 
 * 
 * Fork the process twice,
 * connect STDOUT of one to STDIN of the other, 
 * 
 * pipe(fd[2]) makes fd[0] and fd[1] act as file descriptors.
 * fd[0] is setup for reading.
 * fd[1] is setup for writing.
 * 
 * in a child,
 *  if you want to READ through the pipe,
 *      close(fd[1])
 *  if you want to WRITE through the pipe,
 *      close(fd[0])
 * 
 * write from child 1,
 * read from child 2.
 * 
 * Inter Process Communication 
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv) {
    int fd[2];
    pipe(fd); // fd[2] decomposes to &fd[0].
    // fd[0] is for reading, fd[1] is for writing.
    
    int rc[2];
    for(int i = 0; i < sizeof(rc)/sizeof(int); i += 1) {
        rc[i] = fork();
        if ( rc[i] < 0) {
            fprintf(stderr, "fork failed!\n");
            exit(1);
        }
    }
    
    if (rc[0] == 0) { // Child 1 Routine
        int pid = getpid(); 

        // close reading side of pipe
        close(fd[0]);
        FILE* fp = fdopen(fd[1], "w");
        
        fprintf(fp, "hello from the bright side. - %d\n", pid);
    }
    else if (rc[1] == 0) {
        int pid = getpid();

        // close writing side of pipe.
        close(fd[1]);

        FILE* fp = fdopen(fd[0], "r");
        
        char buf[100];
        fgets(buf, 100, fp);

        printf("%d (child): %s\n", pid, buf);
    }
    else{ // Parent Routine
        // WAIT FOR CHILD TO FINISH EXECUTION.
        int rc_wait = wait(NULL);
    
        int pid = getpid();
        // x = 999;
        printf("%d (parent)\n", pid);
    }

    return 0;
}