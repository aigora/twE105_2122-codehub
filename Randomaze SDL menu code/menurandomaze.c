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
        int x,y;
        int accion;
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
<<<<<<< Updated upstream:Randomaze SDL menu code/menurandomaze.c
            }
                SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                SDL_UpdateWindowSurface(principal);

        }
=======

                if (SDL_MOUSEMOTION == event.type)
                {

                    accion=SDL_GetMouseState(&x,&y);
                    printf(" %d %d", x,y);

                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
>>>>>>> Stashed changes:ingame.v1/main.c

                    if ( x<573 && y> 491 && x>298 && y<588) //Jugar
                    {
                         jugar(50);
                    }
                    else if( x< 957 && y>490 && x>688 && y<589) //Opciones
                    {
                        aux = imagen2;
                    }
                    else if ( x< 1144 && y> 444 && x> 771 && y<566) //Dificultad
                    {
                        aux = imagen3;
                        //Facil. coordenadas,x<828,y>177;x>437,y<269
                        //Normal. Coordenadas, x<818, y>311; x<437, y<403
                        //Dificil. coord x<820, y>456; x>434, y<540;
                    }
                    else if (x<489 && y>442 && x>128 && y<567)
                    {

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
<<<<<<< Updated upstream:Randomaze SDL menu code/menurandomaze.c
=======

//int main(int argc, char* args[] ){
//    jugar(50);
//}
>>>>>>> Stashed changes:ingame.v1/main.c
