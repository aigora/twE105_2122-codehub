


#include <stdio.h>
#include <stdlib.h>

#define filas 100
#define columnas 100
#define wpantalla 1280
#define hpantalla 720
#define N 100

typedef struct {
    int x;
    int y;

} casilla;


casilla vect( casilla inicial, int dire);   //saca la siguiente casilla en función de la dirección
int probabilidad( int n, int vector[]);     //a partir de un vector de probabilidades devuelve una opción
int direccion ( casilla posicion, casilla siguiente);   //saca la dirección a partir de dos posiciones, direcciónes: 0 arriba, 1 derecha, 2 abajo, 3 izquierda

casilla iniciocasilla(int matriz[filas][columnas], casilla inicio, int *num);
void crear ( int matriz [filas][columnas], int col, int fil);
void seguir( int matriz [filas][columnas],  casilla posicion,int dire);
_Bool comprovar ( int matriz [filas][columnas], casilla siguiente);
casilla ffinales ( int matriz [filas][columnas], int num, int col, int fil); //devuelve la posicion aleatoria de el valor pedido ej: ffinales(matriz, 7): devuelve una posicion de uno de los 7s de la matriz

int construir(int matriz[filas][columnas], casilla siguiente, int dire , char forma);
void cam( int matriz[filas][columnas], casilla siguiente , int dire);
void cerrar( int matriz[filas][columnas], casilla posicion );


int representar (int matriz[filas][columnas], int col, int fil);  //representa la función
void matriznula (int matriz[filas][columnas], int col, int fil); //todos los elementos de la matriz a 0

//criterio casillas 0 = vacio, 1 = camino, 2 = muro, 3 = incio, -1 = posible final, 5 = final

void semilla();

casilla casinicial(int mapa[N][N], int n);
SDL_Surface *cargarimagen(char local[20] );
//void prueba(SDL_Surface** prova);
void represent(SDL_Surface *smapa,SDL_Surface *fondo, SDL_Surface *personaje,SDL_Surface *principal, casilla posicion, SDL_Window *ventana, int w, int h, int M, int dire);
void minimapa( SDL_Surface *smapa,SDL_Surface *fondo, SDL_Surface *principal, SDL_Window *ventana );
_Bool cargarimagenes(SDL_Surface *principal, SDL_Surface **fondo, SDL_Surface **personaje);
_Bool cargarmapa(SDL_Surface *smapa, int n, int mapa[N][N]);
casilla teletransporte(int mapa[N][N], casilla posicion, int n);

