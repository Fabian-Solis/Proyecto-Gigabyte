#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // prints
#include <time.h> // prints
#include <unistd.h> // Librería para sleep()
#include "hashmap.h"
#include "list.h"
#include "funciones.h"

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

} Pokemon;

typedef struct
{
  char nombre[MAX];
  Pokemon equipo[5];
  HashMap *mochila;
  int sizeTeam;
} Entrenador;

void funciona2(HashMap *multiplicadores)
{
  Pair *aux = firstMap(multiplicadores);
  
  while (aux != NULL)
  {
    char *tipos = aux -> key;
    float *multi = aux -> value;
    printf("Tipo: %s, Multiplicador: %.1f\n", tipos, *multi);
    
    aux = nextMap(multiplicadores);
  }
}

void funciona3(HashMap *Movimientos)
{
  Pair *aux = firstMap(Movimientos);
  
  while (aux != NULL)
  {
    char *tipos = aux -> key;
    Ataque *a = aux -> value;
    
    printf("Nombre: %s -", tipos);
    printf(" D: %i\n", a->efectoDefensa);
    aux = nextMap(Movimientos);
  }
}

void funciona4(HashMap *Pokedex)
{
  Pair *aux = firstMap(Pokedex);

  while (aux != NULL)
  {
    Pokemon *poke = aux->value;
    
    printf("Pokemon: %s\nAtaques: ", poke->nombre);

    List *ataquesAux = List_clone(poke->habilidades);
    
    Ataque *ataq = firstList(ataquesAux);

    while (ataq != NULL)
    {
      printf("%s - ", ataq->nombre);
      ataq = nextList(ataquesAux);
    }

    puts("\n");
    aux = nextMap(Pokedex);
  }
}

/*void funciona(HashMap *habilidades)
{
  Pair *aux = firstMap(habilidades);
  
  while (aux != NULL)
  {
    TipoElem *auxMap = aux->value;  
    char *tipo = auxMap->nombre;
    int multiplicador =auxMap->multiplicador;
    printf("Tipo: %s, Multiplicador: %d\n", tipo, multiplicador);
    
    aux = nextMap(habilidades);
  }
}
*/