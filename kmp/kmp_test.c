/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：kmp_test.c
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-12-05
*   Description   ：kmp algorithm for accelerating find the matched string(we called it template) in the targets.
*                   it's general used in NLP/ASR
*
================================================================*/


#include "stdio.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1024
#define OPT 0

/**
 *  GetFailureFunction
 *  used to set each rollback position for everyone in next.
 *  @next:
 *      failure function of template string, like [-1, 0, 0] in 'ABC', or [-1, 0, 1] in 'ABA'
 *  @size:
 *      length of @next array
 *  @template:
 *      template string, like 'ABC'
 **/
int GetFailureFunction(char* next, int size, const char* template) {
    int j=0, k=-1;      //j for traverse template, k is failure index
    char *p = template;

    //init iteration
    next[0] = -1;

    //recursion
    while(j < size-1) {
        if(k == -1 || p[j] == p[k]) {
#if (OPT == 0)
            next[++j] = ++k;
#else
            if(p[++j] == p[++k]) {
                next[j] = next[k];
            }
            else {
                next[j] = k;
            }
#endif
        } else {
            k = next[k];
        }
    }

    return 0;
}

int KMP(const char* target, int target_size, const char* template, int template_size) {
    int i = 0, j = 0;                //index for traverse target, template
    char *p = template;
    char *t = target;

    char *next = (char*)malloc(sizeof(char)*template_size);
    if (NULL == next) {
        printf("[kmp] memory allocate fail!\n");
        return -1;
    }
    memset(next, 0, sizeof(char)*template_size);
    GetFailureFunction(next, template_size, template);

    while(i < target_size && j < template_size) {
        if (j == -1 || p[j] == t[i]) {              //when j is -1, we need to set i=i+1; then, set j from 0 (j=j+1) of course.
            j++;
            i++;
        }
        else {
            j = next[j];
        }
    }

    if (next)
        free(next);
    return i-j;
}


int main(int argc, char* argv[]) {
//    char target_array[] = "ABACBCDHI";
//    char template_array[] = "ABAB";
//    int template_size = strlen(template_array);
//    int target_size = strlen(target_array);
    char *target_array = (char*) malloc(MAX_INPUT_LEN * sizeof(char));
    char *template_array = (char*) malloc(MAX_INPUT_LEN * sizeof(char));
    int template_size = 0;
    int target_size = 0;
    ssize_t ret = 0;
    int max_index = -1;

    printf("please input template array:\n");
    fgets(template_array, MAX_INPUT_LEN*sizeof(char), stdin);
    template_size = strlen(template_array) - 1;                     //-1 for removing last '\n'
    printf("teamplate:%s", template_array);
    printf("teamplate len: %d\n", template_size);

    printf("please input template array:\n");
    fgets(target_array, MAX_INPUT_LEN*sizeof(char), stdin);
    target_size = strlen(target_array) - 1;                         //-1 for removing last '\n'
    printf("target_array:%s", target_array);
    printf("target_array len: %d\n", target_size);

    max_index = KMP(target_array, target_size, template_array, template_size);
    printf("index in target is:%d\n", max_index);

    free(target_array);
    free(template_array);
    return 0;
}
