#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int dictionary_capacity(char *dict_path,Array a){
    FILE *f = fopen(dict_path,"r");

    if(f == NULL){
        return false;
    }

    char buffer[50];
    int size=0;
    
    while(fgets(buffer,sizeof(buffer),f)){
        size++;
    }
    

    fclose(f);
    return size;
}

bool dictionary_scan(char* dict_path,Dictionary *a){
    FILE *f = fopen(dict_path,"r");

    if(f==NULL){
        return false;
    }

    int i=0;
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),f)){
        a[i].english = strdup(strtok(buffer,","));
        a[i].czech = strdup(strtok(NULL,"\n")); 
        i++;
    }

    
    fclose(f);
    return true;
}


bool input_file(Dictionary *a,char *input_path,char* output_path,int size){
    FILE *f = fopen(input_path,"r");
    

    if(f == NULL){
        printf("Could not open input file");
        return false;
    }
    
    FILE *fo = fopen(output_path,"w");
    if(fo == NULL){
        printf("Could not open output file");
        return false;
    }

    char buffer[256];
    char *token;

    while(fgets(buffer,sizeof(buffer),f)){
        buffer[strcspn(buffer, "\n")] = '\0';

        token = strtok(buffer," ");
        
        while(token != NULL){

            int flag = 0;
            for(int i = 0; i < size; i++){

                if(!strcmp(token,a[i].english)){
                    fprintf(fo, "%s ", a[i].czech);
                    flag = 1;
                    break;
                }
            }
            if(!flag){
                fprintf(fo,"<unknown> ");
            }
        
        token = strtok(NULL," ");
        }
        fprintf(fo, "\n");
     }   
     
    
    fclose(fo);
    fclose(f);
    return true;
}