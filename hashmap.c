#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}
/* 2.- Implemente la función void insertMap(HashMap * map, char * key, void * value). Esta función inserta un nuevo dato (key,value) en el mapa y actualiza el índice current a esa posición. Recuerde que para insertar un par (clave,valor) debe:

a - Aplicar la función hash a la clave para obtener la posición donde debería insertar el nuevo par

b - Si la casilla se encuentra ocupada, avance hasta una casilla disponible (método de resolución de colisiones). Una casilla disponible es una casilla nula, pero también una que tenga un par inválido (key==NULL).

c - Ingrese el par en la casilla que encontró.

No inserte claves repetidas. Recuerde que el arreglo es circular. Recuerde actualizar la variable size.
*/

void insertMap(HashMap * map, char * key, void * value) {
  
  if(map==NULL) return;
    
  //
    
  int pos = hash(key,map->capacity);

  //el bucket está vacío o invalidado
  if (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) {
    Pair* newElem = malloc(sizeof(Pair));
    newElem->value = value;
    newElem->key = key;
    map->buckets[pos] = newElem;
    map->size++;
  }
  //resolver colision
  if (map->buckets[pos]->key != NULL) {
    for (int i = 0; i < map->capacity; i++) {
      if (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) {
        Pair* newElem = malloc(sizeof(Pair));
        newElem->value = value;
        newElem->key = key;
        map->buckets[pos] = newElem;
        map->size++;
      }
    }
  }
    


}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap *createMap(long capacity) {
    // Reserva memoria para cada dato de esta struct
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL) return NULL;
  

    map->capacity = capacity;
    map->current = -1;

    // Reservar memoria para los buckets
    // se hace con calloc para que se inicien en NULL
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
    if (map->buckets == NULL) {
        free(map); // se libera la memoria de al estructura
        return NULL;
    }

    map->size = 0;

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
