#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define filas 90
#define columnas 90
typedef struct {
    int x;
    int y;

} casilla;

//prototipo
casilla vect( casilla inicial, int dire);

void seguir( int matriz [filas][columnas],  casilla posicion,int dire);
_Bool comprovar ( int matriz [filas][columnas], casilla siguiente);
int direccion ( casilla posicion, casilla siguiente);

void crear ( int matriz [filas][columnas]);

int representar (int matriz[filas][columnas], int col, int fil);
int matriznula (int matriz[filas][columnas], int col, int fil); //todos los elementos de la matriz a 0

int construir(int matriz[filas][columnas], casilla siguiente, int dire , char forma);
void cam( int matriz[filas][columnas], casilla siguiente , int dire);
void cerrar( int matriz[filas][columnas], casilla posicion );

//main
int main(){
    time_t t;
    srand((unsigned) time(&t));

  int mapa[filas][columnas];
  matriznula(mapa, filas , columnas );
  crear( mapa );


  representar(mapa, filas ,columnas);










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
                printf("%c ", ' ');
                break;
            case 2:
                printf("%c ", '#');
                break;
            case 3:
                printf("%c ", '$');
                break;
            }


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

}


void crear ( int matriz [filas][columnas]){
    casilla siguiente;
    int i, j, a, dire;
    casilla inicio;
    inicio.x= rand() %30+40; // establece unas coordenadas de inicio aleatorias !cuidado con estos valores
    inicio.y= rand() %30+40;
    a = rand () %4;
    matriz[inicio.y][inicio.x]= 3;
                                //elige un camino aleatorio
    for ( i = -1; i < 2; i++){
        for (j= -1; j < 2; j++){
            if (  !(j==0 && i== 0)   && j*j == i*i){                //construye las paredes iniciales del laberinto
                matriz[inicio.y +i][inicio.x +j] = 2;
            } else if (!(j==0 && i== 0) && a == 0 && i*i != j*j ){

                matriz[inicio.y + i][inicio.x +j ] = 1;
                siguiente.y = inicio.y +i ;
                siguiente.x = inicio.x +j ;
                dire = direccion(inicio, siguiente);
                a = a -1;
            }else if (!(j==0 && i== 0) && a != 0 && i*i != j*j){
                matriz[inicio.y +i][inicio.x +j] = 2;
                a = a -1;
            }
        }
    }
    for ( i = 0 ; i <columnas ; i++){  //problema en matrices no cuadradas
        matriz[0][i]=2;
        matriz[columnas-1][i]=2;
        matriz[i][columnas-1]=2;
        matriz[i][0]=2;
    }

     seguir(matriz,siguiente,dire);

}

 void seguir( int matriz [filas][columnas], casilla posicion, int dire){
     dire = (4 + dire) %4;
     casilla siguiente = vect(posicion, dire);
     _Bool bo = comprovar(matriz, siguiente);
     if ( comprovar(matriz, siguiente)==1){

        int prob = rand()%120;
        if ( prob <= 70){
            cam(matriz, siguiente, dire);
            seguir( matriz, siguiente, dire);
        } else if ( prob > 70 && prob <= 75){
            construir(matriz, siguiente, dire, 'l');
            seguir( matriz,  vect(siguiente, dire -1   ), dire -1);
        } else if ( prob > 75 && prob <= 80 ){
           construir(matriz, siguiente, dire, 'r');
            seguir( matriz,  vect(siguiente, dire +1   ), dire +1);

        } else if ( prob > 80  ){
             construir(matriz, siguiente, dire, 'd');
            seguir( matriz,  vect(siguiente, dire +1   ), dire +1);
           seguir( matriz,  vect(siguiente, dire -1   ), dire - 1);
        }

    } else {

         cerrar( matriz, posicion);

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
