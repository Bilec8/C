#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char *english;
    char *czech;
}Dictionary;
    
typedef struct{
    int capacity;
    Dictionary size;
}Array;

int  dictionary_capacity(char* dict_path,Array a);
bool dictionary_scan(char* dict_path,Dictionary *a);
bool input_file(Dictionary *a,char *input_path,char* output_path,int size);