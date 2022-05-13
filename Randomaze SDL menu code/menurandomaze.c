    #include <SDL.h>
    #include <stdio.h>

    int main(int argcs, char *args[])
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Rect posicion;
        posicion.x= 0;
        posicion.y= 0;
        posicion.w= 1280;
        posicion.h=720;
        SDL_Surface *pantalla, *aux;
        SDL_Window *principal;
        principal = SDL_CreateWindow( "Randomaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );
        pantalla = SDL_GetWindowSurface(principal);
        aux = SDL_LoadBMP( "randomaze_bueno.bmp" );

        if(aux == NULL){
            printf("error");
        }
        SDL_BlitSurface(aux, NULL, pantalla, &posicion);
        SDL_UpdateWindowSurface(principal);
        SDL_Delay(2000);

        return 0;

    }




