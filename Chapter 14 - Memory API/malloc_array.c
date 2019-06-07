#include<stdio.h>
#include<stdlib.h>

int main() {
    int* arr = (int*)malloc(sizeof(int)*100);

    arr[100] = 0;
    
    free(arr);
    printf("%d", *arr);

    return 0;   
}