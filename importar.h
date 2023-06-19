#ifndef importar_h
#define importar_h
#include "hashmap.h"

void cargarPokedex(HashMap *Pokedex, HashMap *Movimientos);

void cargarMovimientos(HashMap *Movimientos);

void cargarMultiplicadores(HashMap *multiplicadores);

//void cargarEntrenadoresLiga(Entrenador entrenadores[], HashMap *Pokedex)

void cargarObjetos(HashMap *Objetos);


#endif /* importar_h */