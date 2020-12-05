/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：kmp_test.c
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-12-05
*   Description   ：
*
================================================================*/


#include "stdio.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>

int GetFailureFunction(char* next, int size, const char* template) {
    int j=0, k=-1;      //j for traverse template, k is failure index
    char *p = template;

    //init iteration
    next[0] = -1;

    //recursion
    while(j < size-1) {
        if(k == -1 || p[j] == p[k]) {
            //next[++j] = ++k;
            if(next[++j] == next[++k]) {
                next[j] = next[k];
            }
            else {
                next[j] = k;
            }
        } else {
            k = next[k];
        }
    }

    return 0;
}

int KMP(const char* target, int target_size, const char* template, int template_size) {
    int i = 0, j = 0;                //index for traverse target, template
    int k = -1;                      //failure function index
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
        if (k == -1 || p[j] == t[i]) {
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
    char target_array[] = "ABACBCDHI";
    char template_array[] = "ABAB";
    int max_index = -1;

    int template_size = strlen(template_array);
    int target_size = strlen(target_array);
    printf("template:%s len:%d\n", template_array, template_size);
    printf("target:%s len:%d\n", target_array, target_size);

    max_index = KMP(target_array, target_size, template_array, template_size);
    printf("template(%s) index in target(%s) is:%d\n", template_array, target_array, max_index);
    return 0;
}
