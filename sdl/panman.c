#include "panman.h"

int numberCoins(char *path,char character){
    FILE *f = fopen(path,"rt");

    if(f == NULL){
        return 1;
    }

    char buffer[WIN_W];
    int n_coin=0;

    while(fgets(buffer,sizeof(buffer),f)){
        for(int i=0;buffer[i] != '\n';i++){
            if(buffer[i] == character){
                n_coin++;
            }
        }
    }


    fclose(f);
    return n_coin;
}

SDL_Texture *LoadImage(SDL_Renderer *renderer,char *path){
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *image = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    return image;
}

SDL_Texture *LoadText(SDL_Renderer *renderer,TTF_Font *font,SDL_Color color, char *text){
    SDL_Surface *surface = TTF_RenderText_Solid(font,text,color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Point getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}
void LoadImageS(SDL_Renderer *renderer,int numCoins,CoinS *coinTex){

    for(int i=0;i<numCoins;i++){
        SDL_Surface *surface = IMG_Load("images/coin/coin.png");
        coinTex[i].coin_texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
}

void LoadImageB(SDL_Renderer *renderer,int numCoins,BCoinS *coinTex){

    for(int i=0;i<numCoins;i++){
        SDL_Surface *surface = IMG_Load("images/coin/n_coin.png");
        coinTex[i].coin_texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
}

void LoadTextS(SDL_Renderer *renderer,Text_Score *scoreStruct,int numCoins,TTF_Font *font,SDL_Color color){
    char buffer[TEXT];

    for(int i=0;i<=numCoins;i++){
        sprintf(buffer,"Score: %d",i);
        SDL_Surface *surface = TTF_RenderText_Solid(font,buffer,color);
        scoreStruct[i].text_texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
}

SDL_Point mapSize(char *path){
    FILE *f = fopen(path,"rt");

    char buffer[WIN_W];
    SDL_Point map;
    map.x = 0;
    map.y = 0;

    while(fgets(buffer,sizeof(buffer),f)){
    map.x = 0;
        for(int i=0;buffer[i] != '\0';i++){
                map.x++;
            
            
        }
        map.y++;
    }

    fclose(f);
    return map;
}
