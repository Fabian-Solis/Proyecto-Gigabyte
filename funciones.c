#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // prints
#include <time.h> // prints
#include <unistd.h> // Librería para sleep()

#define MAX 16

void menu() // Opciones del menú.
{
  printf("\nElige una opción a continuación:\n");

  printf("\n1. Mostrar la Pokédex.");
  printf("\n2. Administrar Pokémon."); // administrar movimientos tambien
  printf("\n3. Administrar objetos.");
  printf("\n4. Entrenamiento Pokémon.");
  printf("\n5. Entrar a la liga Pokémon.");
  printf("\n6. Salir del programa.\n");
  
  printf("\n");
}

void validarOpcion(int *opcion) // Valida las opciones del menú.
{
  char opcionAux[MAX];
  
  while (true) 
  {
    scanf("%15s", opcionAux);
    printf("\n");
      
    if (isdigit(*opcionAux)) 
    {
      *opcion = atoi(opcionAux);
        
      if (*opcion >= 1 && *opcion <= 10) break;
      else printf("Debe ingresar un número válido entre 1 y 10.\n");
    }
    else printf("Debe ingresar un número válido entre 1 y 10.\n");
    
    getchar();
  }
}

void validarOpcionPokemon(int *opcion, int equipoRegistrado) // Valida las opciones del menú.
{
  char opcionAux[MAX];
  
  while (true) 
  {
    scanf("%15s", opcionAux);
    printf("\n");
      
    if (isdigit(*opcionAux)) 
    {
      *opcion = atoi(opcionAux);
        
      if (*opcion >= 1 && *opcion <= 7)
      {
        if(*opcion != 1 && *opcion != 6 && *opcion != 7 && !equipoRegistrado) 
        {
          puts("Debes registrar al menos un Pokémon en tu equipo para acceder a esta opción!\n");
          *opcion = 0;
        }
      }
      else printf("Debe ingresar un número válido entre 1 y 7.\n");
    }
    else printf("Debe ingresar un número válido entre 1 y 7.\n");
    break;
    getchar();
  }
}

void validar(int *user_continue) // Validamos que el usuario desee seguir con la ejecución del programa.
{
  char salida[2];
  
  printf("Desea realizar otra operación? (s/n)\n");
  scanf("%1s", salida);
  
  if(strcmp(salida, "n") == 0)
  {
    *user_continue = 0;
    printf("\nGracias por usar el programa, adiós!");
  }
  else while (strcmp(salida, "s") != 0)
  {
    printf("Ingrese una opción válida\n\n");
    printf("Desea realizar otra operación? (s/n)\n");
    scanf("%1s", salida);
  }
}

char *gets_csv_field(char *tmp, int k) //
{
  int open_mark = 0;
  char *ret = (char*) malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  int last_field = 0;
  
  while (tmp[i + 1] != '\0')
  {  
    if(tmp[i] == '\"')
    {
      open_mark = 1 - open_mark;
      if(open_mark) ini_i = i + 1;
      i++;
      continue;
    }
    
    if(open_mark || tmp[i] != ',')
    {
      if(k == j) ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if(tmp[i] == ',')
    {
      if(k == j) 
      {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++; 
      ini_i = i + 1;
    }
    i++;
  }

  if(k == j) 
  {
    last_field = 1;
    ret[i - ini_i] = 0;
    return ret;
  }
  
  return NULL;
}

void escribirLentamente(char* cadena) 
{
  for (int i = 0; cadena[i] != '\0'; i++) 
  {
    printf("%c", cadena[i]); 
    fflush(stdout); 
    usleep(2);
  }
}