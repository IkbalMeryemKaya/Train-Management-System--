#ifndef UTILS_H
#define UTILS_H
#include "train.h"

char* to_upper(char* string);     //this make uppercase to word or sentences 
int wagon_not_found(struct Train* tr, int wagon_id);    //If the requested wagon cannot be found
int material_not_found(int material_type);    //If the requested mateerial type cannot be found

#endif