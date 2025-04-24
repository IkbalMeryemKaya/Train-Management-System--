#include "wagon.h"
#include <stdio.h>
#include <stdlib.h>

Wagon* create_wagon(int wagon_id){  //sadece id ve max_weight için atama yapılır, diğerleri işlem yapıldıkça değişir.
    Wagon* wagon = malloc(sizeof(Wagon));
    if(wagon == NULL){  //malloc işlemi kontrol edilir.
        return NULL;
    }

    wagon->wagon_id = wagon_id;
    wagon->max_weight = 1000.00;
    wagon->current_weight = 0;
    wagon->loaded_materials = NULL;
    wagon->next = NULL;
    wagon->prev = NULL;

    //printf("created wagon\n");
    return wagon;
}

void add_wagon(struct Train* train, Wagon* new_wagon){
    if(train->first_wagon == NULL){   //tren boşsa ilk wagon olarak eklenir
        train->first_wagon = new_wagon;
        new_wagon->wagon_id = 1;
    }else{
        Wagon* lastwagon = train->first_wagon;
        while(lastwagon->next){    //trendeki son vagona git
            lastwagon = lastwagon->next;
        }
        lastwagon->next = new_wagon;  //son wagon ve eklenen wagonun next, prev ilişkisi kurulur. Böylece wagon eklenmiş olur.
        new_wagon->prev = lastwagon;
        new_wagon->wagon_id = lastwagon->wagon_id +1;  //id wagon oluşturulurken verilir ancak sıralamada hata olması ihtimaline karşın burada güncellenir.
    }

    train->wagon_count++;  //trenin wagon sayısı bir artırılır
}

void delete_wagon(struct Train* train, struct Wagon* wagon){
  /*  LoadedMaterial* current_mat = wagon->loaded_materials;
    while(current_mat != NULL){        //Wagonun içinde mateyaller hafızadan silindi.
        LoadedMaterial* free_materyal = current_mat;
        current_mat = current_mat->next;
        free(free_materyal);
    }
    
    üstteki kısım ilk denemede yazılmıştı ancak sonrasında sadece wagonun içinin boş olduğu durumlarda 
    wagon silme işlemi gerçekleşeceği için materyal silmek için olan bu kısmı kaldırdık.
    */

    Wagon* temp_wagon = wagon->next;
    while(temp_wagon != NULL){
        temp_wagon->wagon_id--;     //silinecek wagondan sonraki wagonun idsi bir eksik olacak şekilde güncellendi.
        temp_wagon = temp_wagon->next;   //sıradaki wagona geçilir ve son wagon kadar işlem tekrarlanır.
    }
    
    if(wagon == train->first_wagon){    //eğer trenin ilk wagonu ise
        train->first_wagon = wagon->next;   //ilk wagon ikinci wagonu gösterecek şekilde değiştirilir.
        if(train->first_wagon != NULL){  //eğer yeni ilk wagon son wagon değilse
            train->first_wagon->prev = NULL;  //ilk wagonun öncesi null olacak şekilde güncellenir.
        }
    }else{   //eğer trenin ilk wagonu değilse 
        if(wagon->prev != NULL){    //wagonun öncesi boş değilse
            wagon->prev->next = wagon->next;  //wagondan önceki wagonun next i wagondan sonrakini gösterir!!
        }if(wagon->next != NULL){   //wagonun sonrası boş değilse
            wagon->next->prev = wagon->prev;    //wagondan sonraki wagonun prev i wagondan öncekini gösterir!!
        }
    }

    train->wagon_count--;  //trenin wagon sayısı silinen wagon sayısına göre güncellenir.
    free(wagon);         //seçili wagon silinir

}
