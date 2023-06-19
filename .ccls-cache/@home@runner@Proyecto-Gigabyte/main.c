#include <stdio.h>
#include "list.h"
#include "hashmap.h"
#include "funciones.h"
#include "importar.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // prints
#include <time.h> // prints
#include <unistd.h> // Librería para sleep()


#define MAX 16

typedef struct
{
  char nombre[MAX];
  bool revive;
  bool todos;
  int curacion;
  int pp;
  
} Objeto;

typedef struct
{
  char nombre[MAX];
  int multiplicador;
} TipoElem;

typedef struct
{
  
  char nombre[MAX];
  char tipo[MAX];

  int potencia;
  int precision;

  int numUsosMAX;
  int numUsosActual;

  int efectoAtaque;
  int efectoDefensa;
  int efectoSalud;

  int direccion;

} Ataque;

typedef struct
{
  TipoElem tipoElem[MAX];
  
  char nombre[MAX];
  char tipo1[MAX];
  char tipo2[MAX];

  List *habilidades;

  int ataque;
  int defensa;
  int salud;
  int saludActual;

  bool muerto;

} Pokemon;

typedef struct
{
  char nombre[MAX];
  Pokemon equipo[5];
  HashMap *mochila;
  int sizeTeam;
} Entrenador;

void mostrarPokedex(HashMap *Pokedex)
{
  Pair *aux = firstMap(Pokedex);
  char numPokedex[4];
  int n = 1;
  
  while(n != 152)
  {
    sprintf(numPokedex, "%i", n);
    
    Pair *aux2 = searchMap(Pokedex, numPokedex);
    Pokemon *pokemonAux = aux2 -> value;
    
    printf("%s.- %s - %s", numPokedex, pokemonAux -> nombre, pokemonAux -> tipo1);
    
    if (strcmp(pokemonAux -> tipo2, "0") != 0) printf(" & %s.\n", pokemonAux -> tipo2);
    else printf(".\n");
    
    n++;
  }
  puts("");
  
}

void agregarPokemon(Entrenador entrenadores[], int *equipoRegistrado, HashMap *Pokedex)
{
  
  char pokemonPKDX[MAX];
  int buscar;
  int size = entrenadores[0].sizeTeam;

  if(size == 6)
  {
    printf("El equipo está lleno! No puedes agregar más Pokémon.\n\n");
    return;
  }
  
  //printf("Num equipo: %i\n", entrenadores[0].sizeTeam);
  
  puts("Ingrese número de la Pokédex del Pokémon a agregar:");
  
  while(1)
  {
    scanf("%15s", pokemonPKDX);
    getchar();
    
    buscar = atoi(pokemonPKDX);
    
    if (buscar < 1 || buscar > 151) puts("\nIngrese un número válido entre 1 y 151.");
    else break;
  }

  Pair *pokeBusc = searchMap(Pokedex, pokemonPKDX);
  Pokemon *pokeAux = pokeBusc -> value;
  
  printf("\nPokemon: '%s', deseas agregarlo a tu equipo? (s/n)\n", pokeAux -> nombre);

  char salida[2];
  scanf("%1s", salida);
  
  if(strcmp(salida, "n") == 0) 
  {
    puts("\nNo se agregó ningún Pokémon.\n");
    return;
  }
  
  puts("");

  size++;
  puts("Pokémon agregado!\n");
  
  entrenadores[0].equipo[entrenadores[0].sizeTeam] = *pokeAux;
  entrenadores[0].sizeTeam = size;
  
  *equipoRegistrado = 1;
}

void eliminarPokemon(Entrenador entrenadores[]) // O(1) promedio, o(n) peor caso
{
  //system("clear");
  
  bool encontrado = false;
  char pokemonElim[MAX];
  
  puts("Ingrese Pokémon a eliminar del equipo:");
  
  scanf("%15s", pokemonElim);
  getchar();
  
  for (int i = 0; i < entrenadores[0].sizeTeam; i++)
  {
    if (strcmp(entrenadores[0].equipo[i].nombre, pokemonElim) == 0)
    {
      entrenadores[0].equipo[i].nombre[0] = '\0'; // Marcar el nombre como cadena vacía
      entrenadores[0].sizeTeam--;
      encontrado = true;

      printf("\nPokémon '%s' ha sido eliminado del equipo!\n\n", pokemonElim);
      
      for (int j = i + 1; j < entrenadores[0].sizeTeam; j++)
      {
        if (entrenadores[0].equipo[j].nombre[0] != '\0')
        {
          entrenadores[0].equipo[i] = entrenadores[0].equipo[j];
          entrenadores[0].equipo[j].nombre[0] = '\0';
          i++;
        }
      }
      
      break;
    }
  }
  if (!encontrado) puts("\nEl Pokémon no está en el equipo\n");
  
}

void darObjetoPoke(Entrenador entrenadores[])
{
  
}

void administrarOrden(Entrenador entrenadores[])
{
  //system("clear");
  
  //printf("Num equipo: %i\n\n", entrenadores[0].sizeTeam);

  int size = entrenadores[0].sizeTeam;
  
  if (entrenadores[0].sizeTeam == 1)
  {
    puts("Solo hay un Pokémon en el equipo, debes añadir al menos uno más para acceder a esta función.\n");
    return;
  }
  
  int pos1, pos2;
  Pokemon aux;
  
  puts("Ingresa posición del Pokémon de origen:");
  scanf("%i", &pos1);
  pos1--;

  while(pos1 > size - 1 || pos1 < 0)
  {
    if (pos1 > size - 1) printf("\nIngresa posición del Pokémon de origen válida, el equipo solo tiene %i Pokémon:\n", entrenadores[0].sizeTeam);
    if(pos1 < 0) printf("\nEl número ingresado es inválido, ingresa un número positivo:\n");
    scanf("%i", &pos1);
    pos1--;
  }
  
  puts("\nIngresa posición del Pokémon de destino:");
  scanf("%i", &pos2);
  pos2--;

  while(pos2 > size - 1 || pos2 < 0)
  {
    if (pos2 > size - 1) printf("\nIngresa posición del Pokémon de destino válida, el equipo solo tiene %i Pokémon:\n", entrenadores[0].sizeTeam);
    if(pos2 < 0) printf("\nEl número ingresado es inválido, ingresa un número positivo:\n");
    scanf("%i", &pos2);
    pos2--;
  }
  
  if (pos1 == pos2)
  {
    puts("No se ha hecho ningún cambio, las posiciones son iguales.");
    return;
  }
  
  aux = entrenadores[0].equipo[pos1];
  entrenadores[0].equipo[pos1] = entrenadores[0].equipo[pos2];
  entrenadores[0].equipo[pos2] = aux;

  printf("\nPokémon '%s' ha sido intercambiado de posición con '%s'!\n\n", entrenadores[0].equipo[pos1].nombre, entrenadores[0].equipo[pos2].nombre);
  
}

void verEquipoActual(Entrenador entrenadores[])
{
  int i = 0;
  int size = entrenadores[0].sizeTeam;
  printf("EQUIPO POKÉMON DE '%s'\n\n", entrenadores[0].nombre);

  for (int i = 0 ; i < size ; i++)
  {
    printf("%i. %s (%i/%i) PS - Ataque: %i - Defensa : %i LVL. 100\n", i + 1, entrenadores[0].equipo[i].nombre, entrenadores[0].equipo[i].saludActual, entrenadores[0].equipo[i].salud, entrenadores[0].equipo[i].ataque, entrenadores[0].equipo[i].defensa);
  }
  
  puts("");
  
}

void administrarPokemon(Entrenador entrenadores[], int *equipoRegistrado, int *volverMenu, HashMap *Pokedex)
{
  
  puts("¿Qué deseas realizar?\n");

  puts("1. Agregar Pokémon a tu equipo.");
  puts("2. Eliminar Pokémon de tu equipo.");
  puts("3. Administrar movimientos Pokémon.");
  puts("4. Administrar orden de equipo.");
  puts("5. Dar objeto a Pokémon");
  puts("6. Ver tu equipo actual.");
  
  puts("\n7. Volver al menú.\n");
  
  int opcion = 0;
  
  validarOpcionPokemon(&opcion, *equipoRegistrado);

  switch (opcion)
  {
    case 0 : return;
    case 1 : agregarPokemon(entrenadores, equipoRegistrado, Pokedex); break;
    case 2 : eliminarPokemon(entrenadores); break;
    //case 3 : administrarMovimientos(entrenadores); break;
    case 4 : administrarOrden(entrenadores); break;
    case 5 : darObjetoPoke(entrenadores); break;
    case 6 :
    if (!*equipoRegistrado) break;  
    verEquipoActual(entrenadores); break;
    
    case 7 : *volverMenu = 1; return;
  }
}

void mostrarObjetos(HashMap *Objetos)
{
  //system("clear");
  
  Pair *auxMapa = firstMap(Objetos);
  int contador = 1;

  puts("");
  
  while (auxMapa != NULL)
  {
    Objeto *auxObjetos = auxMapa->value;

    printf("%d. %s.\n", contador, auxObjetos -> nombre);
    contador++;

    auxMapa = nextMap(Objetos);
  }
  
  puts("");
}

void agregarObjeto(HashMap *Objetos ,Entrenador entrenadores[])
{
  //system("clear");
  
  char item[MAX];
  int cantidad; 
  entrenadores[0].mochila = createMap(15);
  
  puts("\nIngrese el objeto a añadir:\n");
  scanf("%s", item);
  puts("\nIngrese la cantidad que quiere agregar (Max 99):");
  scanf("%d", &cantidad);
  
  while (cantidad < 0 || cantidad > 99)
  {
    puts("\nIngrese una cantidad válida (entre 0 y 99):");
    scanf("%d", &cantidad);
  }

  Entrenador entrenadorAux = entrenadores[0];

  Pair *objetoPair = searchMap(Objetos,item);

  if(objetoPair != NULL)
  {
    Objeto *mapaObjetos = objetoPair->value;
    int *ptrCantidad = malloc(sizeof(int));
    *ptrCantidad = cantidad;

    insertMap(entrenadorAux.mochila, mapaObjetos->nombre, ptrCantidad);
    
    
  }
  else{
    puts("Ingrese el nombre de un Item Valido");
    agregarObjeto(Objetos,entrenadores);
  }
  
}


void mostrarMochila(HashMap *mochila) 
{
  printf("Objetos en la mochila:\n");

  Pair *auxMapa = firstMap(mochila);
  int contador = 1;

  while (auxMapa != NULL) {
    char *nombreObjeto = auxMapa->key;
    int *cantidad = auxMapa->value;
    printf("%d. %s (Cantidad: %d)\n", contador, nombreObjeto, *cantidad);
    

    auxMapa = nextMap(mochila);
    contador++;
  }
}

void eliminarObjeto(HashMap *mochila)
{
  char item[MAX];
  printf("\nIngrese el objeto que desea eliminar de su mochila:\n");
  fgets(item, sizeof(item), stdin);
  item[strcspn(item, "\n")] = '\0';  // Eliminar el salto de línea final
  
  Pair *objeto = searchMap(mochila, item);
  if (objeto == NULL) {
    printf("El objeto no se encuentra en la mochila.\n");
    return;
  }

  eraseMap(mochila, item);
  printf("El objeto ha sido eliminado correctamente de la mochila.\n");
}

void administrarObjetos(HashMap *Objetos, Entrenador entrenadores[])
{
  //system("clear");
  
  int opcion;

  while (1)
  {
    puts("\n¿Qué deseas realizar?\n");
    puts("1. Ver todos los objetos disponibles.");
    puts("2. Agregar un objeto a tu mochila.");
    puts("3. Ver tus objetos.");
    puts("4. Eliminar un objeto de la mochila.");
    puts("5. Volver al menú.\n");

    // Leer la opción del usuario
    scanf("%d", &opcion);
    getchar(); // Limpiar el búfer de entrada

    switch (opcion) {
      case 1:
        mostrarObjetos(Objetos);
        break;
      case 2:
        agregarObjeto(Objetos, entrenadores);
        break;
      case 3:
        mostrarMochila(entrenadores[0].mochila);
        break;
      case 4:
        eliminarObjeto(entrenadores[0].mochila);
        break;
      case 5:
        return; // Salir del submenú y volver al menú principal
      default:
        puts("Ingrese una opción válida.");
    }
  }
}

// hacer dificultades

int calculoDano(HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores, Pokemon PokeAtaca, Pokemon PokeRecibe, Ataque ataque)
{
  srand(time(NULL));
  
  char *concatAttack;
  float bono, *mult1, *mult2, eficiencia, atk, potencia, defensaRecibe, randomAcc, modifAcc;
  
  if (strcmp(PokeAtaca.tipo1, ataque.tipo) == 0) bono = 1.5;
  else bono = 1;

  int crit;

  float *jaja = malloc(sizeof(float));
  *jaja = 1;

  randomAcc = rand() % 256;
  
  modifAcc = (ataque.precision / 100.0) * 255;
  
  if (randomAcc >= modifAcc)
  {
    printf("El ataque ha fallado!\n\n");
    return 0;
  }

  int probabilidadCrit = rand() % 100 + 1;
  
  if (probabilidadCrit <= 6) crit = 2;
  else crit = 1;

  char aux[16];

  strcpy(aux, ataque.tipo);
  
  concatAttack = strcat(aux, PokeRecibe.tipo1);
  
  Pair *aux4 = searchMap(Multiplicadores, concatAttack);
  mult1 = aux4 -> value;
  
  concatAttack = "\0";

  strcpy(aux, ataque.tipo);
  
  if (PokeRecibe.tipo2[0] == '0')
  {
    mult2 = jaja;
  }
  else
  {
    concatAttack = strcat(aux, PokeRecibe.tipo2);
    //printf("%s", concatAttack);
    
    Pair *aux5 = searchMap(Multiplicadores, concatAttack);
    
    if(aux5 == NULL) printf("a\n");
    
    mult2 = aux5 -> value;
  }
  
  eficiencia = *mult1 * *mult2;

  atk = PokeAtaca.ataque;
  potencia = ataque.potencia;

  defensaRecibe = PokeRecibe.defensa;
  
  float parte1 = ((2 * 100 * crit * 0.2) + 2);
  float parte2 = potencia * (atk/defensaRecibe);
  float parte3 = bono * eficiencia;

  float parte4 = ( ( (parte1 * parte2) / 50) + 2) * parte3;

  float var = rand() % 39 + 217;
  var = var / 255;
  
  float potenciaFinal = parte4 * var;

  /*printf("Eficiencia : %f\n", eficiencia);
  printf("atk : %f\n", atk);
  printf("defensa recibe : %i\n", PokeRecibe.defensa);
  printf("potencia : %i\n", ataque.potencia);
  printf("bono : %f\n", bono);
  printf("prob crit : %i\n", probabilidadCrit);
  printf("crit : %i\n", crit);
  printf("var : %f\n", var);
  
  printf("Parte 1 : %f\n", parte1);
  printf("Parte 2 : %f\n", parte2);
  printf("Parte 3 : %f\n", parte3);
  printf("Parte 4 : %f\n", parte4);
  */
  
  if (eficiencia == 0)
  {
    printf("No le afecta...\n\n");
    return 0;
  }
  
  if (crit == 2) printf("GOLPE CRÍTICO!\n\n");
  
  if (eficiencia == 0.25) printf("Muy poco eficaz...\n\n");
  else if (eficiencia == 0.5) printf("Poco eficaz...\n\n");
  else if (eficiencia == 2.0) printf("Es muy eficaz!\n\n");
  else if (eficiencia == 4.0) printf("ES MUY EFICAZ!\n\n");
  
  //printf("\n\n\n%f\n", potenciaFinal);
  
  return potenciaFinal;
}

void entrenamientoPokemon(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos, HashMap *Multiplicadores)
{
  system("clear");
  
  printf("BIENVENIDO AL MODO ENTRENAMIENTO!!\n\n");
  printf("El entrenador Jesicca será tu enemigo!\n\n");
  printf("Este será el equipo de Jessica contra el que te enfrentarás:\n\n");

  char pokeNum[MAX];
  int numPokedex;
  int size;
  
  srand(time(NULL));
  
  for(size = 0; size < 6; size++)
  {
    numPokedex = rand() % 152;
    
    sprintf(pokeNum, "%i", numPokedex);
  
    Pair *pokeKey = searchMap(Pokedex, pokeNum);
    Pokemon *pokeValue = pokeKey -> value;
  
    entrenadores[1].equipo[size] = *pokeValue;
    entrenadores[1].sizeTeam = size;

    printf("Pokemon %d: %s\n", size+1, entrenadores[1].equipo[size].nombre);
  }
  
  printf("\nLa batalla comienza ahora!!\n\n\n");

  printf("Jesicca envió a %s\n\n", entrenadores[1].equipo[0].nombre);
  printf("Ve %s!\n\n", entrenadores[0].equipo[0].nombre);
  
  while(true)
  {
    if(entrenadores[0].equipo[0].muerto == true || entrenadores[1].equipo[0].muerto == true) break;
    
    printf("Tu Pokémon: %s ", entrenadores[0].equipo[0].nombre);
    printf("(%i/%i) PS - LVL. 100\n\n", entrenadores[0].equipo[0].saludActual, entrenadores[0].equipo[0].salud);

    printf("Pokémon Enemigo: %s ", entrenadores[1].equipo[0].nombre);
    printf("(%i/%i) PS - LVL. 100\n\n", entrenadores[1].equipo[0].saludActual, entrenadores[1].equipo[0].salud);

    printf("Elija una opción:\n\n");
    
    printf("1. Atacar\n");
    printf("2. Cambiar Pokémon\n");
    printf("3. Usar Objeto\n");
    printf("4. Huir\n\n");
    
    int opcionMenuBatalla;
    
    scanf("%d", &opcionMenuBatalla);

    switch(opcionMenuBatalla)
    {
      case 1 :
        
        printf("\nElija el ataque:\n\n");

        char auxNombre[MAX];
        char ataque[MAX];
        int opcionAtaque;
        int i = 0;

        List *ataquesAux = List_clone(entrenadores[0].equipo[0].habilidades);
    
        Ataque *ataq = firstList(ataquesAux);
        
        while(ataq != NULL)
        {
          printf("%d. %s ", i + 1, ataq -> nombre);
          printf("[%d/%d] pp\n", ataq -> numUsosActual, ataq -> numUsosMAX);
          ataq = nextList(ataquesAux);
          i++;
        }
        
        puts("");
        scanf("%d", &opcionAtaque);
        puts("");
        
        ataq = firstList(ataquesAux);
        
        for(int j = 1 ; j != opcionAtaque ; j++) 
          ataq = nextList(ataquesAux);
        
        strcpy(ataque, ataq -> nombre);

        ataq -> numUsosActual--;
        
        printf("%s usó %s\n\n", entrenadores[0].equipo[0].nombre, ataque);

        int danio = calculoDano(Pokedex, Movimientos, Multiplicadores, entrenadores[0].equipo[0], entrenadores[1].equipo[0], *ataq);

        //printf("\n%i\n", danio);

        entrenadores[1].equipo[0].saludActual -= danio; 

        if(entrenadores[1].equipo[0].saludActual <= 0)
        {
          printf("%s enemigo se desmayó!\n\n", entrenadores[1].equipo[0].nombre);
          
          entrenadores[1].equipo[0].saludActual = 0;
          
          int i = 1;

          entrenadores[1].equipo[0].muerto = true;

          while(i < 6)
          {
            if(entrenadores[1].equipo[i].muerto == false)
            {
              Pokemon aux = entrenadores[1].equipo[0];
              entrenadores[1].equipo[0] = entrenadores[1].equipo[i];
              entrenadores[1].equipo[i] = aux;
              
              break;
            }
            else i++; 
          }
          char cambiarPokemon[MAX];
          
          printf("Jessica va a utilizar a %s ...\n\n", entrenadores[1].equipo[0].nombre);
          printf("%s, quieres cambiar de Pokémon? (s/n)\n", entrenadores[0].nombre);

          scanf("%s", cambiarPokemon);
          getchar();
          
          if(strcmp(cambiarPokemon, "s") == 0)
          {
            strcpy(auxNombre, entrenadores[0].equipo[0].nombre);
            administrarOrden(entrenadores);
            printf("%s vuelve\n\n", auxNombre);
            printf("Ve %s!\n", entrenadores[0].equipo[0].nombre);
          }

          printf("\nJesicca envió a %s!\n\n", entrenadores[1].equipo[0].nombre);
        }
         
        
        break;

      case 2 :
        
        strcpy(auxNombre, entrenadores[0].equipo[0].nombre);
        administrarOrden(entrenadores);
        printf("%s vuelve\n\n", auxNombre);
        printf("Ve %s!\n\n", entrenadores[0].equipo[0].nombre);
        break;
      
      case 3 :
        
        break;

      case 4 :
        escribirLentamente("Has huido de la batalla ...");
        puts("\n");
        //printf("\nHas huído de la batalla ... \n\n");
        return;
    }
  }
  
  for(size = 0; size < 6; size++)
  {
    printf("Pokemon %d: %s [%d/%d]\n", size+1, entrenadores[1].equipo[size].nombre, entrenadores[1].equipo[size].saludActual, entrenadores[1].equipo[size].salud);
  }

  puts("");
  escribirLentamente("Felicidades has vencido a la entrenadora Jessica!!");
  puts("\n");
  
  //printf("\nFelicidades has vencido a la entrenadora Jessica!!\n\n");
  
}


//void ligaPokemon()
//{}

//
int main()
{
/*
                      ____ _             _           _             
                     / ___(_) __ _  __ _| |__  _   _| |_ ___     
                    | |  _| |/ _` |/ _` | '_ \| | | | __/ _ \     
                    | |_| | | (_| | (_| | |_) | |_| | ||  __/     
                     \____|_|\__, |\__,_|_.__/ \__, |\__\___| 
                             |___/             |___/
                     ______                                      
                    (_____ \                           _         
                     _____) )___ ___  _   _  ____ ____| |_  ___  
                    |  ____/ ___) _ \| | | |/ _  ) ___)  _)/ _ \ 
                    | |   | |  | |_| | |_| ( (/ ( (___| |_| |_| |
                    |_|   |_|   \___/ \__  |\____)____)\___)___/ 
                                      (____/                      
*/

  char trainer_username[MAX];
  
  //printf("¡Bienvenido al simulador de combates de Pokémon Pokéduel!\n\n");

  escribirLentamente("Bienvenido al simulador de combates de Pokemon Pokeduel!");
  
  puts("\n");
  
  //printf("Ingresa tu nombre de entrenador!\n");
  
  escribirLentamente("Ingresa tu nombre de entrenador!");
  
  puts("");
  
  scanf("%s", trainer_username);
  getchar();
  
  int user_continue = 1, equipoRegistrado = 0;
  
  Entrenador entrenadores[7];
  
  strcpy(entrenadores[0].nombre, trainer_username);

  HashMap *Pokedex = createMap(151);
  HashMap *Movimientos = createMap(105);
  HashMap *Objetos = createMap(15);
  HashMap *Multiplicadores = createMap(225);
  
  cargarMultiplicadores(Multiplicadores);
  cargarMovimientos(Movimientos);
  cargarPokedex(Pokedex, Movimientos);
  cargarObjetos(Objetos);
  

  //cargarEntrenadoresLiga(entrenadores, Pokedex, Movimientos);
  
  //funciona2(Multiplicadores);
  //funciona3(Movimientos);
  //funciona4(Pokedex);
  
  while(user_continue)
  {
    int volverMenu = 0;
    menu();
    
    int opcion = 0;
    
    validarOpcion(&opcion); // Validamos que opción sea un número.
    
    if(equipoRegistrado == 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 6) printf("Debes registrar al menos un Pokémon en tu equipo para acceder!\n");
      
    else switch(opcion)
    {
      case 1 :
        mostrarPokedex(Pokedex);
        validar(&user_continue);
        break;

      case 2 :
        administrarPokemon(entrenadores, &equipoRegistrado, &volverMenu, Pokedex);
        if (volverMenu != 1) validar(&user_continue);
        break;

      case 3 :
        administrarObjetos(Objetos,entrenadores);
        validar(&user_continue);
        break;

      case 4 :
        entrenamientoPokemon(entrenadores, Pokedex, Movimientos, Multiplicadores);
        validar(&user_continue);
        break;

      case 5 :
        //ligaPokemon();
        validar(&user_continue);
        break;

      case 6 : 
        printf("Gracias por usar PokéDuel, adiós!");
        return 0;
    }
  }
  
  return 0;
}