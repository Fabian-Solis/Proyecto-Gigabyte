#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h> // Librería para sleep()
#include "hashmap.h"
#include "list.h"
#include "funciones.h"
#include "test.h"

#define MAX 16

typedef struct
{
  char nombre[MAX];
  bool revive;
  bool todos;
  int curacion;
  int pp;
  int cantidadObj;
} Objeto;

typedef struct
{
  char nombre[MAX];
  float multiplicador;
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


#define MAX 16

void cargarPokedex(HashMap *Pokedex, HashMap *Movimientos)
{
  FILE *fp = fopen("pokemon_pokedex.csv", "r");

  char linea[1024];
  char *cont;
  char *ataque;
  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Pokemon *pokemonAux = malloc(sizeof(Pokemon));
    pokemonAux -> muerto = false;
  
    for(int i = 0; i < 8; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : cont = strdup(aux); break;
        case 1 : strcpy(pokemonAux -> nombre, aux); break;
        case 2 : strcpy(pokemonAux -> tipo1, aux); break;
        case 3 : strcpy(pokemonAux -> tipo2, aux); break;
        case 4 : pokemonAux -> ataque = atoi(aux); break;
        case 5 : pokemonAux -> defensa = atoi(aux); break;
        case 6 : pokemonAux -> salud = atoi(aux); pokemonAux -> saludActual = atoi(aux); break;
        case 7 :
          
          pokemonAux -> habilidades = createList();
          
          for (int j = 0 ; j < 4 ; j++)
          {
            ataque = gets_csv_field(linea, j+7);
  
            if (strcmp(ataque, "-") == 0) continue;
            
            Pair *pairAux = searchMap(Movimientos, ataque);
            
            Ataque *ataqueAux = pairAux -> value;
            
            pushFront(pokemonAux -> habilidades, ataqueAux);
          }
          
          break;
      }
    }
    insertMap(Pokedex, cont, pokemonAux);
  }
  fclose(fp);
}

void cargarMovimientos(HashMap *Movimientos)
{
  FILE *fp = fopen("pokemon_movimientos.csv", "r");

  char linea[1024];
  int i;

  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Ataque *ataqueAux = malloc(sizeof(Ataque));

    for(int i = 0; i < 8; i++)
    {
      char *aux = gets_csv_field(linea, i);
      switch(i)
      {
        case 0 : strcpy(ataqueAux -> nombre, aux); break;
        case 1 : ataqueAux -> potencia = atoi(aux); break;
        case 2 : strcpy(ataqueAux -> tipo, aux); break;
        case 3 : ataqueAux -> precision = atoi(aux); break;
        case 4 : ataqueAux -> numUsosMAX = atoi(aux); ataqueAux -> numUsosActual = ataqueAux -> numUsosMAX; break;
        case 5 : ataqueAux -> efectoAtaque = atoi(aux); break;
        case 6 : ataqueAux -> efectoDefensa = atoi(aux); break;
        case 7 : ataqueAux -> efectoSalud = atoi(aux); break;
        case 8 : ataqueAux -> direccion = atoi(aux); break;
      }
    }
    insertMap(Movimientos, ataqueAux -> nombre, ataqueAux);
  }
  fclose(fp);
}

void cargarMultiplicadores(HashMap *multiplicadores)
{
  FILE *fp = fopen("pokemon_multiplicadores.csv", "r");

  char linea[1024];
  int i;

  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    TipoElem *multi = malloc(sizeof(TipoElem));

    for(i = 0; i < 2; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : strcpy(multi -> nombre, aux); break;
        case 1 : multi -> multiplicador = atof(aux); break;
      }
    }
    
    float multiplicador = multi -> multiplicador;
    float *ptr_multiplicador = malloc(sizeof(float));
    
    *ptr_multiplicador = multiplicador;

    insertMap(multiplicadores, multi -> nombre, ptr_multiplicador);
  }
  fclose(fp);
}

void cargarObjetos(HashMap *Objetos)
{
  FILE *fp = fopen("pokemon_objetos.csv", "r");

  char linea[1024];
  int i;

  fgets(linea, 1023, fp);
  
  while(fgets(linea, 1023, fp) != NULL)
  {
    Objeto *objetoAux = malloc(sizeof(Objeto));
    int revive;
    int todos;

    for(i = 0; i < 5; i++)
    {
      char *aux = gets_csv_field(linea, i);
      
      switch(i)
      {
        case 0 : strcpy(objetoAux -> nombre, aux); break;
        case 1 : objetoAux->curacion = atoi(aux); break;
        case 2 : objetoAux->pp = atoi(aux); break;
        case 3 : revive = atoi(aux);
          if (revive == 1) objetoAux -> revive = true;
          else objetoAux -> revive = false;
          break;
        case 4 : todos = atoi(aux);
          if(todos ==1) objetoAux->todos = true;
          else objetoAux->todos = false;
          break;
      }
    }
    insertMap(Objetos,objetoAux->nombre,objetoAux);
  }
  fclose(fp);
}


/*void cargarEntrenadoresLiga(Entrenador entrenadores[], HashMap *Pokedex, HashMap *Movimientos)
{
 
  
}
*/

