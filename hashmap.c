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


void insertMap(HashMap *map, char *key, void *value) {
  if (map == NULL || key == NULL) return;

  int pos = hash(key, map->capacity);
  int originalPos = pos;

  while (map->buckets[pos] != NULL && map->buckets[pos]->key != NULL) {
    //si la clave ya existe, no se inserta el elemento
    if (strcmp(map->buckets[pos]->key, key) == 0)return;

    pos = (pos + 1) % map->capacity; //mverse a la siguiente posición (circularmente)
    if (pos == originalPos) return;
  }


  //insertar el nuevo elemento en la posición encontrada
  Pair *newElem = malloc(sizeof(Pair));
  newElem->value = value;
  newElem->key = key;
  map->buckets[pos] = newElem;
  map->size++;
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)

  //copia arreglo antiguo
  Pair **old_buckets = map->buckets;
  int old_capacity = map->size;

  //agrandar al doble
  map->capacity *= 2;

  map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));

  map->size = 0;
  
  for (int i = 0; i < old_capacity; i++) {
    if (old_buckets[i] != NULL)
      insertMap(map,old_buckets[i]->key,old_buckets[i]->value);
  }

  free(old_buckets);
  
  return;
}

HashMap *createMap(long capacity) {
  // Reserva memoria para cada dato de esta struct
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL) return NULL;
  
  map->capacity = capacity;
  map->current = -1;

  //reservar memoria para los buckets
  //se hace con calloc para que se inicien en NULL
  map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
  if (map->buckets == NULL) {
    free(map);
    return NULL;
  }

  map->size = 0;

  return map;
}

void eraseMap(HashMap * map,  char * key) {
  
  if (map == NULL || key == NULL) return;

  int pos = hash(key, map->capacity);
  int originalPos = pos;

  while (map->buckets[pos] != NULL) {
    if (strcmp(map->buckets[pos]->key, key) == 0){
      map->buckets[pos]->key = NULL;
      map->size--;
    }
    pos = (pos + 1) % map->capacity;

    if (pos == originalPos) return;
  }

  return;
}

Pair * searchMap(HashMap * map,  char * key) { 
  
  if (map == NULL || key == NULL) return NULL;
  
  //posicion en la que debe estar el 
  int pos = hash(key, map->capacity);
  int originalPos = pos;

  
  while (map->buckets[pos] != NULL) {
    if (strcmp(map->buckets[pos]->key, key) == 0){
      map->current = pos;
      return map->buckets[pos];
    }
    pos = (pos + 1) % map->capacity;
    
    if (pos == originalPos) return NULL;
  }

  return NULL;
}

Pair * firstMap(HashMap * map) {
  
  if (map == NULL) return NULL;
  
  for(int i = 0; i < map->capacity; i++) {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }
  
  return NULL;
}

Pair * nextMap(HashMap * map) {

  if (map == NULL) return NULL;

  for (int i = (map->current + 1); i < map->capacity; i++) {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }

    
  return NULL;
}
