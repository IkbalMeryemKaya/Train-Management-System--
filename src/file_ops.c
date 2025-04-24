#include "file_ops.h"
#include "train.h"
#include <stdio.h>
#include <string.h>

void save_file(struct Train* train, char* file_name){
    FILE* file = fopen(file_name, "w");   //girilen isimde file oluşturuldu (w: yazma)
    //printf("File is created!! :) \n");
    if(file == NULL){    //fileın oluşturulup oluşturulmadığı kontrol edilir
        printf("File could not be open!!");
        return;
    }

    fprintf(file, "TRAIN: %s : %d\n\n", train->train_id, train->wagon_count); //train bilgileri (train: train_id: wagon_count)
    //printf("Train infos printed!! :) \n");

    Wagon* wagon_order = train->first_wagon;
    while (wagon_order != NULL){  //bütün wagonaları gezip bilgilerini yazdırır.
        //printf("Inside wagon while loop\n");
        fprintf(file, "WAGON: %d: 1000.0: %.2f\n", wagon_order->wagon_id, wagon_order->current_weight);
        fflush(file);

        LoadedMaterial* loaded_mat = wagon_order->loaded_materials;
        while(loaded_mat != NULL){  //her wagondaki materyalleri gezip bilgi
            //printf("Inside material while loop\n");
            Material* mat = loaded_mat->type;
            fprintf(file, "Materyal: %s\n",mat->name);
            fflush(file);
            loaded_mat = loaded_mat->next;  //sonraki materyale geçer
        }
        wagon_order = wagon_order->next;
        fprintf(file, "--------------------------\n");  //her wagon bitişinde bunu yazdırır.
    }

    fclose(file);  //dosya kapatılır.
    printf("Train status saved successfully!!\n");
}


/*void load_file(struct Train* train, char* file_name){
    FILE* file = fopen(file_name, "r");   //girilen isimde file oluşturuldu
    printf("File is created!! :) \n");
    if(file == NULL){    //fileın oluşturulup oluşturulmadığı kontrol edilir
        printf("File could not be open!!");
        return;
    }

    int wagon_id;
    float current_weight;
    char train_id[20];
    int wagon_count;

    printf("Reading from file: %s\n", file_name);
    char buffer[200];
    if(fscanf(file, "TRAIN: %s: %d\n", train_id, &wagon_count) != 2){
        printf("train infos is wrong\n");

    }
    strcpy(train->train_id, train_id);
    train->wagon_count = wagon_count;
    printf("Train infos printed!! :) \n");

    while(fscanf(file, "WAGON: %d: 1000.0: %f\n", &wagon_id, &current_weight) == 2){
        printf("wagon added\n");
        Wagon* wagon = create_wagon(wagon_id);
      //  wagon->current_weight = current_weight;
        add_wagon(train, wagon);
        printf("Wagon: %d: %.2f\n", wagon_id, current_weight);

        if(fscanf(file, "Materyal: Small Box\n") == 1){
            Material* material = create_material(3, 1);
            add_material_in_wagon(train, wagon->wagon_id, material);
            printf("Small box added\n");

        }
        if(fscanf(file, "Materyal: Medium Box\n") == 1){
            Material* material = create_material(2, 1);
            add_material_in_wagon(train, wagon->wagon_id, material);
            printf("Medium box added\n");
        }
        if(fscanf(file, "Materyal: Large Box\n") == 1){
            Material* material = create_material(1, 1);
            add_material_in_wagon(train, wagon->wagon_id, material);
            printf("Large box added\n");
        }

        fscanf(file, "--------------------------\n");
        fscanf(file, "\n");
    }

    fclose(file);
    printf("load_file is worked\n");
    
}*/

void load_file(struct Train* train, char* file_name) {
    FILE* file = fopen(file_name, "r");  // Dosya açma (r: okuma)
    if (file == NULL) {  // Dosya açılamazsa hata mesajı
        printf("File could not be opened!!\n");
        return;
    }

    empty_train(train);  //eğer oluşturulmuş bir tren varsa onu boşaltır, sonra kayıtlı olanı yükler.
    int wagon_id;
    float current_weight;

    char train_id[20];
    int wagon_count;

    //printf("Reading from file: %s\n", file_name);
    if (fscanf(file, "TRAIN: %s : %d\n", train_id, &wagon_count) != 2) {  //ilk satırda tren bilgileri yazar, eğer iki değer okumazsa hata mesajı verir.
        //printf("%s  :  %d", train_id, wagon_count);
        printf("Train info is wrong\n");
        fclose(file);  //hata olursa dosyayı kapatır 
        return;        //ve metodu durdurur.
    }

    //okunan bilgiler ile 'train' yapısını oluştur
    strcpy(train->train_id, train_id);
    //add_wagon içerisinde wagon_count güncellendiği için burda biz bu işlemi yapmıyoruz!!
    //printf("Train ID: %s, Wagon Count: %d\n", train->train_id, train->wagon_count);

    while (fscanf(file, "WAGON: %d: 1000.0: %f\n", &wagon_id, &current_weight) == 2) {  //wagon satırlarında wagon_id ve current_weight okunursa
        //printf("Wagon added: %d with weight %.2f\n", wagon_id, current_weight);
        
        Wagon* wagon = create_wagon(wagon_id); //okunan bilgilerle yeni wagon oluşturulur ve trene eklenir
        add_wagon(train, wagon);

        // Materyalleri okuma
        char material_type[50];
        Material* material = NULL;
        while (fscanf(file, "Materyal: %s Box\n", material_type) == 1) {  //materyal satırları okunur ve türüne göre materyal oluşturulur.
            if (strcmp(material_type, "Small") == 0) {
                material = create_material(3, 1);
            } else if (strcmp(material_type, "Medium") == 0) {
                material = create_material(2, 1);
            } else if (strcmp(material_type, "Large") == 0) {
                material = create_material(1, 1);
            }
            if (material != NULL) {  //materyal oluşturulduysa wagona ekle
                add_material_in_wagon(train, wagon_id, material);
                //printf("%s box added\n", material->name);
            }
        }

        fscanf(file, "--------------------------\n"); //çizgileri atla (hiçbir şey yapmaz)
    }

    fclose(file);  //dosya kapatılır.
    printf("Train status updated successfully!!\n");
}
