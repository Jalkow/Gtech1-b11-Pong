#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h> 

// Dimensions fenêtre = dims "renderer" = dims du "playground":
  #define WINDOW_WIDTH  800
  #define WINDOW_HEIGHT 600

// Extrémités du playground:
  #define PLAYGROUND_LIM_XMIN 0
  #define PLAYGROUND_LIM_XMAX WINDOW_WIDTH - BALL_WIDTH - 1
  #define PLAYGROUND_LIM_BOTTOM 0
  #define PLAYGROUND_LIM_TOP WINDOW_HEIGHT - BALL_HEIGHT - 1

// Paramètres du filet:
#define NET_DASH_Y_FIRST 80 // premier rectangle
#define NET_DASH_Y_LAST 560 // dernier rectangle
#define NET_DASH_X WINDOW_WIDTH/2
#define NET_DASH_WIDTH    4 // largeur rectangle
#define NET_DASH_HEIGTH   8 // hauteur rectangle
#define NET_DASH_PERIOD  16 // périodicité des rectangles

// Paramètres des raquettes:
#define RACKET_WIDTH    8  // largeur raquette
#define RACKET_HEIGHT  60  // hauteur raquette (le jeu originel utilise 30!)
#define RACKET_INIT_X_P1   120 // position initiale en x raquette joueur 1
#define RACKET_INIT_X_P2   WINDOW_WIDTH - RACKET_INIT_X_P1 - RACKET_WIDTH - 1 // pour la raquette du joueur 2
#define RACKET_INIT_Y      WINDOW_HEIGHT/2 - RACKET_HEIGHT/2 - 1 // position initiale en y des deux raquettes
#define RACKET_DY      12  // vitesse de déplacement (en y) des raquettes (en pixel/frame ou pixel/touche)

// Paramètres de la balle:
#define BALL_WIDTH      8 // largeur balle
#define BALL_HEIGHT     8 // hauteur balle
#define BALL_INIT_X WINDOW_WIDTH/2 - BALL_WIDTH/2 - 1   // position initiale en x balle
#define BALL_INIT_Y WINDOW_HEIGHT/2 - BALL_HEIGHT/2 - 1 // position initiale en y balle
#define BALL_INIT_VX   10 // Vitesse initiale en x (en pixel/frame)
#define BALL_INIT_VY    5 // Vitesse initiale en y (en pixel/frame)

// Paramètres d'affichage du score:
#define SCORE_WINNER   11 // Score qui fait qu'un joueur a gagné
#define SCORE_X_P1    217 // x0 pour l'affichage du premier digit du joueur 1
#define SCORE_X_P2    621 // x0 pour l'affichage du premier digit du joueur 2
#define SCORE_Y       112 // y0 pour l'affichage des digits des deux joueurs

// Couleurs:
#define SCORE_COLOR {255, 255, 255, 255} // Couleur des scores
#define BALL_COLOR {255, 255, 0, 255}    // Couleur de la balle
#define P1_COLOR {127, 127, 255, 255}    // Couleur de la raquette du joueur 1
#define P2_COLOR {127, 127, 255, 255}    // Couleur de la raquette du joueur 2


void draw_net(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(255, 255, 255, 255);
  SDL_Rect rect = {NET_DASH_Y_FIRST, NET_DASH
}

int main(int argc, char *argv[]){
  SDL_Window* fenetre;
  SDL_Renderer* renderer;
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("Erreur with the initialisation of the SDL : %s",SDL_GetError());
      return EXIT_FAILURE;
    }

  window = SDL_CreateWindow("Pong" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WINDOW_HEIGHT , WINDOW_WIDTH , SDL_WINDOW_RESIZABLE);
  if(window == NULL)
    {
      printf("Error while creating window : %s",SDL_GetError());
      return EXIT_FAILURE;
    }

  renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(renderer == NULL)
    {
      printf("Error while creating renderer : %s",SDL_GetError());
      return EXIT_FAILURE;
    }

  int ball_actual_coord_x = BALL_INIT_X;
  int ball_actual_coord_y = BALL_INIT_Y;
  int ball_actual_speed_x = BALL_INIT_VX;
  int ball_actual_speed_y = BALL_INIT_VY;

  int racketJ1_actual_coord_y = RACKET_INIT_Y;
  int racketJ2_actual_coord_y = RACKET_INIT_Y;

  int J1_actual_score = 0;
  int J2_actual_score = 0;

  SDL_Delay(1000)
  
  while (J1_actual_score < 11 && J2_actual_score < 11){
    SDL_RenderClear(renderer);
    draw_net(renderer);

    SDL_RenderPresent(renderer;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
