#ifndef MATERIAL_H
#define MATERIAL_H
#include "wagon.h"
#include "train.h"

typedef struct Material{    
    char name[50];
    char type[20];
    float weight;
    int loaded;
}Material;

typedef struct LoadedMaterial {
    Material* type;   // Type of box
    struct LoadedMaterial *next, *prev;
} LoadedMaterial;

Material* create_material(int material_type, int loaded);  //create new material depending to material type
void add_material(struct Train* train, Material* material);   //vagonları en baştan kontrol eder. Ona göre materyalleri yerleştirir.
void add_material_in_wagon(struct Train* train, int wagon_id, Material* material);  //spesifik wagonda başlayarak materyal yükler.
void display_material_status();   //print the current loaded material status
//void remove_material(Material* material, int size, char* name);
void remove_material(struct Train* train, struct Material* material);  //ilk wagondan başlayarak boşaltılacak materyal arar, bulursa boşaltır
void remove_material_in_wagon(struct Train* train, int wagon_id, struct Material* material);  //spesifik wagondan başlayarak materyal boşaltır

#endif