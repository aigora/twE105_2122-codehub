    #include<stdio.h>
    #include<stdlib.h>


    void titulo();
    void bienvenida();
    void modosdejuego();
    void estandar();
    void contrareloj();
    void dificultad();
    void opciones();
    void skins();
    void salir();


    int main()
    {
       //Menu provisional.
       //Falta poner el titulo del programa con un generador de letras. O implementando la libreria grafica SDL
       titulo();
       system("cls");
       bienvenida();
       system("cls");




        return 0;

    }

    void titulo()
    {
        //Faltaría la creación del titulo. Con generador de matrices, este es provisional.
        printf("RANDOMAZE\n");
    }

    void bienvenida()
    {
        char selecciona;
        printf("Bienvenido a RandoMaze\n");
        printf("Seleccione alguna de las opciones:\n");
        printf("1-Jugar(J)\n");
        printf("2-Opciones(O)\n");

        scanf("%c", &selecciona);
        do
        {
        switch(selecciona)
        {
        case 'J':
        case 'j':
            modosdejuego();
            break;
        case 'O':
        case 'o':
            opciones();
            break;
        case 'V':
        case 'v':
            main();
        default:
            printf("seleccione una opcion valida\n");
        }
        }while (selecciona!='J'||selecciona!='j'||selecciona!='O'||selecciona!='o'||selecciona!='V'||selecciona!='v');

    }
    void modosdejuego()
    {
        char selecciona;
        printf("Selecciona entre los modos de jeugo disponibles:\n");
        printf("1-Contrareloj(C)\n");
        //Aun estamos trabajando en ello
        printf("2-estandar(E)\n");
        //Aun estamos trabajanod en ella
        printf("3-Volver(V)\n");
        do
        {
        switch(selecciona)
        {
        case 'C':
        case 'c':
            contrareloj();
            break;
        case 'E':
        case 'e':
            estandar();
            break;
        case 'V':
        case 'v':
            main();
        default:
            printf("seleccione una opcion valida\n");
        }
        }while (selecciona!='C'||selecciona!='c'||selecciona!='E'||selecciona!='e'||selecciona!='V'||selecciona!='v');
    }
    void estandar()
    {
        dificultad();
        //Aquí es cuando se iniciaría el programa en si, la generación de matrices. Con un modo estandar
        //aun trabajando en ella.
    }
    void contrareloj()
    {
        dificultad();
        //Aquí es cuando se iniciaría el programa en si, la generación de matrices. Con un modo contrareloj
        //Tiempo y alguna opcion más aún en discusión.
        //aun trabajando en ella.
    }
    void dificultad()
    {
        char selecciona;
        printf("Selecciona una dificultad\n");
        printf("Fácil(1)\n");
        printf("Normal(2)\n");
        printf("Difícil(3)\n");
        do
        {
        switch(selecciona)
        {
        case '1':
            //
            break;
        case '2':
            //
            break;
        case '3':
            //
            break;
        case 'V':
        case'v':
            modosdejuego();
        default:
            printf("seleccione una opcion valida\n");
        }
        } while (selecciona!='1'||selecciona!='2'||selecciona!='3'||selecciona!='V'||selecciona!='v');

    }
    void opciones()
    {
        char selecciona;
        printf("Seleccione alguna de estas opciones:\n");
        printf("Skins(1)\n");
        printf("Salir(2)\n");

        do
        {
        switch(selecciona)
        {
        case '1':
            //
            break;
        case '2':
            //
            break;
        case 'V':
        case 'v':
            bienvenida();
            break;
        default:
            printf("seleccione una opcion valida\n");
        }
        } while (selecciona!='1'||selecciona!='2'||selecciona!='V'||selecciona!='v');



    }

    void skins()
    {
        //Aun trabajando en ello con libreria SDL
    }
    void salir()
    {
        main();
    }



