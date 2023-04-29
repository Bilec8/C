#include "array.h"


int main(int argc, char **argv){

    if(argc<4){
        printf("Wrong parameters");
        return 1;
    }


    Array a;
    

    char *dict_path = argv[1];
    char *input_path = argv[2];
    char *output_path = argv[3];

    int size;
    size = dictionary_capacity(dict_path,a);

    if(size == 0 && argc == 3){

    }

    Dictionary *array = malloc(sizeof(Dictionary)*size);

    if(!dictionary_scan(dict_path,array)){
        printf("Could not load dictionary");
            for(int i=0;i<size;i++){
                free(array[i].english);
                free(array[i].czech);
            }
        free(array);
        return 1;
    }

    if(!input_file(array,input_path,output_path,size)){
        for(int i=0;i<size;i++){
            free(array[i].english);
            free(array[i].czech);
    }
        free(array);
        return 1;
    }


    for(int i=0;i<size;i++){
        free(array[i].english);
        free(array[i].czech);
    }

    free(array);

return 0;
}