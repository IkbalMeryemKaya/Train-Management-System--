#ifndef VAGON_H
#define VAGON_H
#include "material.h"
#include "train.h"

typedef struct Wagon{
    int wagon_id;        
    float max_weight;
    float current_weight;
    LoadedMaterial* loaded_materials;
    struct Wagon *next, *prev;
} Wagon;

Wagon* create_wagon(int wagon_id);   //create new wagon
void add_wagon(struct Train* train, struct Wagon* new_wagon);   //add new wagon in the given train
void delete_wagon(struct Train* train, struct Wagon* wagon);   //deletes the written wagon from the train


#endif