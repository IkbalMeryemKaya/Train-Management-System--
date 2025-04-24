#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wagon.h"

Material* create_material(int material_type, int loaded){
    Material* material = malloc (sizeof(Material));
    if(material == NULL){  //malloc kontrol edilir.
        printf("Failed to allocate memory for Material.\n");
        return NULL;
    }

    //istenen materyalin ne olacağını kontrol eder ve ona göre materyal oluşturur.
    if(material_type == 1){  //1) Large Box
        strcpy(material->name, "Large Box");
        strcpy(material->type, "Steel");
        material->weight = 200.0;
    }if(material_type == 2){  //2) Medium Box
        strcpy(material->name, "Medium Box");
        strcpy(material->type, "Aluminium");
        material->weight = 150.0;
    }if(material_type == 3){  //3) Small Box
        strcpy(material->name, "Small Box");
        strcpy(material->type, "Wood");
        material->weight = 100.0;
    }
    material->loaded = loaded;  //bu her ne seçilirse seçilsin aynı kalacağı için if else dışında yazıldı (kaç adet materyal yüklenecek veya indirilecek)

    //printf("created material\n");
    return material;

}

/*void add_material(struct Train* train, Material* material){
    for(int i = 0; i < material->quantity; i++){    
        printf("Material:%d\n", i+1);
        LoadedMaterial* new_material = malloc(sizeof(LoadedMaterial));
        if (new_material == NULL) {
            printf("Failed to allocate memory for LoadedMaterial.\n");
            return;
        }

        new_material->type = material;
        new_material->next = NULL;
        new_material->prev = NULL;

        Wagon* the_wagon = train->first_wagon;
        if(the_wagon == NULL){
            Wagon* new_wagon = create_wagon(train->wagon_count+1, 1000);
            add_wagon(train, new_wagon);
            printf("Yeni vagon oluşturuldu ve eklendi\n");
            new_wagon->loaded_materials = new_material;
            new_wagon->current_weight = material->weight;
            printf("Material:%d yeni vagona eklendi.\n", i+1);
            the_wagon = new_wagon;
        }else{
            if(material->weight <= the_wagon->max_weight - the_wagon->current_weight){
                if(the_wagon->loaded_materials == NULL){
                    the_wagon->loaded_materials = new_material;
                    printf("Material:%d, %d.vagona eklendi.\n", i+1, the_wagon->wagon_id);
                }else{
                    LoadedMaterial* temp = the_wagon->loaded_materials;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = new_material;
                    new_material->prev = temp;
                    printf("Material:%d, %d.vagona eklendi(2).\n", i+1, the_wagon->wagon_id);
                }

                the_wagon->current_weight += material->weight;
            }else{
                the_wagon = the_wagon->next;
            }
        }
    }
}*/

/*void add_material(struct Train* train, Material* material) {
    for (int i = 0; i < material->quantity; i++) {
        // Her materyal için yeni bir LoadedMaterial oluştur
        LoadedMaterial* new_material = malloc(sizeof(LoadedMaterial));
        if (new_material == NULL) {
            printf("Failed to allocate memory for LoadedMaterial.\n");
            return;
        }

        new_material->type = material;
        new_material->next = NULL;
        new_material->prev = NULL;

        Wagon* the_wagon = train->first_wagon;
        while (the_wagon != NULL) {
            if (material->weight <= the_wagon->max_weight - the_wagon->current_weight) {
                // Eğer vagon uygun ağırlıktaysa materyali buraya ekle
                if (the_wagon->loaded_materials == NULL) {
                    the_wagon->loaded_materials = new_material;
                } else {
                    LoadedMaterial* temp = the_wagon->loaded_materials;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = new_material;
                    new_material->prev = temp;
                }

                // Mevcut ağırlığı güncelle
                the_wagon->current_weight += material->weight;
                printf("Materyal %d. vagona eklendi.\n", the_wagon->wagon_id);
                break;
            } else {
                // Bir sonraki vagona geç
                the_wagon = the_wagon->next;
            }
        }

        // Eğer uygun vagon bulunamazsa yeni vagon oluştur
        if (the_wagon == NULL) {
            Wagon* new_wagon = create_wagon(train->wagon_count + 1, 1000);
            add_wagon(train, new_wagon);
            new_wagon->loaded_materials = new_material;
            new_wagon->current_weight += material->weight;
            printf("Yeni vagon oluşturuldu ve materyal buraya eklendi: Wagon ID %d\n", new_wagon->wagon_id);
        }
    }
}*/

void add_material(struct Train* train, Material* material) {
    for (int i = 0; i < material->loaded; i++) {  //eklenecek her materyal için bir döngü
        //printf("Material:%d (%s)\n", i + 1, material->name);//materyal bilgileri

        LoadedMaterial* new_material = malloc(sizeof(LoadedMaterial));  //memory de yer ayırtılır
        if (new_material == NULL) {  //malloc kontrol edilir.
            printf("Failed to allocate memory for LoadedMaterial.\n");
            return;
        }

        new_material->type = material;  //eklenecek materyalin tipi istenen materyali işaret eder.
        new_material->next = NULL;
        new_material->prev = NULL;

        //eğer trende hiç vagon yoksa yeni bir vagon oluştur ve ekle
        if (train->first_wagon == NULL) {
            Wagon* new_wagon = create_wagon(1); //id'si 1 olan yeni vagon oluştur
            add_wagon(train, new_wagon);  //wagon trene eklenir
            //printf("Trende hiç vagon yoktu, yeni vagon oluşturuldu ve eklendi (id: %d)\n", new_wagon->wagon_id);
            new_wagon->loaded_materials = new_material;  //wagondaki ilk materyal, eklenecek olan materyali gösterir (böylece materyal eklenmiş olur)
            new_wagon->current_weight += material->weight;  //wagonun current_weight materyalin ağırlığına göre güncellenir
            //printf("Materyal yeni vagona eklendi.\n");
            continue; //döngünün sonraki materyale geçmesi için
        }

        //eğer trende zaten wagonlar varsa
        Wagon* the_wagon = train->first_wagon;
        bool is_added = false; //materyal eklendiğinde true olacak!!

        //mevcut vagonlar arasında uygun yer bul
        while (the_wagon != NULL) { //ilk wagondan başlar, yüklenene kadar veya wagonlar bitene kadar her wagonu kontrol eder
            //printf("Checking wagon %d - current weight: %.2f, max weight: 1000.0\n", the_wagon->wagon_id, the_wagon->current_weight);

            if (the_wagon->current_weight + material->weight <= 1000) {  //wagonda ağırlık olarak yer olup olmadığını kontrol eder
                if (the_wagon->loaded_materials == NULL) {  //wagona hiç materyal yüklenmemişse
                    the_wagon->loaded_materials = new_material;  //ilk materyal olarak yükler
                    the_wagon->current_weight += new_material->type->weight; //wagonun ağırlığını günceller
                    is_added = true;  //eklendiği için true olur
                    //printf("Materyal ilk olarak eklendi.\n");
                    break;  //eklendiği için diğer wagonalrı kontrol etmesine gerek yok, while döngüsünü bitirir
                } else {  //wagonda daha önce materyal varsa
                    LoadedMaterial* temp = the_wagon->loaded_materials;  
                    while(temp->next != NULL){     //wagondaki materyallerin en sonuncusuna git
                        temp = temp->next;
                    }

                    if(new_material->type->weight <= temp->type->weight){   //eğer eklenecek materyalin ağırlığı, son materyalin ağırlığından küçük veya eşit ise
                        temp->next = new_material;  //son materyalden sonrasına yeni materyali yükler
                        new_material->prev = temp;  //yeni yüklenen materyalin prev güncellenir
                        the_wagon->current_weight += material->weight;   //wagonun ağırlığı güncellendi
                        //printf("Materyal %d. vagona eklendi.\n", the_wagon->wagon_id);
                        is_added = true;  //eklendiği için true oldu.
                        break; //başarıyla eklendi, döngüyü kır

                    }

                }

            }

            the_wagon = the_wagon->next;  //eğer break gelmezse (yüklenemezse) sıradaki wagona geçer ve onu kontrol eder.
        }

        //eğer hiçbir vagon uygun değilse yeni bir vagon oluşturur.
        if (!is_added) {  //bütün wagonlar bitmesine rağmen materyal yüklenmediyse
            Wagon* new_wagon = create_wagon(train->wagon_count + 1);
            add_wagon(train, new_wagon);
            //printf("Yeni vagon oluşturuldu ve eklendi (id: %d)\n", new_wagon->wagon_id);

            new_wagon->loaded_materials = new_material;  //yeni wagona ilk materyal olarak yüklenir
            new_wagon->current_weight = material->weight;  //wagonun ağırlığıda güncellenir.
            //printf("Materyal yeni vagona eklendi.\n");
        }
    }
}


void add_material_in_wagon(struct Train* train, int wagon_id, Material* material){
    Wagon* wagon = train->first_wagon;
    while(wagon->wagon_id != wagon_id){  //id'si girilen wagonu bulur çünkü ondan başlanacak
        wagon = wagon->next;
    }
    
    for (int i = 0; i < material->loaded; i++) {    //eklenecek her materyal için bir döngü
        //printf("Material:%d (%s)\n", i + 1, material->name);

        LoadedMaterial* new_material = malloc(sizeof(LoadedMaterial));  //bellekte yer ayırıldı
        if (new_material == NULL) {  //malloc kontrol edilir.
            printf("Failed to allocate memory for LoadedMaterial.\n");
            return;
        }

        new_material->type = material;   //eklenecek materyalin tipi istenen materyali işaret eder.
        new_material->next = NULL;
        new_material->prev = NULL;

        bool is_added = false;

        //Mevcut vagonda uygun yer var mı diye kontrol edilir
        while (wagon != NULL) {   //ilk wagondan başlar, yüklenene kadar veya wagonlar bitene kadar her wagonu kontrol eder
            //printf("Checking wagon %d - current weight: %.2f, max weight: %.2f\n", wagon->wagon_id, wagon->current_weight, wagon->max_weight); 

            if (material->weight <= wagon->max_weight - wagon->current_weight) {   //wagonda ağırlık olarak yer var mı? 
                if (wagon->loaded_materials == NULL) {   //wagonda hiç materyal yoksa
                    //printf("Added as first material!!\n");
                    wagon->loaded_materials = new_material;  //wagona ilk materyal olarak yüklenir
                    wagon->current_weight += material->weight;  //wagan ağırlığı güncellenir
                    is_added = true;  //eklendiği için true olur
                } else {  //wagonda başka materyaller varsa 
                    LoadedMaterial* temp = wagon->loaded_materials;
                    while(temp->next != NULL){     //wagondaki materyallerin en sonuncusuna git
                        temp = temp->next;
                    }

                    if(new_material->type->weight <= temp->type->weight){  //eğer eklenecek materyalin ağırlığı, son materyalin ağırlığından küçük veya eşit ise
                        //printf("Agirlik takibi basarili: EKLENEBILIR\n");
                        temp->next = new_material;  //wagondaki materyallerin en sonuna eklenir
                        new_material->prev = temp;  //eklenen materyalin next ve prev güncellemesi

                        wagon->current_weight += material->weight;  //eklenen kadar ağırlık wagona eklenir
                        //printf("Materyal %d.vagona eklendi.\n", wagon->wagon_id);
                        is_added = true;  //eklendiği için true olur
                        break; // Başarıyla eklenirse döngüyü kır
                    }
                    
                }

            }

            wagon = wagon->next;   //eğer break gelmezse (yüklenemezse) sıradaki wagona geçer ve onu kontrol eder. 
        }

        // Eğer vagon uygun değilse yeni bir vagon oluşturur
        if (!is_added) {  //materyal hala yüklenmediyse
            Wagon* new_wagon = create_wagon(train->wagon_count + 1); 
            add_wagon(train, new_wagon);
            wagon = new_wagon;   //bunu eklemediğimde 5'den sonraki her materyal için yeni wagon oluşturuyor.
            //printf("Yeni vagon oluşturuldu ve eklendi (id: %d)\n", new_wagon->wagon_id);

            new_wagon->loaded_materials = new_material;   //yeni wagona ilk materyal olarak yüklenir
            new_wagon->current_weight = material->weight;  //eşit olur çünkü ilk materyal, başka materyal yok
            //printf("Materyal yeni vagona eklendi.\n");
        }
    }
}

void display_material_status(struct Train* train){
    int large_count=0, medium_count=0, small_count=0;  //trende kaç tane materyal olduğunu sayacaklar, ilk başta hepsi sıfır
    Wagon* wagon = train->first_wagon;

    while(wagon != NULL){    //ilk wagondan başlar, en son wagona kadar bakar
        LoadedMaterial* ld_materyal = wagon->loaded_materials;
        while(ld_materyal != NULL){  //wagondaki materyallerin tipini tek tek kontrol eder ve sayar
            if(strcmp(ld_materyal->type->name,"Large Box") == 0){
                large_count++;
            }if(strcmp(ld_materyal->type->name,"Medium Box") == 0){
                medium_count++;
            }if(strcmp(ld_materyal->type->name,"Small Box") == 0){
                small_count++;
            }
            ld_materyal = ld_materyal->next; //sıradaki materyale geçer
        }
        wagon = wagon->next;  //sıradaki wagona geçer
    }

    //hangi materyalden kaç tane olduğunu yazdırır.
    printf("Large Box: Steel: 200.0: %d\n", large_count);
    printf("Medium Box: Aluminium: 150.0: %d\n", medium_count);
    printf("Small Box: Wood: 100.0: %d\n\n", small_count);
}

// Function to remove a material from the list by name
/*void remove_material(Material* material, int size, char* name){
    for(int i = 0; i< size; i++){
        if (strcmp(material[i].name, name) == 0){  // Compare the current material's name with the given name
            for(int j = i; j< size-1; j++){      // If a match is found, start shifting elements to the left
                material[j] = material[j+1];     // Copy the next element to the current position
            }

            size--;
            material = realloc(material, size * sizeof(Material));
            printf("Material %s removed successfully \n", name);
            return;

        } 

    } 
    printf("Material %s not found.\n", name);
}*/

void remove_material(struct Train* train, struct Material* material){
    bool is_found = false;  //indirilecek materyal bulunursa true olacak 
    int finding_number = 0;  //kaç materyalin bulunup indirildiğini sayar
    Wagon* wagon = train->first_wagon;

    while(wagon != NULL){   //girilen wagondan başlayarak wagonları dolaşır
        //printf("Wagonlar araniyor...: Wagon %d\n", wagon->wagon_id);
        LoadedMaterial* current_material = wagon->loaded_materials;

        while(current_material != NULL){   //mevcut wagondaki materyalleri dolaşır
            //printf("Materyaller araniyor...\n");

            if(strcmp(current_material->type->name, material->name) == 0 &&    //yüklü materyallerin isimler (ex. Large Box)
            strcmp(current_material->type->type, material->type) == 0 &&       //tipleri (ex. Wood)
            current_material->type->weight == material->weight){               //ve ağırlıkları (ex. 150.0) aynı ise devam eder.

                //printf("Material found in wagon %d!\n", wagon->wagon_id);
                is_found = true;  //istenen materyal bulunduğu için true olur
                finding_number++;
                LoadedMaterial* deleted_material = current_material;  //bulunan materyal silinmek için ayrı bir değişkene atanır
                //silmeden önce current_material ile işlem yapacağımız için başka değişkene veriyoruz, yapmazsak başka bir materyali silebilir
                
                if(current_material->prev == NULL){   //eğer wagondaki ilk materyal ise
                //printf("ilk materyal\n");
                    wagon->loaded_materials = current_material->next;  //ikinci materyal, ilk olarak güncellenir
                    if(current_material->next != NULL){    //eğer ikinci boş değilse (current_material->next->prev  boşsa burada next->prev kısmı error verir)
                        current_material->next->prev = NULL;   //yeni ilk materyalin (eski ikinci olan) öncesini NULL yap
                    }
                }else if(current_material->next == NULL){   //eğer wagondaki son materyal ise
                    //printf("son materyal\n");
                    current_material->prev->next = NULL;    //yeni son materyalin (mevcut son materyalin önceki) sonrasını NULL yap
                }else{    //eğer wagondaki ilk veya son materyal değil ise 
                    //printf("ortada materyal\n");
                    current_material->prev->next = current_material->next;  //silinecek materyalin öncesi ve sonrası arada materyal yokmuş gibi bağlanır (materyal kaldırılmış olur)
                    current_material->next->prev = current_material->prev;
                }

                wagon->current_weight -= current_material->type->weight;  //toplam ağırlıktan çıkarılan ağırlık çıkarılır.
                current_material = current_material->next;  //sıradaki materyale geçer
                //printf("Material deleted: %s\n", deleted_material->type->name);
                free(deleted_material);  //kaldırılan materyal free ile hafızadan silinir.

                if(finding_number == material->loaded){   //eğer istenen sayıda ve isimde materyal bulunduysa
                    printf("The requested number of materials has been removed!!\n");
                    if(wagon->current_weight == 0.0){   //wagon boşaldıysa (içinde hiç materyal kalmadıysa)
                        //printf("wagon siliyor!!\n");
                        Wagon* next_wagon = wagon->next;
                        delete_wagon(train, wagon);  //wagon silinir
                        wagon = wagon->next;  
                        return;
                    }
                    return; //istenilen sayıda materyal çıkarıldığı için kod durur.
                }
            }else{  //materyalin, indirilmek istenen materyal ile aynı özellikleri yoksa 
                current_material = current_material->next;  //sıradaki materyale geçilir.
            }
        }   
                
        //mavcut wagonda istenen sayıda materyal bulunamazsa yine de wagonlar boş mu diye kontrol edilir.
        if(wagon->current_weight == 0.0){   //wagon boşaldıysa (içinde hiç materyal kalmadıysa)
            //printf("wagon siliyor!!\n");
            Wagon* next_wagon = wagon->next;
            delete_wagon(train, wagon);  //wagon silinir
            wagon = next_wagon;
        }else{  //eğer boş değilse sıradaki wagona geçer
            wagon = wagon->next;
        }

    }

    if(!is_found){  //istenen materyal hiç bulunamadıysa
        printf("Material '%s' was not found in any wagon of train '%s'.\n", material->name, train->train_id);
    }if(finding_number < material->loaded){  //istenen sayıdan az bulunduysa
        printf("There are not enough materials!! %d materials were removed.\n", finding_number);
    }
    
}



void remove_material_in_wagon(struct Train* train, int wagon_id, struct Material* material){
    bool is_found = false;
    int finding_number = 0;

    Wagon* wagon = train->first_wagon;  //baştan başlar, istenen wagona ulaşınca durur
    while(wagon->wagon_id != wagon_id){
        wagon = wagon->next;
    }

    while(wagon != NULL){                  //girilen wagondan başlayarak wagonları dolaşır
        //printf("Wagonlar araniyor...: Wagon %d\n", wagon->wagon_id);
        LoadedMaterial* current_material = wagon->loaded_materials;

        while(current_material != NULL){      //bir wagondaki materyalleri dolaşır
            //printf("Materyaller araniyor...\n");

            if(strcmp(current_material->type->name, material->name) == 0 &&    //yüklü materyallerin isimler (ex. Large Box)
            strcmp(current_material->type->type, material->type) == 0 &&       //tipleri (ex. Wood)
            current_material->type->weight == material->weight){               //ve ağırlıkları (ex. 150.0) aynı ise devam eder.

                //printf("Material found in wagon %d!\n", wagon->wagon_id);
                is_found = true;
                finding_number++;
                LoadedMaterial* deleted_material = current_material;
                
                if(current_material->prev == NULL){   //eğer wagondaki ilk materyal ise
                //printf("ilk materyal\n");
                    wagon->loaded_materials = current_material->next;  //ikinci materyal ilk olarak güncellenir
                    if(current_material->next != NULL){    //eğer ikinci boş değilse (current_material->next->prev  burada next->prev kısmı error verir)
                        current_material->next->prev = NULL;   //yeni ilk materyalin öncesini NULL yap
                    }
                }else if(current_material->next == NULL){   //eğer wagondaki son materyal ise
                    //printf("son materyal\n");
                    current_material->prev->next = NULL;    //yeni son materyalin (mevcut son materyalin önceki) sonrasını NULL yap
                }else{    //eğer wagondaki ilk veya son materyal değil ise 
                    //printf("ortada materyal\n");
                    current_material->prev->next = current_material->next;
                    current_material->next->prev = current_material->prev;
                }

                wagon->current_weight -= current_material->type->weight;  //toplam ağırlıktan çıkarılan ağırlık çıkarılır.
                current_material = current_material->next;  
                //printf("Material deleted: %s\n", deleted_material->type->name);
                free(deleted_material);

                if(finding_number == material->loaded){   //eğer istenen sayıda ve isimdemateryal bulunduysa
                    printf("The requested number of materials has been removed!!\n");
                    if(wagon->current_weight == 0.0){   //wagon boşaldıysa (içinde hiç materyal kalmadıysa)
                        //printf("wagon siliyor!!\n");
                        Wagon* next_wagon = wagon->next;
                        delete_wagon(train, wagon);
                        wagon = wagon->next;
                        return;
                    }
                    return;
                }
            }else{
                current_material = current_material->next;
            }
        }
                
        if(wagon->current_weight == 0.0){   //wagon boşaldıysa (içinde hiç materyal kalmadıysa)
            //printf("wagon siliyor!!\n");
            Wagon* next_wagon = wagon->next;
            delete_wagon(train, wagon);
            wagon = next_wagon;
        }else{
            wagon = wagon->next;
        }

    }

    if(!is_found){  //istenen materyal hiç bulunamadıysa
        printf("Material '%s' was not found in any wagon of train '%s'.\n", material->name, train->train_id);
    }if(finding_number < material->loaded){  //istenen sayıdan az bulunduysa
        printf("There are not enough materials!! %d materials were removed.\n", finding_number);
    }
}