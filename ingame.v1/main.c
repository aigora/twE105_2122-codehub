#include <SDL.h>
#include <stdio.h>
#include<stdbool.h>
#include "glaberinto.c"
#include <stdlib.h>
#include <math.h>


#define wpantalla 1280
#define hpantalla 720
#define N 100



    int main(int argcs, char *args[])
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Rect posicion;
        posicion.x= 0;
        posicion.y= 0;
        posicion.w= 1280;
        posicion.h=720;
        SDL_Surface *pantalla, *aux;
        SDL_Surface *imagen1;
        SDL_Surface *imagen2;
        SDL_Surface *imagen3;
        SDL_Surface *imagen4;
        SDL_Surface *fondo;
        SDL_Window *principal;
        bool isRunning = true;
        SDL_Event event;
        imagen1= SDL_LoadBMP("randomaze_bueno.bmp");
        imagen2= SDL_LoadBMP("opcionesradomaze.bmp");
        imagen3= SDL_LoadBMP("dificultadrandomaze.bmp");
        imagen4= SDL_LoadBMP("");

        SDL_SetColorKey( imagen1, SDL_TRUE, SDL_MapRGB(imagen1->format, 0,255,0));
        SDL_SetColorKey( imagen2, SDL_TRUE, SDL_MapRGB(imagen2->format, 0,255,0));
        SDL_SetColorKey( imagen3, SDL_TRUE, SDL_MapRGB(imagen3->format, 0,255,0));
        //SDL_SetColorKey( imagen4, SDL_TRUE, SDL_MapRGB(imagen4->format, 0,255,0));


        principal = SDL_CreateWindow( "Randomaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );
        pantalla = SDL_GetWindowSurface(principal);
        aux = SDL_LoadBMP( "randomaze_bueno.bmp" );


        if(aux == NULL)
        printf("error al cargar SDL");

        while(isRunning)
        {
            while(SDL_PollEvent(&event)!=0)
            {
                if (event.type==SDL_QUIT)
                isRunning= false;
                else if(event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_1:
                            jugar(50);
                        break;
                    case SDLK_2:
                        aux = imagen2;
                        break;
                    case SDLK_3:
                        {
                        aux= imagen3;//Opciones
                        if (SDLK_3)
                            aux = imagen3; //dificultad;
                        else if(SDLK_4)
                            aux = imagen4; //personajes;
                        break;
                        }
                    case SDLK_SPACE:
                        aux = imagen1;
                        break;
                    }
                }
                if (SDL_MOUSEMOTION == event.type)
                {
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    printf(" %d %d", x,y);

                }
            }
                SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                SDL_UpdateWindowSurface(principal);

        }


        SDL_FreeSurface(imagen1);
        SDL_FreeSurface(imagen2);
        SDL_FreeSurface(imagen3);
        SDL_FreeSurface(imagen4);
        SDL_FreeSurface(aux);
        SDL_FreeSurface(pantalla);
        SDL_DestroyWindow(principal);
        SDL_Quit();
        return 0;

    }






//int main(int argc, char* args[] ){
//    jugar(50);
//}
