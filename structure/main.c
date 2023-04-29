#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct{
  int index;
  char name[MAX];
  float start_value;
  float end_value;
  int num_of_trades;
} Scompany;

int max(Scompany *array,int max,int loop,char* value){

     max = 0;
    for(int i=0; i<loop; i++){
        if(strcmp(array[i].name,value) == 0){
            if(array[i].num_of_trades > max){
                max = array[i].num_of_trades;
            }
        }
    }
    return max;
}

void print_main_value(int loop, Scompany *array,char* m_value, int max){
  printf("<div>\n");
    for(int i=0; i<loop; i++){
      if(array[i].num_of_trades == max){

         printf("<h1>%s: highest volume</h1>\n",array[i].name);
         printf("<div>Day: %d</div>\n",array[i].index);
         printf("<div>Start price: %.2f</div>\n",array[i].start_value);
         printf("<div>End price: %.2f</div>\n",array[i].end_value);
         printf("<div>Volume: %d</div>\n",array[i].num_of_trades);
      } 
    }

    if(max == 0){
      printf("Ticker %s was not found\n",m_value);
    }
printf("</div>\n");
}

void print_values(int loop,Scompany *array, char *m_value){
   printf("<ul>\n");
    for(int i=0; i<loop; i++){
      printf("<li>");

      if (strcmp(array[loop-i-1].name,m_value)==0) printf("<b>");
      printf("Day: %d, ticker: %s, start: %.2f, end: %.2f, diff: %.2f, volume: %d",array[loop-i-1].index,array[loop-i-1].name,array[loop-i-1].start_value,array[loop-i-1].end_value,(array[loop-i-1].end_value - array[loop-i-1].start_value),array[loop-i-1].num_of_trades);
      if (strcmp(array[loop-i-1].name,m_value)==0) printf("</b>");

      printf("</li>\n");
    }
  printf("</ul>\n");
}

int main(int argc, char** argv){
    int loop;
    char buffer[101];
    const char *start ="<html>\n<body>\n";
    const char *end = "</body>\n</html>\n";

    if(argv[1] == NULL || argv[2] == NULL){
      printf("Wrong parameters\n");
        return 1;
    }
    
    loop = atoi(argv[2]);
    char *m_value = (char*)malloc(sizeof(char*));
    Scompany *array = malloc(sizeof(Scompany)*loop);
    strcpy(m_value,argv[1]);

    for(int i=0; i<loop; i++){
  
    fgets(buffer,sizeof(buffer),stdin);
    array[i].index = atoi(strtok(buffer,","));
    strcpy(array[i].name,strtok(NULL,","));
    array[i].start_value = atof(strtok(NULL,","));
    array[i].end_value = atof(strtok(NULL,","));
    array[i].num_of_trades = atoi(strtok(NULL,"\n"));

    }
int m,tmp;
m = max(array,tmp,loop,m_value);


printf("%s",start);

print_main_value(loop,array,m_value,m);
print_values(loop,array,m_value);


printf("%s",end);


free(m_value);
free(array);

  return 0;
}