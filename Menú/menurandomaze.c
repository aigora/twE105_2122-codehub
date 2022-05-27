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

        int x, y;
        int accion;
        int momento=0;

        SDL_Surface *pantalla, *aux;
        SDL_Surface *imagen1;
        SDL_Surface *imagen2;
        SDL_Surface *imagen3;
        SDL_Surface *imagen4;
        SDL_Surface *fondo;
        SDL_Window *principal;
        SDL_Event event;

        imagen1= SDL_LoadBMP("randomaze_bueno.bmp");
        imagen2= SDL_LoadBMP("opcionesradomaze.bmp");
        imagen3= SDL_LoadBMP("dificultadrandomaze.bmp");
        imagen4= SDL_LoadBMP("personajes.bmp");

//        SDL_SetColorKey( imagen1, SDL_TRUE, SDL_MapRGB(imagen1->format, 0,255,0));
//        SDL_SetColorKey( imagen2, SDL_TRUE, SDL_MapRGB(imagen2->format, 0,255,0));
//        SDL_SetColorKey( imagen3, SDL_TRUE, SDL_MapRGB(imagen3->format, 0,255,0));
//        SDL_SetColorKey( imagen4, SDL_TRUE, SDL_MapRGB(imagen4->format, 0,255,0));


        principal = SDL_CreateWindow( "Randomaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );
        pantalla = SDL_GetWindowSurface(principal);
        aux = SDL_LoadBMP( "randomaze_bueno.bmp" );
        bool isRunning = true;

        if (SDL_PollEvent(&event)!=0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning= false;
                break;

            default:
                break;
            }

        }
        do
        {
            switch (momento)
            {
            case 0: //Pantalla principal, quit y jugar.
                {
                    while (momento == 0)
                    {
                        aux = imagen1;
                        accion = SDL_GetMouseState(&x, &y);
                        while (SDL_PollEvent(&event)!=0)
                        {
                            if(event.type == SDL_Quit)
                            {
                                return 0;
                            }
                            else if( event.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if(x<573 && y> 491 && x>298 && y<588)
                                    momento=1; //Jugar
                                else if (x< 957 && y>490 && x>688 && y<589)
                                    momento=2; //Entramos en opciones
                            }

                        }
                        SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                        SDL_UpdateWindowSurface(principal);
                    }
                }
                break;

            case 1: //Jugar
                {
                    while (momento == 1)
                    {
                        accion = SDL_GetMouseState(&x, &y);
                        while (SDL_PollEvent(&event)!=0)
                        {
                            if(event.type == SDL_Quit)
                            {
                                return 0;
                            }

                            // Se inicia la función de jugar; Si es que no se a pulsado quit.
                        }
                    }
                }
                break;

            case 2: //Opciones
                {
                    while (momento == 2)
                    {
                        aux=imagen2;
                        accion = SDL_GetMouseState(&x, &y);
                        while (SDL_PollEvent(&event)!=0)
                        {
                            if(event.type == SDL_Quit)
                            {
                                return 0;
                            }
                            else if(event.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if ( x< 1144 && y> 444 && x> 771 && y<566)
                                {
                                    momento=3; //Dificultad;
                                }
                                else if (x<489 && y>442 && x>128 && y<567)
                                {
                                    momento=4;
                                }
                                else if (x<1277 && x>1088 && y<73 && y>3) //Retroceder al menu
                                {
                                    aux=imagen1;
                                    momento=0;
                                }
                            }
                        }
                        SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                        SDL_UpdateWindowSurface(principal);
                    }

                }
                break;

            case 3: //Dificultad
                {
                    while ( momento == 3)
                    {
                        aux = imagen3;
                        accion = SDL_GetMouseState(&x, &y);
                        while (SDL_PollEvent(&event)!=0)
                        {
                            if(event.type == SDL_Quit)
                            {
                                return 0;
                            }
                            else if(event.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if (x<828 && y>177 && x>437 &&y<269)
                                {
                                    //Facil
                                }
                                else if( x<818 && y>311 && x<437 && y<403)
                                {
                                    //Normal
                                }
                                else if( x<820 && y>456 && x>434 && y<540)
                                {
                                    //Difícil
                                }
                                else if(x<1277 && x>1088 && y<73 && y>3)
                                {
                                    aux= imagen2; //Volver a la pantalla de opciones.
                                    momento=2;
                                }
                            }
                            SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                            SDL_UpdateWindowSurface(principal);
                        }

                    }
                }
                break;

            case 4: //Personajes
                {
                    while (momento == 4)
                    {
                        aux = imagen4;
                        accion = SDL_GetMouseState(&x, &y);
                        while (SDL_PollEvent(&event)!=0)
                        {
                            if(event.type == SDL_Quit)
                            {
                                return 0;
                            }
                            else if(event.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if(x>251 && x<525 && y>434 && y<531)
                                {
                                    //personaje 1;
                                }
                                else if(x>740 && x<1015 && y<529 && y>433)
                                {
                                    //personaje 2
                                }
                                else if(x<1277 && x>1088 && y<73 && y>3) //vuelve a las opciones.
                                {
                                    aux= imagen2;
                                    momento=2;
                                }
                                SDL_BlitSurface(aux, NULL, pantalla, &posicion);
                                SDL_UpdateWindowSurface(principal);
                            }

                        }


                    }
                }
                break;

            }

        }while(isRunning);

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
