#include "panman.h"


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Moje SDL okno", WIN_X, WIN_Y, WIN_W, WIN_H, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    int ghost_speed = 1;
    int numCatches = 3;

    SDL_Rect map;
    TTF_Font *fontGame = TTF_OpenFont("font/OpenSans-Bold.ttf",GAME_FONT);
    TTF_Font *fontMenu = TTF_OpenFont("font/OpenSans-Bold.ttf",MENU_FONT);
    TTF_Font *fontTitleMenu = TTF_OpenFont("font/OpenSans-Bold.ttf",TITLE_FONT);

    SDL_Color white = {255,255,255,255};
    SDL_Color red = {194, 24, 7,255};
    SDL_Color yellow = {255, 218, 0, 0};
    
    int numCoins = numberCoins("maps/map2.txt",'c');
    int numBCoins = numberCoins("maps/map2.txt",'b');
    
    SDL_Texture *sizeCoin = LoadImage(renderer,"images/coin/coin.png");
    SDL_Point point = getsize(sizeCoin);

    SDL_Texture *sizeBCoin = LoadImage(renderer,"coin/n_coin.png");
    SDL_Point Bpoint = getsize(sizeBCoin);

    char sizeScoreBuffer[TEXT];
    sprintf(sizeScoreBuffer,"Score: %d",numCoins+1);

    SDL_Texture *sizeText = LoadText(renderer,fontGame,white,sizeScoreBuffer);
    SDL_Point sizeOfScore = getsize(sizeText);

    //Vytvoreni surface a texture pro panmana
    SDL_Texture *panmanL = LoadImage(renderer,"images/panman/panman.png");
    SDL_Texture *panmanR = LoadImage(renderer,"images/panman/panman.png");
    SDL_Texture *panmanU = LoadImage(renderer,"images/panman/panman.png");
    SDL_Texture *panmanD = LoadImage(renderer,"images/panman/panman.png");

    //Vytvoreni surface a texture pro ghosty
    SDL_Texture *rGhostR= LoadImage(renderer,"images/r_ghost/red_g_r.png");
    SDL_Texture *rGhostL= LoadImage(renderer,"images/r_ghost/red_g_l.png");
    SDL_Texture *rGhostD= LoadImage(renderer,"images/r_ghost/red_g_d.png");
    SDL_Texture *rGhostU= LoadImage(renderer,"images/r_ghost/red_g_u.png");

    SDL_Texture *yGhostR= LoadImage(renderer,"images/y_ghost/y_g_r.png");
    SDL_Texture *yGhostU= LoadImage(renderer,"images/y_ghost/y_g_u.png");
    SDL_Texture *yGhostD= LoadImage(renderer,"images/y_ghost/y_g_d.png");
    SDL_Texture *yGhostL= LoadImage(renderer,"images/y_ghost/y_g_l.png");

    SDL_Texture *pGhostR= LoadImage(renderer,"images/p_ghost/p_g_r.png");
    SDL_Texture *pGhostL= LoadImage(renderer,"images/p_ghost/p_g_l.png");

    SDL_Texture *brGhostR= LoadImage(renderer,"images/br_ghost/br_g_r.png");
    SDL_Texture *brGhostL= LoadImage(renderer,"images/br_ghost/br_g_l.png");
    

    SDL_Texture *ghostHunted = LoadImage(renderer,"images/hunted/hunted.png");

    //Struktura pro mince
    CoinS *s_coin = malloc(sizeof(point)*numCoins);
    LoadImageS(renderer,numCoins,s_coin);

    BCoinS *b_coin = malloc(sizeof(Bpoint)*numBCoins);
    LoadImageB(renderer,numBCoins,b_coin);
    
    Text_Score *s_text = malloc(sizeof(sizeOfScore)*numCoins+10);
    LoadTextS(renderer,s_text,numCoins,fontGame,white);
    
    char coinTextN[TEXT];

    Lives *s_lives = malloc(sizeof(SDL_Surface)*4);
    char number_of_lives[TEXT];

    for(int i=0;i<=3;i++){
        sprintf(number_of_lives,"Lives: %d",i);
        s_lives[i].lives = TTF_RenderText_Solid(fontGame,number_of_lives,white);
        s_lives[i].lives_texture = SDL_CreateTextureFromSurface(renderer,s_lives[i].lives);
        SDL_FreeSurface(s_lives[i].lives);
    }

    SDL_Rect scoreText = {WIN_W/2-50,0,100,40};

    SDL_Texture *playButton = LoadText(renderer,fontMenu,white,"PLAY GAME");
    SDL_Texture *titleMenu = LoadText(renderer,fontTitleMenu,yellow,"PANMAN");
    SDL_Texture *settings = LoadText(renderer,fontMenu,white,"SETTINGS");

    SDL_Texture *endScreen = LoadText(renderer,fontMenu,white,"GAME OVER!");
    SDL_Texture *winScreen = LoadText(renderer,fontMenu,white,"YOU WON!");

    SDL_Texture *ghosts = LoadText(renderer,fontMenu,yellow,"GHOSTS");
    SDL_Texture *mapType = LoadText(renderer,fontMenu,yellow,"PANMAN");
    SDL_Texture *back = LoadText(renderer,fontMenu,yellow,"BACK");
    SDL_Texture *mapEasy = LoadText(renderer,fontMenu,white,"EASY");
    SDL_Texture *mapMedium = LoadText(renderer,fontMenu,white,"MEDIUM");
    SDL_Texture *mapHard = LoadText(renderer,fontMenu,white,"HARD");

    SDL_Texture *mapEasyS = LoadText(renderer,fontMenu,red,"EASY");
    SDL_Texture *mapMediumS= LoadText(renderer,fontMenu,red,"MEDIUM");
    SDL_Texture *mapHardS = LoadText(renderer,fontMenu,red,"HARD");

    SDL_Rect menu_place;
    menu_place.h = MENU_H;
    menu_place.w = MENU_W;
    menu_place.y = WIN_H/2 - menu_place.h/2;
    menu_place.x = WIN_W/2 - menu_place.w/2;

    SDL_Rect settings_place;
    settings_place.h = menu_place.h;
    settings_place.w = menu_place.w;
    settings_place.y = (WIN_H/2 - settings_place.h/2) + menu_place.h + 20;   //20 pro misto mezi textem
    settings_place.x = WIN_W/2 - settings_place.w/2;

    SDL_Rect map_place;
    map_place.h = menu_place.h;
    map_place.w = menu_place.w;
    map_place.x = WIN_W/4 - map_place.w;  
    map_place.y = MAP_Y;

    SDL_Rect back_place;
    back_place.h = menu_place.h;
    back_place.w = menu_place.w;
    back_place.x = WIN_W/2 - back_place.w/2;   
    back_place.y = WIN_H - 100;

    SDL_Rect map_easy_place;
    map_easy_place.h = menu_place.h;
    map_easy_place.w = menu_place.w;
    map_easy_place.x = WIN_W/4 - map_place.w; 
    map_easy_place.y = map_place.y + 50 + map_place.h;

    SDL_Rect map_medium_place;
    map_medium_place.h = menu_place.h;
    map_medium_place.w = menu_place.w;
    map_medium_place.x = WIN_W/4 - map_place.w; 
    map_medium_place.y = map_easy_place.y + 50 + map_easy_place.h;

    SDL_Rect map_hard_place;
    map_hard_place.h = menu_place.h;
    map_hard_place.w = menu_place.w;
    map_hard_place.x = WIN_W/4 - map_place.w; 
    map_hard_place.y = map_medium_place.y + 50 + map_medium_place.h;

    SDL_Rect ghost_title_place;
    ghost_title_place.h = menu_place.h;
    ghost_title_place.w = menu_place.w;
    ghost_title_place.x = WIN_W/2 + ghost_title_place.w + ghost_title_place.w/2;  
    ghost_title_place.y = MAP_Y;

    SDL_Rect ghost_easy;
    ghost_easy.h = menu_place.h;
    ghost_easy.w = menu_place.w;
    ghost_easy.x = ghost_title_place.x;   
    ghost_easy.y = map_easy_place.y;

    SDL_Rect ghost_medium;
    ghost_medium.h = menu_place.h;
    ghost_medium.w = menu_place.w;
    ghost_medium.x = ghost_title_place.x;
    ghost_medium.y = map_medium_place.y;

    SDL_Rect ghost_hard;
    ghost_hard.h = menu_place.h;
    ghost_hard.w = menu_place.w;
    ghost_hard.x = ghost_title_place.x;
    ghost_hard.y = map_hard_place.y;

    SDL_Rect lives_text;
    lives_text.h = scoreText.h;
    lives_text.w = scoreText.w;
    lives_text.x = lives_text.y = 0;

    SDL_Rect title_place;
    title_place.h = 100;
    title_place.w = 300;
    title_place.y = menu_place.y - 100 - title_place.h;
    title_place.x = WIN_W/2 - (title_place.w/2); 

    TTF_CloseFont(fontGame);
    TTF_CloseFont(fontMenu);
    TTF_CloseFont(fontTitleMenu);

    SDL_Event e;
    bool quit = false;
    SDL_Rect texture;
    texture.w = PANMAN_W-5;
    texture.h = PANMAN_H-5;

    SDL_Rect r_ghost;
    r_ghost.w = r_ghost.h = texture.h;

    SDL_Rect y_ghost;
    y_ghost.w = y_ghost.h = texture.h;

    SDL_Rect p_ghost;
    p_ghost.w = p_ghost.h = texture.h;

    SDL_Rect br_ghost;
    br_ghost.w = br_ghost.h = texture.h;

    SDL_Rect starting_pos_panman;
    starting_pos_panman.h = texture.h;
    starting_pos_panman.w = texture.w;

    SDL_Rect starting_pos_r_ghost;
    starting_pos_r_ghost.h = r_ghost.h;
    starting_pos_r_ghost.w = r_ghost.w;

    SDL_Rect starting_pos_y_ghost;
    starting_pos_y_ghost.w = starting_pos_y_ghost.h = y_ghost.h;

    SDL_Rect starting_pos_p_ghost;
    starting_pos_p_ghost.w = starting_pos_p_ghost.h = y_ghost.h;

    SDL_Rect starting_pos_br_ghost;
    starting_pos_br_ghost.w = starting_pos_br_ghost.h = y_ghost.h;

    int score=0;

    int catchHunter = 0;
    int hunter = 0;
    int flag_border_r = 0;
    int flag_border_l = 0;
    int flag_border_u = 0;
    int flag_border_d = 0;
    
    int flag_menu = 1;
    int flag_settings = 1;
    int flag_back = 0;

    char flag_position = 'r';
    char flag_ghost_red = 'r';
    char flag_ghost_y = 'r';
    char flag_ghost_br = 'r';
    char flag_ghost_p = 'r';

    int flag_map_select = 10;
    int flag_ghost_select = 10;

    int movementFlagR = 0;
    int movementFlagY = 0;
    int movementFlagBr = 0;
    int movementFlagP = 0;

    int n_lives = 4;

    int panman_starting_pos = 0;
    int r_starting_pos = 0;
    int y_starting_pos = 0;
    int p_starting_pos = 0;
    int br_starting_pos = 0;

    SDL_Rect mouse_motion;

    int *token = (int*)malloc(sizeof(int)*numCoins);

    for(int i=0;i<numCoins;i++){
        token[i] = ERROR_INDEX;
    }

    int *token2 = (int*)malloc(sizeof(int)*numBCoins);

    for(int i=0;i<numBCoins;i++){
        token2[i] = ERROR_INDEX;
    }

    while (!quit){


        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                
                flag_position = 0;

                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        flag_position = 'r';
                            if(flag_border_r == 0){
                                texture.x += MOVE_PIX;
                            }
                            flag_border_l = 0;
                            flag_border_u = 0;
                            flag_border_d = 0;
                    break;
                    
                    case SDLK_LEFT:
                        flag_position = 'l';
                            if(flag_border_l == 0){
                                texture.x -= MOVE_PIX;
                            }        
                        flag_border_r = 0;
                        flag_border_u = 0;
                        flag_border_d = 0;
                    break;
                    case SDLK_DOWN:
                        flag_position = 'd';
                            if(flag_border_d == 0){
                                texture.y += MOVE_PIX;
                            }
                        flag_border_r = 0;
                        flag_border_u = 0;
                        flag_border_l = 0;
                    break;
                    case SDLK_UP:
                        flag_position = 'u';
                            if(flag_border_u == 0){
                                texture.y -= MOVE_PIX;
                            }
                        flag_border_r = 0;
                        flag_border_l = 0;
                        flag_border_d = 0;
                    break;
                    
                    }
                
            }else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_LEFT){
                    mouse_motion.x = e.button.x;
                    mouse_motion.y = e.button.y;
                    mouse_motion.h = menu_place.h;
                    mouse_motion.w = menu_place.w;

                    if(SDL_HasIntersection(&menu_place,&mouse_motion)){
                        flag_menu = 0;
                    }
                    if(SDL_HasIntersection(&settings_place,&mouse_motion)){
                        flag_settings = 0;
                    }
                    if(SDL_HasIntersection(&back_place,&mouse_motion)){
                        flag_back = 1;
                    }
                    if(SDL_HasIntersection(&map_easy_place,&mouse_motion)){
                        flag_map_select = 1;
                        numCatches = 4;
                        
                    }
                    if(SDL_HasIntersection(&map_medium_place,&mouse_motion)){
                        flag_map_select = 2;
                        numCatches = 3;
                    }
                    if(SDL_HasIntersection(&map_hard_place,&mouse_motion)){
                        flag_map_select = 3;
                        numCatches = 2;
                    }


                    if(SDL_HasIntersection(&ghost_easy,&mouse_motion)){
                        flag_ghost_select = 1;
                        ghost_speed = 1;
                    }
                    if(SDL_HasIntersection(&ghost_medium,&mouse_motion)){
                        flag_ghost_select = 2;                        
                        ghost_speed = 1;
                    }
                    if(SDL_HasIntersection(&ghost_hard,&mouse_motion)){
                        flag_ghost_select = 3;
                        ghost_speed = 1;
                    }
                
                } 
            }
        }


     if(flag_menu == 1){
        
            if(flag_settings == 1){
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer,titleMenu,NULL,&title_place);
                SDL_RenderCopy(renderer,playButton,NULL,&menu_place);
                SDL_RenderCopy(renderer,settings,NULL,&settings_place);
                SDL_RenderPresent(renderer);
            }
                if(flag_settings == 0){
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer,mapType,NULL,&map_place);
                    SDL_RenderCopy(renderer,back,NULL,&back_place);
                    
                    SDL_RenderCopy(renderer,mapEasy,NULL,&map_easy_place);
                    SDL_RenderCopy(renderer,mapMedium,NULL,&map_medium_place);
                    SDL_RenderCopy(renderer,mapHard,NULL,&map_hard_place);

                    SDL_RenderCopy(renderer,ghosts,NULL,&ghost_title_place);

                    SDL_RenderCopy(renderer,mapEasy,NULL,&ghost_easy);
                    SDL_RenderCopy(renderer,mapMedium,NULL,&ghost_medium);
                    SDL_RenderCopy(renderer,mapHard,NULL,&ghost_hard);

                        if(flag_map_select == 1){
                            SDL_RenderCopy(renderer,mapEasyS,NULL,&map_easy_place);
                            SDL_RenderCopy(renderer,mapMedium,NULL,&map_medium_place);
                            SDL_RenderCopy(renderer,mapHard,NULL,&map_hard_place);
                        }

                        if(flag_map_select == 2){
                            SDL_RenderCopy(renderer,mapEasy,NULL,&map_easy_place);
                            SDL_RenderCopy(renderer,mapMediumS,NULL,&map_medium_place);
                            SDL_RenderCopy(renderer,mapHard,NULL,&map_hard_place);                        
                        }

                        if(flag_map_select == 3){
                            SDL_RenderCopy(renderer,mapEasy,NULL,&map_easy_place);
                            SDL_RenderCopy(renderer,mapMedium,NULL,&map_medium_place);
                            SDL_RenderCopy(renderer,mapHardS,NULL,&map_hard_place);                         
                            }

                        if(flag_ghost_select == 1){
                            SDL_RenderCopy(renderer,mapEasyS,NULL,&ghost_easy);
                            SDL_RenderCopy(renderer,mapMedium,NULL,&ghost_medium);
                            SDL_RenderCopy(renderer,mapHard,NULL,&ghost_hard);    
                        }

                        if(flag_ghost_select == 2){
                            SDL_RenderCopy(renderer,mapEasy,NULL,&ghost_easy);
                            SDL_RenderCopy(renderer,mapMediumS,NULL,&ghost_medium);
                            SDL_RenderCopy(renderer,mapHard,NULL,&ghost_hard);                           
                        }

                        if(flag_ghost_select == 3){
                            SDL_RenderCopy(renderer,mapEasy,NULL,&ghost_easy);
                            SDL_RenderCopy(renderer,mapMedium,NULL,&ghost_medium);
                            SDL_RenderCopy(renderer,mapHardS,NULL,&ghost_hard);                          
                            }

                }        
     } 

    if(flag_back == 1){
         flag_menu = 1;
         flag_settings = 1;  
         flag_back = 0;
    }  

    if(numCoins != score){
        if(n_lives != 0){     
            if(flag_menu == 0){
        
        //Movement for yellow ghost
          if(y_ghost.x >= texture.x){
                if(movementFlagY == 0){
                    y_ghost.x -= ghost_speed;
                    flag_ghost_y = 'l';
                }
                
                if(y_ghost.y == texture.y || y_ghost.x == texture.x || movementFlagY == 1){
                        if(y_ghost.y >= texture.y){
                            y_ghost.y -= ghost_speed;
                            flag_ghost_y = 'u';
                        }

                    if(y_ghost.y <= texture.y){
                        y_ghost.y +=ghost_speed;
                        flag_ghost_y = 'd';
                        }

                    if(movementFlagY == 1 && y_ghost.x >= texture.x){
                        movementFlagY = 0;
                    }    
                }   
            }

            
            if(y_ghost.x <= texture.x){
                if(movementFlagY == 0){
                    y_ghost.x += ghost_speed;
                    flag_ghost_y = 'r'; 
                }
                
                if(y_ghost.y == texture.y || y_ghost.x == texture.x || movementFlagY == 1){
                    if(y_ghost.y >= texture.y){
                        y_ghost.y -= ghost_speed;
                        flag_ghost_y = 'u';
                    }
                    
                    if(y_ghost.y <= texture.y){
                       y_ghost.y +=ghost_speed;
                        flag_ghost_y = 'd';
                    }

                    if(movementFlagY == 1 && r_ghost.x <= texture.x){
                        movementFlagY = 0;
                    }
                }
            }

        //Movement for red ghost
            if(r_ghost.x >= texture.x){
                if(movementFlagR == 0){
                    r_ghost.x -= ghost_speed;
                    flag_ghost_red = 'l';
                }
                
                if(r_ghost.y == texture.y || r_ghost.x == texture.x || movementFlagR == 1){
                        if(r_ghost.y >= texture.y){
                            r_ghost.y -= ghost_speed;
                            flag_ghost_red = 'u';
                        }

                    if(r_ghost.y <= texture.y){
                        r_ghost.y +=1;
                        flag_ghost_red = 'd';
                        }

                    if(movementFlagR == 1 && r_ghost.x >= texture.x){
                        movementFlagR = 0;
                    }    
                }   
            }

            
            if(r_ghost.x <= texture.x){
                if(movementFlagR == 0){
                    r_ghost.x += ghost_speed;
                    flag_ghost_red = 'r'; 
                }
                
                if(r_ghost.y == texture.y || r_ghost.x == texture.x || movementFlagR == 1){
                    if(r_ghost.y >= texture.y){
                        r_ghost.y -= ghost_speed;
                        flag_ghost_red = 'u';
                    }
                    
                    if(r_ghost.y <= texture.y){
                        r_ghost.y += ghost_speed;
                        flag_ghost_red = 'd';
                    }

                    if(movementFlagR == 1 && r_ghost.x <= texture.x){
                        movementFlagR = 0;
                    }
                }
            }

        //Movement for pink ghost
            if(p_ghost.x >= texture.x){
                if(movementFlagP == 0){
                    p_ghost.x -= ghost_speed;
                    flag_ghost_p = 'l';
                }
                
                if(p_ghost.y == texture.y || p_ghost.x == texture.x || movementFlagP == 1){
                        if(p_ghost.y >= texture.y){
                            p_ghost.y -= ghost_speed;
                        }

                    if(p_ghost.y <= texture.y){
                        p_ghost.y +=1;
                        }

                    if(movementFlagP == 1 && p_ghost.x >= texture.x){
                        movementFlagP = 0;
                    }    
                }   
            }

            
            if(p_ghost.x <= texture.x){
                if(movementFlagP == 0){
                    p_ghost.x += ghost_speed;
                    flag_ghost_p = 'r'; 
                }
                
                if(p_ghost.y == texture.y || p_ghost.x == texture.x || movementFlagP == 1){
                    if(p_ghost.y >= texture.y){
                        p_ghost.y -= ghost_speed;
                    }
                    
                    if(p_ghost.y <= texture.y){
                        p_ghost.y += ghost_speed;
                    }

                    if(movementFlagP == 1 && p_ghost.x <= texture.x){
                        movementFlagP = 0;
                    }
                }
            }

        //Movement for brown ghost
            if(br_ghost.x >= texture.x){
                if(movementFlagBr == 0){
                    br_ghost.x -= ghost_speed;
                    flag_ghost_br = 'l';
                }
                
                if(br_ghost.y == texture.y || br_ghost.x == texture.x || movementFlagBr == 1){
                        if(br_ghost.y >= texture.y){
                            br_ghost.y -= ghost_speed;
                        }

                    if(br_ghost.y <= texture.y){
                        br_ghost.y +=1;
                        }

                    if(movementFlagBr == 1 && br_ghost.x >= texture.x){
                        movementFlagBr = 0;
                    }    
                }   
            }

            
            if(br_ghost.x <= texture.x){
                if(movementFlagBr == 0){
                    br_ghost.x += ghost_speed;
                    flag_ghost_br = 'r'; 
                }
                
                if(br_ghost.y == texture.y || br_ghost.x == texture.x || movementFlagBr == 1){
                    if(br_ghost.y >= texture.y){
                        br_ghost.y -= ghost_speed;
                    }
                    
                    if(br_ghost.y <= texture.y){
                        br_ghost.y += ghost_speed;
                    }

                    if(movementFlagBr == 1 && p_ghost.x <= texture.x){
                        movementFlagBr = 0;
                    }
                }
            }   

        SDL_SetRenderDrawColor(renderer, 130, 180, 45, 99);

        SDL_RenderClear(renderer);


       
        if((SDL_HasIntersection(&texture,&r_ghost) == SDL_TRUE) || (SDL_HasIntersection(&texture,&y_ghost) == SDL_TRUE) || ((SDL_HasIntersection(&texture,&p_ghost) == SDL_TRUE)) || ((SDL_HasIntersection(&texture,&br_ghost) == SDL_TRUE))){
            if(hunter == 0){
            texture.x = starting_pos_panman/x;
            texture.y = starting_pos_panman.y;

            r_ghost.x = starting_pos_r_ghost.x;
            r_ghost.y = starting_pos_r_ghost.y;

            y_ghost.x = starting_pos_y_ghost.x;
            y_ghost.y = starting_pos_y_ghost.y;

            p_ghost.x = starting_pos_p_ghost.x;
            p_ghost.y = starting_pos_p_ghost.y;

            br_ghost.x = starting_pos_br_ghost.x;
            br_ghost.y = starting_pos_br_ghost.y;

            n_lives--;
            
            }
            if(hunter == 1){
                if((SDL_HasIntersection(&texture,&r_ghost) == SDL_TRUE)){
                    r_ghost.x = starting_pos_r_ghost.x;
                    r_ghost.y = starting_pos_r_ghost.y;
                    catchHunter++;
                }
                if((SDL_HasIntersection(&texture,&y_ghost) == SDL_TRUE)){
                    y_ghost.x = starting_pos_y_ghost.x;
                    y_ghost.y = starting_pos_y_ghost.y;
                    catchHunter++;
                }

                if((SDL_HasIntersection(&texture,&p_ghost) == SDL_TRUE)){
                    p_ghost.x = starting_pos_p_ghost.x;
                    p_ghost.y = starting_pos_p_ghost.y;
                    catchHunter++;
                }

                if((SDL_HasIntersection(&texture,&br_ghost) == SDL_TRUE)){
                    br_ghost.x = starting_pos_br_ghost.x;
                    br_ghost.y = starting_pos_br_ghost.y;
                    catchHunter++;
                }


                if(catchHunter >= numCatches){
                    hunter = 0;
                    catchHunter = 0;
                }
            }
        }
        



        switch(flag_position){
            case 'r':
                SDL_RenderCopy(renderer,panmanR,NULL,&texture);

            break;
            case 'l':
                SDL_RenderCopy(renderer,panmanL,NULL,&texture);

            break;
            case 'd':
                SDL_RenderCopy(renderer,panmanD,NULL,&texture);

            break;            
            case 'u':
                SDL_RenderCopy(renderer,panmanU,NULL,&texture);
            break;
        }

    FILE *f = fopen("maps/map2.txt","rt");

    SDL_Point a = mapSize("maps/map2.txt");
    char buffer[WIN_W];

    map.x = 0;
    map.y = 50; 
    map.h = PANMAN_H;
    map.w = PANMAN_H;

    if(f == NULL){
        return false;
    }
    
    SDL_Rect coin_place;
    coin_place.h=coin_place.w = 20;

    SDL_Rect b_coin_place;
    b_coin_place.h = b_coin_place.w = coin_place.h;
    
    int i=0;
    int x = 0;
    int nBcoins = 0;
    
    //SDL_RenderCopy(renderer,s_text[0].text_texture,NULL,&scoreText);
    int score_help = 0; 
    while(fgets(buffer,sizeof(buffer),f)){
        for(int z=0;buffer[z] != '\0'; z++){

            if(buffer[z] == '#'){
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_RenderFillRect(renderer,&map);

                                if(SDL_HasIntersection(&map,&r_ghost) == SDL_TRUE){
                                        movementFlagR = 1;
                                }
                                if(SDL_HasIntersection(&map,&y_ghost) == SDL_TRUE){
                                        movementFlagY = 1;
                                }

                                if(SDL_HasIntersection(&map,&p_ghost) == SDL_TRUE){
                                        movementFlagP = 1;
                                }

                                if(SDL_HasIntersection(&map,&br_ghost) == SDL_TRUE){
                                        movementFlagBr = 1;
                                }
                        
                        if(SDL_HasIntersection(&map,&texture) == SDL_TRUE){
                            switch(flag_position){
                                case 'r':
                                    flag_border_r = 1;
                                        
                                            texture.x -= 1;
                                        
                                break;

                                case 'l':
                                    flag_border_l = 1;
                                        //while(SDL_HasIntersection(&map,&texture) == SDL_TRUE){
                                            texture.x += 1;
                                        //}
                                break;

                                case 'd':
                                    flag_border_d = 1;
                                        //while(SDL_HasIntersection(&map,&texture) == SDL_TRUE){
                                            texture.y -= 1;
                                        //}
                                break;

                                case 'u':
                                    flag_border_u = 1;
                                        //while(SDL_HasIntersection(&map,&texture) == SDL_TRUE){
                                            texture.y += 1;
                                        //}
                                break;
                            }
                        }
                        
                       map.x+=PANMAN_H;
            }
            if(buffer[z] == ' '){
                
                map.x+=PANMAN_H_H;
                
            }

            if(buffer[z] == 'p'){
                if(p_starting_pos == 0){
                    p_ghost.x = map.x;
                    p_ghost.y = map.y;
                    p_starting_pos = 1;
                    


                    starting_pos_p_ghost.x = p_ghost.x;
                    starting_pos_p_ghost.y = p_ghost.y;
                }    

                map.x += PANMAN_H_H;   
            }

            if(buffer[z] == 'w'){
                if(br_starting_pos == 0){
                    br_ghost.x = map.x;
                    br_ghost.y = map.y;
                    br_starting_pos = 1;
                    


                    starting_pos_br_ghost.x = br_ghost.x;
                    starting_pos_br_ghost.y = br_ghost.y;
                }    

                map.x += PANMAN_H_H;   
            }

            if(buffer[z] == 'h'){ 
                if(r_starting_pos == 0){
                    r_ghost.x = map.x;
                    r_ghost.y = map.y;
                    r_starting_pos = 1;
                    


                    starting_pos_r_ghost.x = r_ghost.x;
                    starting_pos_r_ghost.y = r_ghost.y;
                }    

                map.x += PANMAN_H_H;
            }
            if(buffer[z] == 'y'){
                if(y_starting_pos == 0){
                y_ghost.x = map.x;
                y_ghost.y = map.y;
                y_starting_pos = 1;

                starting_pos_y_ghost.x = y_ghost.x;
                starting_pos_y_ghost.y = y_ghost.y;
                }

                map.x += PANMAN_H_H;
            }

            if(buffer[z] == 's'){ 
                if(panman_starting_pos == 0){
                    texture.x = map.x;
                    texture.y = map.y;

                    starting_pos_panman.x = texture.x;
                    starting_pos_panman.y = texture.y;

                    panman_starting_pos = 1;
                }    

                map.x += PANMAN_H_H;
            }

            if(buffer[z] == 'b'){
                b_coin_place.x = map.x;
                b_coin_place.y = map.y;
                SDL_RenderCopy(renderer,b_coin[nBcoins].coin_texture,NULL,&b_coin_place);
                
                if(SDL_HasIntersection(&b_coin_place,&texture) == SDL_TRUE){
                    SDL_DestroyTexture(b_coin[nBcoins].coin_texture);
                    if(token2[nBcoins] == ERROR_INDEX){
                        token2[nBcoins] = nBcoins;
                        hunter = 1;
                    }
                }

                nBcoins++;
                map.x+=PANMAN_H_H;
            }

            if(buffer[z] == 'c'){
            
            coin_place.x = map.x;
            coin_place.y = map.y; 
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
            SDL_RenderCopy(renderer,s_coin[x].coin_texture,NULL,&coin_place);
            

            
            if(SDL_HasIntersection(&coin_place,&texture) == SDL_TRUE){
                
                if(token[x] == ERROR_INDEX){
                    token[x] = x;
                    score++;
                }
                
                SDL_DestroyTexture(s_coin[x].coin_texture);
            }
            
            x++;
            map.x+=PANMAN_H_H;
            }
               
            if(score_help == 0){
                SDL_RenderCopy(renderer,s_text[score].text_texture,NULL,&scoreText);
                score_help =1;
            }
            


                   
        }

        i++;
        map.y+=PANMAN_H_H;
        map.x = 0;

    }
    score_help = 0;

    if(hunter == 0){

    

    switch(flag_ghost_y){
            case 'r':
                 SDL_RenderCopy(renderer,yGhostR,NULL,&y_ghost);
            break;

            case 'l':
                SDL_RenderCopy(renderer,yGhostL,NULL,&y_ghost);
            break;

            case 'u':
                SDL_RenderCopy(renderer,yGhostU,NULL,&y_ghost);
            break;

            case 'd':
                SDL_RenderCopy(renderer,yGhostD,NULL,&y_ghost);
            break;
        }


    switch(flag_ghost_p){
            case 'r':
                 SDL_RenderCopy(renderer,pGhostR,NULL,&p_ghost);
            break;

            case 'l':
                SDL_RenderCopy(renderer,pGhostL,NULL,&p_ghost);
            break;
        } 


    switch(flag_ghost_br){
            case 'r':
                 SDL_RenderCopy(renderer,brGhostR,NULL,&br_ghost);
            break;

            case 'l':
                SDL_RenderCopy(renderer,brGhostL,NULL,&br_ghost);
            break;
        } 
        
    switch(flag_ghost_red){
            case 'r':
                 SDL_RenderCopy(renderer,rGhostR,NULL,&r_ghost);
            break;

            case 'l':
                SDL_RenderCopy(renderer,rGhostL,NULL,&r_ghost);
            break;

            case 'u':
                SDL_RenderCopy(renderer,rGhostU,NULL,&r_ghost);
            break;

            case 'd':
                SDL_RenderCopy(renderer,rGhostD,NULL,&r_ghost);
            break;
        } 
    }
    if(hunter == 1){
        SDL_RenderCopy(renderer,ghostHunted,NULL,&r_ghost);
        SDL_RenderCopy(renderer,ghostHunted,NULL,&y_ghost);
        SDL_RenderCopy(renderer,ghostHunted,NULL,&p_ghost);
        SDL_RenderCopy(renderer,ghostHunted,NULL,&br_ghost);
    }


    switch(n_lives){
        case 3:
            SDL_RenderCopy(renderer,s_lives[n_lives].lives_texture,NULL,&lives_text);
        break;

        case 2:
            SDL_RenderCopy(renderer,s_lives[n_lives].lives_texture,NULL,&lives_text);
        break;

        case 1:
            SDL_RenderCopy(renderer,s_lives[n_lives].lives_texture,NULL,&lives_text);
        break;
    }
        


    fclose(f);
    

        
        
            }
        }
    }

    if(n_lives == 0){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,endScreen,NULL,&menu_place);
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);

        SDL_RenderCopy(renderer,s_lives[0].lives_texture,NULL,&lives_text);
        SDL_RenderCopy(renderer,s_text[score].text_texture,NULL,&scoreText);

    }


    if(numCoins == score){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,winScreen,NULL,&menu_place);

        SDL_RenderCopy(renderer,s_lives[n_lives].lives_texture,NULL,&lives_text);
        SDL_RenderCopy(renderer,s_text[score].text_texture,NULL,&scoreText);
    }

    SDL_RenderPresent(renderer);

    }    
    
    

    SDL_DestroyTexture(rGhostR);
    SDL_DestroyTexture(rGhostL);
    SDL_DestroyTexture(rGhostD);
    SDL_DestroyTexture(rGhostU);

    SDL_DestroyTexture(yGhostR); 
    SDL_DestroyTexture(yGhostU); 
    SDL_DestroyTexture(yGhostD); 
    SDL_DestroyTexture(yGhostL);

    SDL_DestroyTexture(brGhostR); 
    SDL_DestroyTexture(brGhostL);

    SDL_DestroyTexture(pGhostR); 
    SDL_DestroyTexture(pGhostL); 

    SDL_DestroyTexture(panmanR);
    SDL_DestroyTexture(panmanL);
    SDL_DestroyTexture(panmanU);
    SDL_DestroyTexture(panmanD);

    

    SDL_DestroyTexture(ghostHunted);

    SDL_DestroyTexture(back);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(mapEasy);
    SDL_DestroyTexture(mapHard);
    SDL_DestroyTexture(mapEasyS);
    SDL_DestroyTexture(mapHardS);
    SDL_DestroyTexture(titleMenu);
    SDL_DestroyTexture(settings);
    SDL_DestroyTexture(mapMedium);
    SDL_DestroyTexture(mapMediumS);
    SDL_DestroyTexture(endScreen);
    SDL_DestroyTexture(winScreen);
    SDL_DestroyTexture(ghosts);
    SDL_DestroyTexture(mapType);

    free(s_text);
    free(token);
    free(s_lives);
    free(b_coin);
    free(s_coin);
    free(token2);

    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    
    
}