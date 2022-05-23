#include <SDL.h>
#include <stdio.h>
#include "glaberinto.c"
#include <stdlib.h>
#include <math.h>


#define wpantalla 1280
#define hpantalla 720
#define N 100



int main(int argc, char* args[] ){

int n = 100;

if (SDL_Init(SDL_INIT_VIDEO) < 0)
{
 printf("No se pudo inicializar SDL: %s\n",
 SDL_GetError());
 exit(1);
}



SDL_Window  *ventana;
SDL_Surface *principal;


SDL_Surface *personaje;
SDL_Surface *fondo;
SDL_Surface *smapa;

smapa = SDL_CreateRGBSurface(32, 16*n,16*n,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);

ventana = SDL_CreateWindow( "laberinto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wpantalla, hpantalla, SDL_WINDOW_SHOWN );
principal = SDL_GetWindowSurface( ventana );

 cargarimagenes(principal, &fondo, &personaje);


semilla();

  int mapa[100][100];



  crear( mapa ,n,n);



cargarmapa(smapa, n, mapa);



casilla posicion=casinicial(mapa, n);

int h=11, w= 17; //h= 44  w= 53



_Bool cerrar = 0;

SDL_Event e;
int dire;

while (!cerrar){
    while( SDL_PollEvent( &e ) != 0 ){
                    //User requests quit
                if( e.type == SDL_QUIT )
                {
                        cerrar = 1;
                }else if(( e.type == SDL_KEYDOWN )){
                    switch( e.key.keysym.sym ){
                    case SDLK_UP:
                        if(mapa[posicion.y-1][posicion.x]!= 0 & mapa[posicion.y-1][posicion.x]!= 2  || 0){
                        posicion.y = posicion.y -1;
                        dire = 0;
                        represent(smapa,fondo,personaje, principal, posicion, ventana,w,h,n, dire);}
                        break;
                    case SDLK_DOWN:
                         if(mapa[posicion.y+1][posicion.x] != 0 & mapa[posicion.y+1][posicion.x] != 2 || 0 ){
                        posicion.y = posicion.y +1;
                        dire = 2;
                        represent(smapa,fondo,personaje, principal, posicion, ventana,w,h,n, dire);}

                        break;
                    case SDLK_LEFT:
                        if(mapa[posicion.y][posicion.x-1] !=0 & mapa[posicion.y][posicion.x-1] !=2 || 0 ){
                        posicion.x = posicion.x -1;
                        dire = 3;
                        represent(smapa,fondo,personaje, principal, posicion, ventana,w,h,n, dire);}
                        break;
                    case SDLK_RIGHT:
                        if(mapa[posicion.y][posicion.x+1] !=0  & mapa[posicion.y][posicion.x+1] !=2 || 0 ){
                           posicion.x = posicion.x +1;
                        dire= 1;
                        represent(smapa,fondo,personaje, principal, posicion, ventana,w,h,n, dire);
                        }

                        break;
                    case SDLK_m:
                        minimapa(smapa, fondo, principal,ventana);
                        break;
                    }



                    if(mapa[posicion.y][posicion.x]>3){
                        posicion = teletransporte(mapa, posicion, n);
                        represent(smapa, fondo, personaje, principal, posicion, ventana ,w,h,n, dire);
                    }




    }
}




}}


