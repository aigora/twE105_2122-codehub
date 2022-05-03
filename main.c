#include <stdio.h>
#include <stdlib.h>




#define filas 30
#define columnas 100


typedef struct {
    int x;
    int y;

} casilla;


casilla vect( casilla inicial, int dire);   //saca la siguiente casilla en función de la dirección
int probabilidad( int n, int vector[]);     //a partir de un vector de probabilidades devuelve una opción
int direccion ( casilla posicion, casilla siguiente);   //saca la dirección a partir de dos posiciones, direcciónes: 0 arriba, 1 derecha, 2 abajo, 3 izquierda

casilla iniciocasilla(int matriz[filas][columnas], casilla inicio, int *num);
void crear ( int matriz [filas][columnas]);
void seguir( int matriz [filas][columnas],  casilla posicion,int dire);
_Bool comprovar ( int matriz [filas][columnas], casilla siguiente);
casilla ffinales ( int matriz [filas][columnas], int num); //devuelve la posicion aleatoria de el valor pedido ej: ffinales(matriz, 7): devuelve una posicion de uno de los 7s de la matriz

int construir(int matriz[filas][columnas], casilla siguiente, int dire , char forma);
void cam( int matriz[filas][columnas], casilla siguiente , int dire);
void cerrar( int matriz[filas][columnas], casilla posicion );


int representar (int matriz[filas][columnas], int col, int fil);  //representa la función
int matriznula (int matriz[filas][columnas], int col, int fil); //todos los elementos de la matriz a 0

//criterio casillas 0 = vacio, 1 = camino, 2 = muro, 3 = incio, -1 = posible final, 5 = final

//main
int main(){


    time_t t;
    srand((unsigned)  time(&t));
    //srand(1651588327);
   printf( "%li \n", time(&t));

  int mapa[filas][columnas];
  matriznula(mapa, filas , columnas );

  crear( mapa );


    representar(mapa, filas ,columnas);
    int s;
    scanf("  %i", &s );
    system("cls");


    main();








return 0;


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
                printf("%c ", '#');
                break;
            case 2:
                printf("%c ", '&');
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
                printf("%c ",  '#');
                break;
            default:
                printf("%i ", matriz[i][j]);
                break;

            }
            //printf(",");


        }
        printf("\n");

    }
}

int matriznula (int matriz[filas][columnas], int col, int fil){
    int i, j;
    for ( i=0; i<col; i++ ){
        for (j= 0; j<fil ; j++){
            matriz[i][j] = 0;
        }
    }
    for ( i = 0 ; i <columnas ; i++){  //problema en matrices no cuadradas
        matriz[0][i]=2;
        matriz[filas-1][i]=2;
    }
    for ( i = 0 ; i <filas ; i++){  //problema en matrices no cuadradas
        matriz[i][0]=2;
        matriz[i][columnas-1]=2;
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

void crear ( int matriz [filas][columnas] ){
    casilla siguiente;
    int i, j, dire, numinicio= 3;
    casilla inicio;

    inicio.y= rand() % (filas / 2) + filas/4; // establece unas coordenadas de inicio aleatorias !cuidado con estos valores
    inicio.x= rand() % (columnas / 2) + columnas/4;

    siguiente = iniciocasilla( matriz,  inicio, &numinicio);
    dire = direccion(inicio, siguiente);
    seguir(matriz,siguiente,dire);


int x, y, cont=1;

     for (i=4; i<columnas-3; i++){
        for ( j= 4; j<filas-3; j++){
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

               casilla fin = ffinales(matriz,-1);
               matriz[fin.y][fin.x] = numinicio;
               siguiente = iniciocasilla(matriz, inicio, &numinicio);
               dire = direccion(inicio, siguiente);
               seguir(matriz,siguiente, dire);

            }
            cont =1 ;
        }
     }






     casilla fin = ffinales(matriz,-1);


     matriz[fin.y][fin.x] = 255;



}

 void seguir( int matriz [filas][columnas], casilla posicion, int dire){
    int i, j, cont;



     dire = (4 + dire) %4;
     casilla siguiente = vect(posicion, dire);

     if ( comprovar(matriz, siguiente)==1){
        int vectdifur[4] = {50,50,50,50,50,50};
        int camgirdif[4]= {30,4,4,60};
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

casilla ffinales ( int matriz [filas][columnas], int num){
    int y = rand() % filas;
    int x = rand() % columnas;

    while ( matriz[y][x]!= num){
        if ( x < columnas  && y <= filas){
            x = x+1;
        } else if (x == columnas && y<filas){
            x = 0;
            y = y+1;
        } else if( (x >= columnas && y >= filas) ){
            x= 0;
            y = 0;
        }

    }
    return (casilla) {x , y};
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

int probabilidad( int n, int vector[]){
    int i;
    int total = 0;
    for (i = 0; i<n; i++){
        total = total + vector[i];   // saca el total del vector
    }
    for (i = 1; i<n; i++){
        vector[i] =vector[i] + vector[i-1];   // saca el total del vector
    }
    int aleatorio = rand() % total;
    if( aleatorio <= vector[0]){
        return 0;
    }
    for ( i = 0; i<n-1; i++){
        if ( vector[i]< aleatorio && aleatorio <= vector[i+1]  ){
            return (i+1);
        }
    }



}
