#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Dimensions fenÃªtre = dims "renderer" = dims du "playground":
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

// ExtrÃ©mitÃ©s du playground:
#define PLAYGROUND_LIM_XMIN 0
#define PLAYGROUND_LIM_XMAX WINDOW_WIDTH - BALL_WIDTH - 1
#define PLAYGROUND_LIM_BOTTOM 0
#define PLAYGROUND_LIM_TOP WINDOW_HEIGHT - BALL_HEIGHT - 1

#define NET_DASH_X WINDOW_WIDTH/2 // pos x
#define NET_DASH_Y_FIRST 80 // premier rectangle
#define NET_DASH_Y_LAST 560 // dernier rectangle
#define NET_DASH_WIDTH    4 // largeur rectangle
#define NET_DASH_HEIGTH   8 // hauteur rectangle
#define NET_DASH_PERIOD  16 // pÃ©riodicitÃ© des rectangles

// ParamÃ¨tres des raquettes:
#define RACKET_WIDTH    8  // largeur raquette
#define RACKET_HEIGHT  60  // hauteur raquette (le jeu originel utilise 30!)
#define RACKET_INIT_X_P1   120 // position initiale en x raquette joueur 1
#define RACKET_INIT_X_P2   WINDOW_WIDTH - RACKET_INIT_X_P1 - RACKET_WIDTH - 1 // pour la raquette du joueur 2
#define RACKET_INIT_Y      WINDOW_HEIGHT/2 - RACKET_HEIGHT/2 - 1 // position initiale en y des deux raquettes
#define RACKET_DY      24  // vitesse de dÃ©placement (en y) des raquettes (en pixel/frame ou pixel/touche)

// ParamÃ¨tres de la balle:
#define BALL_WIDTH      8 // largeur balle
#define BALL_HEIGHT     8 // hauteur balle
#define BALL_INIT_X WINDOW_WIDTH/2 - BALL_WIDTH/2 - 1   // position initiale en x balle
#define BALL_INIT_Y WINDOW_HEIGHT/2 - BALL_HEIGHT/2 - 1 // position initiale en y balle
#define BALL_INIT_VX   10 // Vitesse initiale en x (en pixel/frame)
#define BALL_INIT_VY    5 // Vitesse initiale en y (en pixel/frame)

// ParamÃ¨tres d'affichage du score:
#define SCORE_WINNER  11 // Score qui fait qu'un joueur a gagnÃ©
#define SCORE_X_P1    180 // x0 pour l'affichage du premier digit du joueur 1
#define SCORE_X_P2    550 // x0 pour l'affichage du premier digit du joueur 2
#define SCORE_Y       112 // y0 pour l'affichage des digits des deux joueurs
#define SCORE_LENGTH 40 // Longueur des rectangles utilisÃ©s pour former les nombres
#define SCORE_WIDTH 10 // largueur des rectangles utilisÃ©s pour former les nombres

// Couleurs:
#define NET_COLOR {255, 255, 255, 255}   // Couleur du filet
#define SCORE_COLOR {255, 255, 255, 255} // Couleur des scores
#define BALL_COLOR {255, 255, 0, 255}    // Couleur de la balle
#define P1_COLOR {127, 127, 255, 255}    // Couleur de la raquette du joueur 1
#define P2_COLOR {127, 127, 255, 255}    // Couleur de la raquette du joueur 2


bool segment_state[10][7] = {{true, true, true, false, true, true, true},     //0
                             {false, false, true, false, false, true, false}, //1
                             {true, false, true, true, true, false, true},    //2
                             {true, false, true, true, false, true, true},    //3
                             {false, true, true, true, false, true , false},  //4
                             {true, true, false, true, false, true, true},    //5
                             {true, true, false, true, true, true, true},     //6
                             {true, false, true, false, false, true, false},  //7
                             {true, true, true, true, true, true, true},      //8
                             {true, true, true, true, false, true, true}      //9

};

void draw_ball(SDL_Renderer* renderer, int x_coord, int y_coord){
    static const SDL_Color ball_color = BALL_COLOR;

    SDL_SetRenderDrawColor(renderer, ball_color.r, ball_color.g, ball_color.b, ball_color.a);
    SDL_Rect ball = {x_coord, y_coord, BALL_WIDTH, BALL_HEIGHT};
    SDL_RenderFillRect(renderer, &ball);
}

void draw_segment(SDL_Renderer* renderer, int coord_x, int coord_y, int length, int width){
    int i;
    SDL_Rect rectangle = {coord_x, coord_y, length, width};
    SDL_Rect* rect = &rectangle;
    SDL_RenderFillRect(renderer,  rect);


    // dessiner le segment des coord de dÃ©part aux coords de fin
}

void draw_digit(int number, int coord_x, int coord_y, SDL_Renderer* renderer){
    static const SDL_Rect digit_segments[7] = {
        {0, 0, SCORE_LENGTH, SCORE_WIDTH},   //honrizontale en haut
        {0, 0, SCORE_WIDTH, SCORE_LENGTH},   // verticale haut gauche
        {SCORE_LENGTH - SCORE_WIDTH, 0, SCORE_WIDTH, SCORE_LENGTH}, // verticale haut droite
        {0, SCORE_LENGTH - SCORE_WIDTH, SCORE_LENGTH, SCORE_WIDTH}, // horizontale milieu
        {0, SCORE_LENGTH - SCORE_WIDTH, SCORE_WIDTH, SCORE_LENGTH}, //verticale bas gauche
        {SCORE_LENGTH - SCORE_WIDTH, SCORE_LENGTH - SCORE_WIDTH, SCORE_WIDTH, SCORE_LENGTH}, //verticale bas droite
        {0, 2 * (SCORE_LENGTH - SCORE_WIDTH), SCORE_LENGTH, SCORE_WIDTH} // honrizontale en bas
    };

    int i;
    
    for(i=0; i<8; i++){
        if (segment_state[number][i] == true){
            draw_segment(renderer, coord_x + digit_segments[i].x, coord_y + digit_segments[i].y, digit_segments[i].w, digit_segments[i].h);
        }
    }
}

void draw_number(int number, int coord_x, int coord_y, SDL_Renderer* renderer){
    if (number == 0){
        draw_digit(0, coord_x, coord_y, renderer);
        return;
    }
    
    int nbDigits=log10(number) + 1;
    //int posDigit=1; // position du chiffre (1=unites, 2=dizaines, 3=centaines, ...)
    for (int posDigit=1; posDigit<=nbDigits; posDigit++)
    {
        int n = (int)pow(10, posDigit - 1);
        int digit = (number % (10 * n)) / n;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_digit(digit, coord_x, coord_y, renderer);
        coord_x -= SCORE_LENGTH + 20;
    }
}

void draw_net(SDL_Renderer* renderer){
    static const SDL_Color net_color = NET_COLOR;

    SDL_SetRenderDrawColor(renderer, net_color.r, net_color.g, net_color.b, net_color.a);
    int actual_y_pos = NET_DASH_Y_FIRST;

    while (actual_y_pos <= NET_DASH_Y_LAST){
        SDL_Rect rectangle = {NET_DASH_X, actual_y_pos, NET_DASH_WIDTH, NET_DASH_HEIGTH};
        SDL_RenderFillRect(renderer, &rectangle);
        actual_y_pos += NET_DASH_PERIOD;
    }
}

void draw_rackets(SDL_Renderer* renderer, int j1_x_coord, int j1_y_coord, int j2_x_coord, int j2_y_coord){
    static const SDL_Color Couleur_J1 = P1_COLOR;
    static const SDL_Color Couleur_J2 = P2_COLOR;

    //Raquette J1
    SDL_SetRenderDrawColor(renderer, Couleur_J1.r, Couleur_J1.g, Couleur_J1.b, Couleur_J1.a);
    SDL_Rect Player1_racket = {j1_x_coord, j1_y_coord, RACKET_WIDTH, RACKET_HEIGHT};
    SDL_RenderFillRect(renderer, &Player1_racket);

    //Raquette J2
    SDL_SetRenderDrawColor(renderer, Couleur_J2.r, Couleur_J2.g, Couleur_J2.b, Couleur_J2.a);
    SDL_Rect Player2_racket = {j2_x_coord, j2_y_coord, RACKET_WIDTH, RACKET_HEIGHT};
    SDL_RenderFillRect(renderer, &Player2_racket);
}

/* moves a racket down or up */
void move_rackets(int direction, int* y_coord){
    if (direction == -1){
        *y_coord += RACKET_DY;
    }
    else{
        *y_coord -= RACKET_DY;
    } 
}

void move_ball(int x_speed, int y_speed, int* ball_coord_x, int* ball_coord_y){
    *ball_coord_x += x_speed;
    *ball_coord_y += y_speed;
}

int main(int argc, char *argv[])
{
    SDL_Window* fenetre;  // DÃ©claration de la fenÃªtre
    SDL_Renderer* renderer; // DÃ©claration du renderer
    int i;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)  // initialisation de la SDL
    {
       printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
       return EXIT_FAILURE;
    }

    fenetre = SDL_CreateWindow("Compteur",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);  // CrÃ©ation de la fenÃªtre

    if (fenetre == NULL)  //gestion des erreurs
    {
        printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // CrÃ©ation du renderer

    if(renderer == NULL)//gestion des erreurs
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Delay(1000);
    int ball_actual_x_coord = BALL_INIT_X;
    int ball_actual_y_coord = BALL_INIT_Y;
    int ball_actual_x_speed = BALL_INIT_VX;
    int ball_actual_y_speed = BALL_INIT_VY;

    int racketJ1_actual_x_coord = RACKET_INIT_X_P1;
    int racketJ1_actual_y_coord = RACKET_INIT_Y;
    
    int racketJ2_actual_x_coord = RACKET_INIT_X_P2;
    int racketJ2_actual_y_coord = RACKET_INIT_Y;

    int J1_actual_score = 0;
    int J2_actual_score = 0;

    SDL_Event event;


        
        while (J1_actual_score < 11 && J2_actual_score < 11){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            draw_net(renderer);
            draw_rackets(renderer, racketJ1_actual_x_coord, racketJ1_actual_y_coord, racketJ2_actual_x_coord, racketJ2_actual_y_coord);
            draw_ball(renderer, ball_actual_x_coord, ball_actual_y_coord);

            while (SDL_PollEvent(&event) == 1){
                if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
                        move_rackets(-1, &racketJ1_actual_y_coord);
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                        move_rackets(1, &racketJ1_actual_y_coord);
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        move_rackets(-1, &racketJ2_actual_y_coord);
                    }
                    if (event.key.keysym.sym == SDLK_z){
                        move_rackets(1, &racketJ2_actual_y_coord);
                    }
                }
            }
            move_ball(ball_actual_x_speed, ball_actual_y_speed, &ball_actual_x_coord, &ball_actual_y_coord);
            draw_number(J1_actual_score, SCORE_X_P1, SCORE_Y, renderer);
            draw_number(J2_actual_score, SCORE_X_P2, SCORE_Y, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
        }

    // Destruction du renderer et de la fenÃªtre :
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(fenetre);
    SDL_Quit();  //on quitte la SDL
    return 0;
}
