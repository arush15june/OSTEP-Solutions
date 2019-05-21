/* 

    System Call Measurement

    Measure time taken by back to back `gettimeofday()` calls.
        t1 = time(gettimeofday())
        t2 = time(gettimeofday())

        t2 - t1

 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>

void print_time_diff(struct timeval *t1, struct timeval *t2) {
    printf("t1 = %lld\n", (t1->tv_sec*1000000LL) + t1->tv_usec);
    printf("t2 = %lld\n", (t2->tv_sec*1000000LL) + t2->tv_usec);
    printf("Difference = %lld\n", (t2->tv_sec-t1->tv_sec)*1000000LL + t2->tv_usec-t1->tv_usec);   
}

int main() {
    struct timeval t1;
    struct timeval t2;
    
    puts("[+] Back to Back gettimeofday() calls");
    
    gettimeofday(&t1, NULL);
    gettimeofday(&t2, NULL);

    print_time_diff(&t1, &t2);
    
    FILE* f = fopen("TEST_FILE", "r+");
    char buf[10];
    int fd = fileno(f);
    
    puts("[+] 0 Byte read() from file.");
    
    gettimeofday(&t1, NULL);
        read(fd, buf, 0);
    gettimeofday(&t2, NULL);

    print_time_diff(&t1, &t2);

    return 0;
}