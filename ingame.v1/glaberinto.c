
#include "glaberinto.h"


#define filas 100
#define columnas 100
#define wpantalla 1280
#define hpantalla 720
#define N 100

void crearfondo(SDL_Surface **entrada){              //funciona

    SDL_Surface *retorno;
    SDL_Surface *fondo;
    SDL_Surface *smapa;
    cargarfondo(&fondo);

    retorno = SDL_CreateRGBSurface(32,1280  ,720  ,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
    smapa   = SDL_CreateRGBSurface(32,16*64 ,16*36,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);

int mapa[100][100];
crear(mapa, 64 ,36);

cargarmapa(smapa,  64,36 , mapa);


SDL_Rect posicion;
posicion.x = 0;
posicion.y = 0;
posicion.w = 1280;
posicion.h = 720;
SDL_BlitScaled(fondo, NULL, retorno, &posicion);

SDL_BlitScaled(smapa, NULL, retorno, &posicion);
*entrada = retorno;
}


void cargarmapa(SDL_Surface *smapa, int col,int fil, int mapa[N][N]){  //esta funcion crea una superficie con el mapa entero y fondo trasparente
int i,j;
SDL_Rect posicion;
int vectprob[5] = {80,8,8,8,8}; //porcentajes de provabilidad de los diferentes bloques

SDL_Surface *bloque = cargarimagen("img/bloque.bmp");          //carga las imagenes
SDL_Surface *bloque1= cargarimagen("img/bloque1.bmp");
SDL_Surface *bloque2= cargarimagen("img/bloque2.bmp");
SDL_Surface *bloque3= cargarimagen("img/bloque3.bmp");
SDL_Surface *bloque4= cargarimagen("img/bloque4.bmp");
SDL_Surface *portal= cargarimagen("img/portal.bmp");
SDL_Surface *lapida= cargarimagen("img/inicio.bmp");
SDL_Surface *fin = cargarimagen("img/fin.bmp");

for( i = 0; i < fil ; i++){                                   //realiza un barrido por todo el mapa
    for(j= 0; j < col ; j++){
        if( mapa[i][j] != 0 & mapa[i][j] != 2  ){
            posicion.x = j*16;
            posicion.y = i*16;
            posicion.w = 16;
            posicion.h = 24;

            switch (probabilidad(5,vectprob)){              //selecciona aleatoriamente que tipo de bloque se implementa
        case 0:
            SDL_BlitSurface(bloque, NULL, smapa, &posicion);
            break;
        case 1:
            SDL_BlitSurface(bloque1, NULL, smapa, &posicion);
            break;
        case 2:
            SDL_BlitSurface(bloque2, NULL, smapa, &posicion);
            break;
        case 3:
            SDL_BlitSurface(bloque3, NULL, smapa, &posicion);
            break;
        case 4:
            SDL_BlitSurface(bloque4, NULL, smapa, &posicion);
            break;

            }

        }
        if( mapa[i][j] > 3 && mapa[i][j] < 255 ){                    //implementa los portales
              posicion.y = i*16 -10;
            SDL_BlitSurface(portal, NULL, smapa, &posicion);
        } else if ( mapa[i][j] == 3){

            posicion.y = i*16 -6;
             SDL_BlitSurface(lapida, NULL, smapa, &posicion);        //implementa la casilla de incio
        } else if ( mapa[i][j] == 255){

            posicion.y = i*16 -9;
             SDL_BlitSurface(fin, NULL, smapa, &posicion);             //implementa la casilla final
        }
    }
}


}

void represent(SDL_Surface *smapa,SDL_Surface *fondo,SDL_Surface *personaje,SDL_Surface *principal, casilla posicion, SDL_Window *ventana, int w, int h, int M, int dire){

SDL_FillRect(principal, NULL, 255);                         //esta función genera una sucesion de superficies que simulan una fluidez con las siguientes capas: fondo, mapa(grafico) y personaje

float frames = 0.1;
float i = 0;
float s;
float j = 0;
float l;
switch (dire){ // en función de la dirección elige la correcta animación
case -1:
    s=0;
    l=3;
    break;
case 0:
    s= 0;
    l= -frames;
    posicion.y++;
    break;
case 1:
    posicion.x--;
    l= 0;
    s= frames;
    break;
case 2:
    s= 0;
    l= +frames;
    posicion.y--;
    break;
case 3:
     posicion.x++;
    l= 0;
    s= -frames;
    break;



}
    SDL_Rect stretchRect;

    for ( i = 0  ; (sqrt(i*i) <= 1.01) && (sqrt(j*j) <= 1.01)  ; i = i + s ){


            stretchRect.x = (-2560+wpantalla) * (posicion.x+i)/(M-1.0);
            stretchRect.y = (-1440+hpantalla) * (posicion.y+j)/(M-1.0);
            stretchRect.w = 2560; //resolucion del fondo en cuestión
            stretchRect.h = 1440;


  SDL_BlitScaled( fondo, NULL, principal, &stretchRect );



            stretchRect.x =   -((posicion.x+i+1-(w+1)/2.0))*((wpantalla+0.0)/(1*16))*16/ (w+0.0);//  se restan casillas para centrar la imagen
            stretchRect.y =   -((posicion.y+j+1-(h+1)/2.0))*((hpantalla+0.0)/(1*16)) *16/(h+0.0);
            stretchRect.w = ((wpantalla+0.0)/(16)) *1*16*M  /(w+0.0);
            stretchRect.h = ((hpantalla+0.0)/(16))  *1*16*M  /(h+0.0);  // (proporcion resolución pantalla / resolucion mapa) * (tamaño mapa) * (porcion representada)


  SDL_BlitScaled( smapa, NULL, principal, &stretchRect );

            stretchRect.x = wpantalla/2-wpantalla/(2.0*w);
            stretchRect.y = hpantalla/2-hpantalla*2.0/(2.0*h);
            stretchRect.w = wpantalla/w;
            stretchRect.h = 1.5*hpantalla/h;


  SDL_BlitScaled( personaje, NULL, principal, &stretchRect );


   SDL_UpdateWindowSurface( ventana );
   j = j + l;

   }



}

casilla casinicial(int mapa[N][N], int n){
    int i, j;
    casilla inicio;
for (i = 0; i<n; i++){
    for ( j = 0; j<n; j++){
        if ( mapa[j][i]== 3){
            inicio.y = j;
            inicio.x = i;
        }
    }
}
return inicio;

}

casilla teletransporte(int mapa[N][N], casilla posicion, int n){
    int i, j;
    i = posicion.x+1;
    j = posicion.y;

    casilla retorno;
    while ( mapa[posicion.y][posicion.x] != mapa[j][i] ){

        if ( i<n-1){
            i++;
        }else if( j<n-1){
            i = 0;
            j++;
        }else{
            i= 0;
            j= 0;
        }
    }
    retorno.x = i;
    retorno.y = j;
    return retorno;


}
SDL_Surface *cargarimagen(char local[20] ){

SDL_Surface *aux;
    aux = SDL_LoadBMP( local );
    if (aux == NULL){
        printf("error al cargar imagen: %s", local);
        return 0;
    }
SDL_SetColorKey(aux, SDL_TRUE, SDL_MapRGB(aux->format, 0,0,0));
    return aux;
}

_Bool cargarfondo( SDL_Surface **fondo){


SDL_Surface *aux;



    aux = SDL_LoadBMP( "img/fondo.bmp" );
    if (aux == NULL){
        printf("error al cargar imagen: fondo.bmp");
        return 0;
    }
    *fondo = aux;



return 1;
}
//final de función
void semilla(){
    time_t t;
    int tiempo = time(&t);
    //tiempo = 1653664203;
   srand((unsigned)  tiempo);

  // printf( "%li \n", tiempo);

   FILE *pf;
    pf = fopen("registro.txt", "a");

    fprintf(pf, "%i --> %s \n" , tiempo, ctime(&t));

    fclose(pf);
}

void minimapa( SDL_Surface *smapa,SDL_Surface *fondo, SDL_Surface *principal, SDL_Window *ventana){

SDL_Rect stretchRect;

            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = 1280; //resolucion del fondo en cuestión
            stretchRect.h = 720;

  SDL_BlitScaled( fondo, NULL, principal, &stretchRect );






            stretchRect.x = 280;
            stretchRect.y = 0;
            stretchRect.w = 720; //resolucion del fondo en cuestión
            stretchRect.h = 720;


  SDL_BlitScaled( smapa, NULL, principal, &stretchRect );
  SDL_UpdateWindowSurface( ventana );

}

//funciones
int representar (int matriz[filas][columnas], int col, int fil){
    int i, j;
    for ( i=0; i<col; i++ ){
        for (j= 0; j<fil; j++){

            switch (matriz[i][j]){
            case 0:
                printf("%c ", ' ');
                break;
            case 1:
                printf("%c ", ' ');
                break;
            case 2:
                printf("%c ", '#');
                break;
            case 3:
                printf("%c ", '3');
                break;
            case 4:
                printf("%c ", '4');
                break;
            case 5:
                printf("%c ",  '5');
                break;
            case -1:
                printf("%c ",  'F');
                break;
            case 255:
                printf("%c ",  'E');
                break;
            default:
               // printf("%i ", matriz[i][j]);
                break;

            }
            //printf(",");


        }
        printf("\n");

    }
}

void matriznula (int matriz[filas][columnas], int col, int fil){
    int i, j;
    for ( i=0; i<col; i++ ){
        for (j= 0; j<fil ; j++){
            matriz[i][j] = 0;
        }
    }
    for ( i = 0 ; i <col ; i++){  //problema en matrices no cuadradas
        matriz[0][i]=2;
        matriz[fil-1][i]=2;
    }
    for ( i = 0 ; i <fil ; i++){  //problema en matrices no cuadradas
        matriz[i][0]=2;
        matriz[i][col-1]=2;
    }

}
casilla iniciocasilla(int matriz[filas][columnas], casilla inicio, int *num){
    casilla siguiente;
    int a, i, j;
    matriz[inicio.y][inicio.x]= *num;
    a = rand () %4;                            //elige un camino aleatorio
    for ( i = -1; i < 2; i++){
        for (j= -1; j < 2; j++){
            if (  !(j==0 && i== 0)   && j*j == i*i){                //construye las paredes iniciales del laberinto
                matriz[inicio.y +i][inicio.x +j] = 2;
            } else if (!(j==0 && i== 0) && a == 0 && i*i != j*j ){

                matriz[inicio.y + i][inicio.x +j ] = 1;
                siguiente.y = inicio.y +i ;
                siguiente.x = inicio.x +j ;

                a = a -1;
            }else if (!(j==0 && i== 0) && a != 0 && i*i != j*j){
                matriz[inicio.y +i][inicio.x +j] = 2;
                a = a -1;
            }
        }
    }
    *num += 1;

    return siguiente;
}

void crear ( int matriz [filas][columnas],  int col,  int fil){
    matriznula(matriz, col , fil );
    casilla siguiente;
    int i, j, dire, numinicio= 3;
    casilla inicio;

    inicio.y= rand() % (fil / 2) + fil/4; // establece unas coordenadas de inicio aleatorias !cuidado con estos valores
    inicio.x= rand() % (col / 2) + col/4;

    siguiente = iniciocasilla( matriz,  inicio, &numinicio);
    dire = direccion(inicio, siguiente);
    seguir(matriz,siguiente,dire);


int x, y, cont=1;

     for (i=4; i<col-3; i++){
        for ( j= 4; j<fil-3; j++){
            inicio.x= i;
            inicio.y= j;
           for( x=i-4 ; x<= i+4; x++){
                for (y = j-4; y <= j+4; y++){

                    if(matriz[y][x] != 0){
                        cont = 0;
                    }
                }
            }
            if (cont == 1){

               casilla fin = ffinales(matriz,-1, col, fil);
               matriz[fin.y][fin.x] = numinicio;
               siguiente = iniciocasilla(matriz, inicio, &numinicio);
               dire = direccion(inicio, siguiente);
               seguir(matriz,siguiente, dire);

            }
            cont =1 ;
        }
     }






     casilla fin = ffinales(matriz,-1, col, fil);


     matriz[fin.y][fin.x] = 255;



}

 void seguir( int matriz [filas][columnas], casilla posicion, int dire){
    int i, j, cont;

    printf("\n");


     dire = (4 + dire) %4;
     casilla siguiente = vect(posicion, dire);

     if ( comprovar(matriz, siguiente)==1){
        int vectdifur[6] = {50,50,50,50,50,50};
        int camgirdif[4]= {40,6,6,40};
        switch ( probabilidad(4, camgirdif)){
        case 0:
            cam(matriz, siguiente, dire);
            seguir( matriz, siguiente, dire);
            break;
        case 1:
            construir(matriz, siguiente, dire, 'l');
            seguir( matriz,  vect(siguiente, dire -1   ), dire -1);
            break;
        case 2:
            construir(matriz, siguiente, dire, 'r');
            seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
            break;
        case 3:


            switch (probabilidad(6, vectdifur)){
                case 0:
                    construir(matriz, siguiente, dire, 'd');
                    seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
                    seguir( matriz,  vect(siguiente, dire -1   ), dire - 1);
                    break;
                case 1:
                    construir(matriz, siguiente, dire, 'd');
                    seguir( matriz,  vect(siguiente, dire -1   ), dire -1);
                    seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
                    break;
                case 2:
                    construir(matriz, siguiente, dire, 'R');
                    seguir( matriz,  vect(siguiente, dire    ), dire );
                    seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
                    break;
                case 3:
                    construir(matriz, siguiente, dire, 'L');
                    seguir( matriz,  vect(siguiente, dire -1   ), dire -1);
                    seguir( matriz,  vect(siguiente, dire    ), dire );
                    break;
                case 4:
                    construir(matriz, siguiente, dire, 'L');
                    seguir( matriz,  vect(siguiente, dire    ), dire );
                    seguir( matriz,  vect(siguiente, dire -1   ), dire -1);
                    break;
                case 5:
                    construir(matriz, siguiente, dire, 'R');
                    seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
                    seguir( matriz,  vect(siguiente, dire    ), dire );
                    break;
            }
            break;
        }


    } else {

        cerrar( matriz, posicion);

        cont = 0;
        for ( i = -1; i <= 1; i++){
            for (j = -1; j<= 1; j++){
                if ( !(j == 0 && i == 0) && matriz[posicion.y+i][posicion.x+j] == 2 ){   // comprueba que las casillas cercanas no sumen un numero total mayor a 3
                    cont = cont +1;
                }
            }
        }

        if (cont >= 6){
            matriz[posicion.y][posicion.x]= -1;
        }

     }


 }


_Bool comprovar ( int matriz [filas][columnas], casilla siguiente){ // comprueba que se pueda construir un camino
    int i;
    int j;
    int cont = 0;
    if ( matriz[siguiente.y][siguiente.x] != 0){                                        // comprueba que la casilla sea diferente de 0
        return 0;
    }

    for ( i = -1; i <= 1; i++){
        for (j = -1; j<= 1; j++){
            if ( !(j == 0 && i == 0) && matriz[siguiente.y+i][siguiente.x+j] != 0 ){   // comprueba que las casillas cercanas no sumen un numero total mayor a 3
               cont = cont +1;
            }
        }
    }


    if (cont > 3 ){
        return 0;
    } else if (cont <= 3 ){
        return 1;
    }
}

casilla ffinales ( int matriz [filas][columnas], int num, int col, int fil){
    int i;
    int j;
    int cont=0;
    casilla lista[N*N/2];

    for(i = 0; i< col; i++){
        for(j = 0 ; j<fil; j++){
            if( matriz[j][i] == num){
                lista[cont].x = i;
                lista[cont].y = j;
                cont++;
            }
        }
    }
    int aleatorio = rand() % cont;

return lista[aleatorio];

}


void cam( int matriz[filas][columnas], casilla siguiente, int dire){                // escribe un camino en funcion de la dirección y la casilla
    switch (dire%2)
  {
  case 0 :
    matriz[siguiente.y][siguiente.x]= 1;
    matriz[siguiente.y][siguiente.x+1]= 2;
    matriz[siguiente.y][siguiente.x-1]= 2;
    break;
  case 1:
    matriz[siguiente.y][siguiente.x]= 1;
    matriz[siguiente.y+1][siguiente.x]= 2;
    matriz[siguiente.y-1][siguiente.x]= 2;
    break;

  }

}
int construir(int matriz[filas][columnas], casilla siguiente, int dire , char forma){       // construye un giro a la drecha / izquierda / difuración
    int i, j, s = 0;
    dire = (4+dire) %4;

    int l[6] = {1,1,2,2,2,2};
    int r[6] = {2,1,1,2,2,2};
    int d[6] = {1,1,1,2,2,2};
    int dl[6] = {1,1,2,2,1,2};
    int dr[6] = {2,1,1,2,1,2};
    int vecgiz[6];
    switch (forma) {
    case 'l':
        for( i = 0; i<6; i ++){vecgiz[i] = l[i] ;};
        break;
    case 'r':
        for( i = 0; i<6; i ++){vecgiz[i] = r[i] ;};
        break;
    case 'd':
        for( i = 0; i<6; i ++){vecgiz[i] = d[i] ;};
        break;
    case 'L':
        for( i = 0; i<6; i ++){vecgiz[i] = dl[i] ;};
        break;
    case 'R':
        for( i = 0; i<6; i ++){vecgiz[i] = dr[i] ;};
        break;
    }

    switch (dire){
    case 0:
        for ( i = 0; i<= 1; i++){ for ( j = -1; j<= 1; j++) {matriz[siguiente.y-i][siguiente.x +j]= vecgiz[s]; s =s+1;}};

        break;
    case 1:
        for ( i = 0; i<= 1; i++){ for ( j = -1; j<= 1; j++) {matriz[siguiente.y+j][siguiente.x +i]= vecgiz[s]; s =s+1;}};

        break;
    case 2:
        for ( i = 0; i<= 1; i++){ for ( j = -1; j<= 1; j++) {matriz[siguiente.y+i][siguiente.x -j]= vecgiz[s]; s =s+1;}};

        break;
    case 3:
        for ( i = 0; i<= 1; i++){ for ( j = -1; j<= 1; j++) {matriz[siguiente.y-j][siguiente.x -i]= vecgiz[s]; s =s+1;}};

        break;

    }

}



void cerrar( int matriz[filas][columnas], casilla  posicion){  // cierra un carril
    int i, j;
    for ( i = -1; i<=1; i++){
        for (j = -1; j<= 1; j++){
            if ( matriz[posicion.y+i][posicion.x+j] ==0){
                matriz[posicion.y+i][posicion.x+j] =2;
            }
        }
    }

}

int direccion ( casilla posicion, casilla siguiente){   // determina la dirección en función de dos casillas
    if( siguiente.y -posicion.y  == 1){

            return 2;
    } else if ( siguiente.y -posicion.y  == -1){

            return 0;
    } else if ( siguiente.x -posicion.x == 1){

            return 1;
    } else if ( siguiente.x -posicion.x == -1){

            return 3;
    }

}


casilla vect( casilla inicial, int dire){ // devuelve la casilla siguiente en función de la dirección
    dire = (4+dire )%4;
    casilla vuelta;
    switch (dire){
        case 0:
        vuelta.x = inicial.x;
        vuelta.y = inicial.y-1;
        break;
        case 1:
        vuelta.x = inicial.x+1;
        vuelta.y = inicial.y;
        break;
        case 2:
        vuelta.x = inicial.x;
        vuelta.y = inicial.y+1;
        break;
        case 3:
        vuelta.x = inicial.x-1;
        vuelta.y = inicial.y;
        break;


    }
    return vuelta;
}

int probabilidad( int n, int vector[]){  //saca un número del 0 al n-1 con las provabilidades del vector[]
    int aux[15];
    aux[0]= vector[0];
    int i;
    int total = 0;
    for (i = 0; i<n; i++){
        total = total + vector[i];   // saca el total del vector
    }
    for (i = 1; i<n; i++){
        aux[i] = vector[i] + aux[i-1];   // saca el total del vector
    }
    int aleatorio = rand() % total;
    if( aleatorio <= vector[0]){
        return 0;
    }
    for ( i = 0; i<n-1; i++){
        if ( aux[i]< aleatorio && aleatorio <= aux[i+1]  ){
            return (i+1);
        }
    }



}


void jugar(int n, int p){




if (SDL_Init(SDL_INIT_VIDEO) < 0)              //iniciación del video SDL
{
 printf("No se pudo inicializar SDL: %s\n",
 SDL_GetError());
 exit(1);
}

    SDL_Surface *personaje;
    SDL_Window  *ventana;
    SDL_Surface *principal;
    SDL_Surface *fondo;
    SDL_Surface *smapa;

    switch (p){                                                 //carga los personajes en funcion de la entrada
    case 0:
        personaje = cargarimagen("img/personaje.bmp");
    break;
    case 1:
        personaje = cargarimagen("img/personaje1.bmp");
    break;
    }

    smapa = SDL_CreateRGBSurface(32, 16*n,16*n,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);


    ventana = SDL_CreateWindow( "laberinto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wpantalla, hpantalla, SDL_WINDOW_SHOWN );
    principal = SDL_GetWindowSurface( ventana );

    cargarfondo( &fondo);


    semilla();                                              //guarda semilla y la imprime en un fichero

  int mapa[100][100];



  crear( mapa ,n,n);



    cargarmapa(smapa, n, n, mapa);



    casilla posicion = casinicial(mapa, n);

int dire;
int h=11, w= 19;



represent(smapa,fondo,personaje, principal, posicion, ventana,w,h,n, -1); //representación sin movimiento


_Bool cerrar = 0;

SDL_Event e;



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
                        represent(smapa, fondo, personaje, principal, posicion, ventana ,w,h,n, -1);
                    }
                    if (mapa[posicion.y][posicion.x]== 255){
                            cerrar = 1;
                        }




    }
}
}
SDL_Quit();
}

