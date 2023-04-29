#include <stdio.h>
#include <unistd.h>

int canvas_height = 40;

void hide_cursor();
void show_cursor();
void reset_color();
void set_red_color();
void set_green_color();
void set_blue_color();
void clear_screen();
void move_right();
void move_left();
void move_up();
void move_down();
void move_to(int line, int column);
void draw_pixel();
void end_drawing();
void animate();

void line(int lenght,char r,char c);
void house();
void menu();
void window();
void i_line(int lenght);
void stairs(int num);
void village(int num);
void animation(int num);
void new_house(int a);

int main() {
    int lenght,volba,n_stairs,sum,anim,a;
  
    clear_screen();
    menu();
    
    scanf("%d",&volba);
    clear_screen();

    switch(volba){
        case 1:
        printf("Zadej delku strany domu.\n");
        scanf("%d",&a);

        new_house(a);
        break;

        case 2:

            printf("Zadejte pocet domku.\n");
            scanf("%d",&sum);

            village(sum);
        break;

        case 3:
        printf("Zadejte delku prerusovane cary.\n");
        scanf("%d",&lenght);
        i_line(lenght);
        break;


        case 4:
        printf("Zadejte pocet schodu.\n");
        scanf("%d",&n_stairs);
        stairs(n_stairs);
        break;

        case 5:
            printf("Zadejte pocet schodu.\n");
            scanf("%d",&anim);
            animation(anim);
        break;

        case 6:
            house();
        break;
    }

    end_drawing();

    return 0;
}

void hide_cursor() {
    printf("\x1b[?25l");
}
void show_cursor() {
    printf("\x1b[?25h");
}

void reset_color() {
    printf("\x1b[0m");
}
void set_red_color() {
    printf("\x1b[41;1m");
}
void set_green_color() {
    printf("\x1b[42;1m");
}
void set_blue_color() {
    printf("\x1b[44;1m");
}

void clear_screen() {
    reset_color();
    hide_cursor();

    printf("\x1b[2J");
    printf("\x1b[0;0F");
    for (int i = 0; i < canvas_height; i++) {
        printf("\n");
    }
    for (int i = 0; i < canvas_height; i++) {
        printf("\x1b[1A");
    }
}

void move_right() {
    printf("\x1b[1C");
}
void move_left() {
    printf("\x1b[1D");
}
void move_up() {
    printf("\x1b[1A");
}
void move_down() {
    printf("\x1b[1B");
}
void move_to(int line, int column) {
    printf("\x1b[%d;%dH", line, column);
}

void draw_pixel() {
    printf(" ");
    move_left();
}
void end_drawing() {
    reset_color();
    printf("\x1b[0;0H");
    for (int i = 0; i < canvas_height; i++) {
        move_down();
    }
    printf("\n");
    show_cursor();
}
void animate() {
    fflush(stdout);
    // Sleep for 500ms
    usleep(1000 * 500);
}

void line(int lenght,char r,char c){
int i, cmp;

for(i=1;i<=lenght;i++){
    switch(c){
        case 'r':
        set_red_color();
        break;

        case 'b':
        set_blue_color();
        break;
    
        case 'g':
        set_green_color();
        break;
    }
        draw_pixel();
        switch(r){
            case 'r':
                move_right();
            break;

            case 'l':
                move_left();
            break;

            case 'u':
                move_up();
            break;

            case 'd':
                move_down();
            break;

            default: printf("Spatna volba.\n");
        }
    }
}

void menu(){
    
    printf("Vyberte ulohu: \n\n");
    printf("1 == dum\n");
    printf("2 == vesnice\n");
    printf("3 == prerusovana cara\n");
    printf("4 == schody\n");
    printf("5 == animace\n");
    printf("6 == bonusovy dum\n\n");

}

void window(){
int i;
    for(i=1;i<=1;i++){
        line(4,'r',' ');
        move_down();
        move_left();
        line(4,'l',' ');
    }
}

void i_line(int lenght){
    int i;

    for(i=1;i<=lenght*2;i++){
        if((i%2) == 0){
            move_right();
            continue;
        }else {
            set_green_color();
            draw_pixel();
        }
        move_right();   
    }
}


void stairs(int num){
    int i,y;

    for(i=1;i<=num;i++){
            if(i<7 || y<5){
            line(3,'r','b');
            line(1,'d','b'); 
            }else{      
            line(1,'u','r');
            line(3,'r','r'); 
            y++;
            }

    }
}



void house(){
    int i,y;

move_to(5,0);

for(i=1;i<=3;i++){
    line(3,'r','g');
    move_up();
}
for(i=0;i<=3;i++){
    line(3,'r','g');
    move_down();
}

    move_to(6,0);
    for(i=1;i<=8;i++){
        for(y=1;y<=5;y++){
            if(i % 2){
                line(5,'r','r');
                move_left();
            }else line(5,'l','r');
        }
        move_down();
    }

    set_blue_color();
    move_to(8,4);
    window();

    move_to(8,15);
    window();

    reset_color();
    set_green_color();
    move_to(11,10);
    window();
    move_to(11,9);
    line(2,'d','g');
    
}

void animation(int num){
int i,y;
     for(i=1;i<=num;i++){
            if(i<7 || y<5){
            animate();
            line(3,'r','b');
            animate();
            line(1,'d','b'); 
            animate();
            }else{      
            line(1,'u','r');
            animate();
            line(3,'r','r'); 
            animate();
            y++;
            }

    }
}

void village(int num){
    int i,y;

    for(i=1;i<=num;i++){
        new_house(5);
    }
}

void new_house(int a){
    int i;
    move_right();

    move_right(2);
    line(a-2,'r','r');
    move_right(2);
    move_down();
    move_left();
    line(a,'l','r');


   move_down();

   for(i=0;i<a;i++){
    if((i%2)==0){
        move_right();
        line(a,'r','b');
        
    }else{
      move_left();
      line(a,'l','b');
       
    }
    move_down();
   }
    
    for(i=0;i<=a+1;i++){
        move_up();
    }

    for(i=0;i<=5;i++){       
        move_right();
    }
}