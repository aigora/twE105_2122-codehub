    #include <SDL.h>
    #include <stdbool.h>
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
        SDL_Surface *imagen1;
        SDL_Surface *imagen2;
        SDL_Surface *imagen3;
        SDL_Surface *imagen4;
        SDL_Window *principal;
        bool isRunning = true;
        SDL_Event event;
        imagen1= SDL_LoadBMP("randomaze_bueno.bmp");
        imagen2= SDL_LoadBMP("opcionesradomaze.bmp");
        imagen3= SDL_LoadBMP("dificultadrandomaze.bmp");
        imagen4= SDL_LoadBMP("");


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
                        //principal= Jugar; Aún por implementar.
                        break;
                    case SDLK_2:
                        aux = imagen2; //Opciones
                        if(SDLK_3)
                            aux = imagen3; //dificultad;
                        else if(SDLK_4)
                            aux = imagen4; //personajes;
                        else if(SDLK_SPACE)
                            aux = imagen1; //Pulsando espacio te redirige a la pantalla principal;
                        break;
                    }
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




