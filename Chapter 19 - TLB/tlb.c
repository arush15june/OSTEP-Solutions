#define _GNU_SOURCE 
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>

long double run_trial(const int numpages, uint64_t trials) {
    int PAGESIZE = getpagesize(); 
    size_t jump = PAGESIZE / sizeof(int);
    struct timespec start_time;
    struct timespec end_time;

    int *arr = (int*)calloc(numpages*PAGESIZE, sizeof(int));

    // Touch NUMPAGES amount of pages.
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    while(trials > 0) {
        for(size_t iPage = 0; iPage < numpages; iPage += jump) {
            arr[iPage] += 1;
        }
        trials -= 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    long double time_taken = (end_time.tv_sec - start_time.tv_sec) * 1e9; 
    time_taken = (time_taken + (end_time.tv_nsec - start_time.tv_nsec)); 
    
    printf("%Lf\n", time_taken);

    return (long double) time_taken / (long double) (numpages*trials);
}

int main(int argc, char** argv) {
    if(argc != 3) {
        puts("Usage: ./tlb <number of pages> <number of trials>");
        exit(1);
    }

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset)) {
        puts("Error setting cpu affinity\n");
        exit(1);
    }

    size_t NUMPAGES = atoi(argv[1]);
    size_t TRIALS = atoi(argv[2]);

    struct timespec res_time;
    clock_getres(CLOCK_MONOTONIC, &res_time);
    // printf("%ld %ld\n", res_time.tv_sec, res_time.tv_nsec);

    long double ACCESS_TIME = run_trial(NUMPAGES, TRIALS);
    // printf("%Le\n", ACCESS_TIME);
    return 0;
}