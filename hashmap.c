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


int solveCollisions(HashMap * map, char * key, void * value){
  
}

////
void insertMap(HashMap * map, char * key, void * value) {
  int position = hash(key,map->capacity);
  
  if ((map->buckets[position] == NULL) || (is_equal(map->buckets[position]->key, NULL))){
    map->buckets[position] = createPair(key, value);
    
    strcpy(map->buckets[position]->key,key);
    map->buckets[position]->value = value;
    map->size++;
    map->current = position;
  }

}

void enlarge(HashMap * map) {
  //enlarge_called = 1; //no borrar (testing purposes)
  Pair** old_buckets = map->buckets;
  int old_buckets_capacity = map->capacity;
  
  map->capacity *= 2;
  map->buckets = (Pair**) malloc(sizeof(Pair*) * map->capacity);
  map->size = 0;
  
  int index = 0;
  while(index < old_buckets_capacity){
    if(old_buckets[index] != NULL){
      insertMap(map, old_buckets[index]->key, old_buckets[index]->value);
    }
    
    index++;
  }
  free(old_buckets);
}


HashMap * createMap(long capacity) {

  HashMap* map = (HashMap *) malloc(sizeof(HashMap));
  if (map == NULL) return NULL;
  
  map->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);
  if (map->buckets == NULL){
    free(map);
    return NULL;
  }
  
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
  
  return map;
}

void eraseMap(HashMap * map,  char * key) {    
  if (map == NULL || map->buckets == NULL) return;

  Pair* pair = searchMap(map,key);
  if (pair != NULL){
    pair->key = NULL;
    map->size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  int position = hash(key,map->capacity);

  if (is_equal(map->buckets[position]->key,key)){
    map->current = position;
    return map->buckets[position];
  }

    return NULL;
}

Pair * firstMap(HashMap * map) {
  
  for (int i = 0; i < map->capacity; i++){
    if ((map->buckets[i] != NULL) && (map->buckets[i]->key != NULL)){
      map->current = i;
      return map->buckets[i];
    }
  }
  map->current = -1;
  return NULL;
}

Pair * nextMap(HashMap * map) {

  long nextToCurrent = map->current + 1;
  for (int i = nextToCurrent; i < map->capacity; i++){
    if ((map->buckets[i] != NULL) && (map->buckets[i]->key != NULL)){
      map->current = i;
      return map->buckets[i];
    }
  }
    return NULL;
}
