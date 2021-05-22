#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "lib/list.h"
#include "lib/BST.h"
#include "lib/hash.h"
#define MAX_INPUT_NUM 1000000
#define MAX_QUERY_NUM 100000

void error(char *dataname);
void data_init(int *arr, int num);
void swap(int *a, int *b);
int cmp(const void *a, const void *b);
int *binary_search(int *arr, int begin, int end, int target);
int input[MAX_INPUT_NUM]; // prepare for input
int query[MAX_QUERY_NUM]; // prepare for query

int main(int argc, char **argv){
    
    // create N, M
    if(argc < 5) error(argv[0]);
    int N = 0, M = 0;
    if(strcmp(argv[1], "-d") == 0){
        if(strcmp(argv[2], "1e4") == 0) N = 10000;
        else if(strcmp(argv[2], "1e5") == 0) N = 100000;
        else if(strcmp(argv[2], "1e6") == 0) N = 1000000;
        else error(argv[0]);
    }else error(argv[0]);
    if(strcmp(argv[3], "-q") == 0){
        if(strcmp(argv[4], "1e3") == 0) M = 1000;
        else if(strcmp(argv[4], "1e4") == 0) M = 10000;
        else if(strcmp(argv[4], "1e5") == 0) M = 100000;
        else error(argv[0]);
    }else error(argv[0]);

    //determine which data structure should do
    int LinkedList = 0, Array = 0, SortedArray = 0, BST = 0, Hash = 0;
    for (int i = 5; i < argc; i++){
        if(strcmp(argv[i], "-ll") == 0) LinkedList = 1;
        else if(strcmp(argv[i], "-arr") == 0) Array = 1;
        else if(strcmp(argv[i], "-bs") == 0) SortedArray = 1;
        else if(strcmp(argv[i], "-bst") == 0) BST = 1;
        else if(strcmp(argv[i], "-hash") == 0) Hash = 1;
        else error(argv[0]);
    }

    // summon unique input data from 0~N-1
    data_init(input, N);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++){
        swap(input + rand() % (N - i), input + N - i - 1);
    }

    //summon query data from 0~N-1
    for (int i = 0; i < M; i++){
        query[i] = rand() % N;
    }

    // timeval
    struct timeval start, end;
    unsigned long insert_time, query_time;

    // linked list
    if(LinkedList){
        list *head = NULL;
        list *find;
        gettimeofday(&start, NULL);
        for (int i = 0; i < N; i++){
            L_insert(&head, input[i]);
        }
        gettimeofday(&end, NULL);
        insert_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++){
            find = L_find(head, query[i]);
        }
        gettimeofday(&end, NULL);
        query_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        printf("linked list:\n");
        printf("building time: %f sec\n", insert_time / 1000000.0);
        printf("query time: %f sec\n", query_time / 1000000.0);
        printf("\n");
    }

    // array
    if(Array){
        int *arr;
        int *find;
        arr = (int *)malloc(sizeof(int) * N);

        gettimeofday(&start, NULL);
        for (int i = 0; i < N; i++){
            arr[i] = input[i];
        }
        gettimeofday(&end, NULL);
        insert_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++){
            find = NULL;
            for (int j = 0; j < N; j++){
                if(query[i] == arr[j]){
                    find = arr + j;
                    break;
                }
            }
        }
        gettimeofday(&end, NULL);
        query_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        printf("array:\n");
        printf("building time: %f sec\n", insert_time / 1000000.0);
        printf("query time: %f sec\n", query_time / 1000000.0);
        printf("\n");
    }

    // array with binary search
    if(SortedArray){
        int *sarr;
        int *find;
        sarr = (int *)malloc(sizeof(int) * N);

        gettimeofday(&start, NULL);
        for (int i = 0; i < N; i++){
            sarr[i] = input[i];
        }
        qsort(sarr, N, sizeof(sarr[0]), cmp);
        gettimeofday(&end, NULL);
        insert_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++){
            find = binary_search(sarr, 0, N - 1, query[i]);
        }
        gettimeofday(&end, NULL);
        query_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        printf("array with binary search:\n");
        printf("building time: %f sec\n", insert_time / 1000000.0);
        printf("query time: %f sec\n", query_time / 1000000.0);
        printf("\n");
    }

    // BST(binary search tree)
    if(BST){
        bst *root = NULL;
        bst *find;

        gettimeofday(&start, NULL);
        for (int i = 0; i < N; i++){
            bst_insert(&root, input[i]);
        }
        gettimeofday(&end, NULL);
        insert_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++){
            find = bst_find(root, query[i]);
        }
        gettimeofday(&end, NULL);
        query_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        printf("BST:\n");
        printf("building time: %f sec\n", insert_time / 1000000.0);
        printf("query time: %f sec\n", query_time / 1000000.0);
        printf("\n");
    }

    // hash
    if(Hash){
        hash h;

        gettimeofday(&start, NULL);
        H_init(&h);
        for (int i = 0; i < N; i++){
            H_insert(&h, input[i]);
        }
        gettimeofday(&end, NULL);
        insert_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        for (int i = 0; i < M; i++){
            H_find(&h, query[i]);
        }
        gettimeofday(&end, NULL);
        query_time = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);

        printf("hash:\n");
        printf("building time: %f sec\n", insert_time / 1000000.0);
        printf("query time: %f sec\n", query_time / 1000000.0);
        printf("\n");
    }

    return 0;
}

void error(char *dataname){
    printf("format error!\n");
    printf("%s -d [1e4/1e5/1e6] -q [1e3/1e4/1e5] [-ll][-arr][-bs][-bst][-hash]\n", dataname);
    exit(1);
}
void data_init(int *arr, int num){
    for (int i = 0; i < num; i++)
        arr[i] = i;
}
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
int *binary_search(int *arr, int begin, int end, int target){
    if(begin > end) return NULL;
    int upper = end, lower = begin, mid;
    while(lower <= upper){
        mid = lower + (upper - lower) / 2;
        if(arr[mid] < target)
            lower = mid + 1;
        else if(arr[mid] > target)
            upper = mid - 1;
        else return (arr + mid);
    }
    return NULL;
}