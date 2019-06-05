#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char** argv) {
    int alloc_mb, loop_time;

    if(argc == 3) {
        alloc_mb = atoi(argv[1]);
        loop_time = atoi(argv[2]);
    }
    else if(argc == 2) {
        alloc_mb = atoi(argv[1]);
        loop_time = 0;
    }
    else {
        puts("Usage: ./memory-user [memory in MB to allocate] [seconds to run for]\n./memory-user 100 10");
        return 1;
    }

    int alloc_bytes = alloc_mb*1024*1024;

    int *buf = (int *)malloc(alloc_bytes);

    struct timespec start_time;
    struct timespec end_time;
    struct timespec last_print;

    clock_gettime(CLOCK_REALTIME, &start_time);
    clock_gettime(CLOCK_REALTIME, &last_print);

    while(1) {
        for(int i = 0; i < alloc_bytes/sizeof(buf); i++) {
            buf[i] = i;
        }

        clock_gettime(CLOCK_REALTIME, &end_time);

        if((end_time.tv_sec - last_print.tv_sec) > 0) {
            printf("Runtime: %d s\r", end_time.tv_sec - start_time.tv_sec);
            fflush(stdout);
            clock_gettime(CLOCK_REALTIME, &last_print);
        }

        if(loop_time != 0) {
            if(end_time.tv_sec - start_time.tv_sec >= loop_time) {
                break;
            }
        }
    }

    return 0;
}
