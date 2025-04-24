#include "wagon.h"
#ifndef TRAIN_H
#define TRAIN_H

typedef struct Train{          //train structure
    char train_id[20];
    struct Wagon* first_wagon;
    int wagon_count;
}Train;

Train* create_train();     //this code for create a new train
void delete_train(Train* train);         //first, delete wagons inside the train, then deletes the train
void display_train(struct Train* train); //print the information about the train
void empty_train(struct Train* train);   //don't delete the train, just empties all the materials and wagons in the train

#endif