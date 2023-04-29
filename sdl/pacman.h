#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define GAME_FONT 30
#define MENU_FONT 60
#define TITLE_FONT 100
#define MOVE_PIX 3
#define WIN_X 100
#define MENU_H 40
#define MAP_Y 100
#define MENU_W 120
#define WIN_Y 100
#define WIN_W 800
#define WIN_H 600
#define TEXT 20
#define PANMAN_W 20
#define BORDER_H 20
#define BORDER_W 20
#define PANMAN_H 20
#define ERROR_INDEX -5

#define panman_h

    typedef struct{
        SDL_Texture *coin_texture;
    }CoinS;

    typedef struct{
        SDL_Texture *coin_texture;
    }BCoinS;

    typedef struct{
        SDL_Texture *text_texture;
    }Text_Score; 

    typedef struct{
        SDL_Surface *lives;
        SDL_Texture *lives_texture;
    }Lives; 

int numberCoins(char *path,char character);
SDL_Texture *LoadImage(SDL_Renderer *renderer,char *path);
SDL_Texture *LoadText(SDL_Renderer *renderer,TTF_Font *font,SDL_Color color, char *text);
void LoadTextS(SDL_Renderer *renderer,Text_Score *scoreStruct,int numCoins,TTF_Font *font,SDL_Color color);
SDL_Point getsize(SDL_Texture *texture);
SDL_Point mapSize(char* path);
int movement(SDL_Rect panman,SDL_Rect ghost,int flag_lr,int flag_ud,char flag_ghost_red );
void LoadImageS(SDL_Renderer *renderer,int numCoins,CoinS *coinTex);
void LoadImageB(SDL_Renderer *renderer,int numCoins,BCoinS *coinTex);