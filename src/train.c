#include "train.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Train* create_train(){
    Train* train = malloc(sizeof(Train));
    if(train == NULL){
        return NULL;
    }

    strcpy(train->train_id, "TR123");   //sadece tek tren oluşturulacağı için sabit bir id verdik, birden fazla tren olsaydı kullanıcıdan isteyecektik
    train->first_wagon = NULL;    //içi boş bir tren (sadece lokomotif)
    train->wagon_count = 0;   

    //printf("created train\n");
    return train;
}

/*void delete_train(struct Train* train){
    Wagon* current_wagon = train->first_wagon;
    while(current_wagon != NULL){
        current_wagon = current_wagon->next;
        free(current_wagon->prev);
    }

    free(train);
}
Bu haliyle yanlış oldu!!!
*/


/*Bellek sızıntısı olmaması için sadece free(train) diyemez.
  Çünkü train'in bellekteki yeri silinir ancak wagonların yeri 
  kalmaya devam eder.*/
void delete_train(struct Train* train){
    if(train == NULL){
        printf("Train is also NULL!!.");
    }else{
        Wagon* current_wagon = train->first_wagon;
        while(current_wagon != NULL){    //sırasıyla wagonları gezer ve siler.
            LoadedMaterial* current_material = current_wagon->loaded_materials;
            while(current_material != NULL){   //wagonlardaki bütün gezer ve materyalleri siler.
                LoadedMaterial* deleted_material = current_material;
                current_material = current_material->next;
                free(deleted_material);
            }
            Wagon* deleted_wagon = current_wagon;
            current_wagon = current_wagon->next;
            free(deleted_wagon);
        }
    }

    free(train);  //en son tren boşaldıktan sonra treni siler.
    //printf("Train is deleted.\n");
}

void display_train(struct Train* train){
    printf("TRAIN: %s : %d\n",train->train_id, train->wagon_count);   //prints train's id and wagon count
 //   display_material_status(train);
    Wagon* wagon_order = train->first_wagon;
    while (wagon_order != NULL){   //checks every wagon
        printf("WAGON: %d: 1000.0: %.2f\n", wagon_order->wagon_id, wagon_order->current_weight);  //prints wagon's id, max weight and current weight 
                
        LoadedMaterial* loaded_mat = wagon_order->loaded_materials;
        while(loaded_mat != NULL){  //checks every material in current wagon
            Material* mat = loaded_mat->type;
            printf("Materyal: %s\n",mat->name);  //prints material's name
            loaded_mat = loaded_mat->next;
        }
        wagon_order = wagon_order->next;
        printf("--------------------------\n");  //prints it between two wagons
    }
}


void empty_train(struct Train* train){
    if(train->first_wagon == NULL){  //if train is already empty
        printf("Train is also empty!!.\n");
    }else{
        Wagon* current_wagon = train->first_wagon;
        while(current_wagon != NULL){    //sırasıyla wagonları gezer ve siler.
            LoadedMaterial* current_material = current_wagon->loaded_materials;
            while(current_material != NULL){   //wagonlardaki bütün materyalleri gezer ve siler.
                LoadedMaterial* deleted_material = current_material;
                current_material = current_material->next;
                free(deleted_material);
            }
            Wagon* deleted_wagon = current_wagon;
            current_wagon = current_wagon->next;
            free(deleted_wagon);
        }
        train->first_wagon = NULL;  //eğer null yapılmazsa saçma değerler döndürür.
        train->wagon_count = 0;     //wagon sayısı güncellenir (tren tamamen boşaltıldığı için 0)
        printf("Train has been emptied successfully.\n");
    }
}