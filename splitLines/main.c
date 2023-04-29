#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void tok(char* token, char **dp_array,int rows){
int tmp=0;
    for(int i=0;i<rows;i++){
    token = strtok(dp_array[i]," ");
    
    while(token != NULL){

        printf("Slovo %d: %s\n",tmp,token);
        token = strtok(NULL," ");
        tmp++;
     }
    }


    
}

int main(){
char p_rows[5],array[101];
int rows;

fgets(p_rows,sizeof(p_rows),stdin);
rows = atoi(p_rows);


char **dp_array = (char**)malloc(sizeof(array)*rows);
char* token = (char*)malloc(sizeof(char)*101*rows);

for(int i=0;i<rows;i++){
    dp_array[i] = (token + 101 * i);
}

for(int i=0;i<rows;i++){
    
     fgets(array,sizeof(array),stdin);

    
    array[strcspn(array, "\n")] = ' ';

     strcpy(dp_array[i],array);

   
}

tok(token,dp_array,rows);
    

free(token);
free(dp_array);

return 0;
}

