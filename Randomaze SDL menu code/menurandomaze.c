    #include <SDL.h>
    #include <stdio.h>

    int main(int argcs, char *args[])
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Surface *pantalla;
        SDL_Window *principal;
        principal = SDL_CreateWindow( "Randomaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );
        pantalla = SDL_GetWindowSurface(principal);
        pantalla = SDL_LoadBMP( "randomaze_bueno.bmp" );

        if(pantalla == NULL){
            printf("error");
        }
        SDL_UpdateWindowSurface(principal);
        SDL_Delay(2000);

        return 0;

    }





