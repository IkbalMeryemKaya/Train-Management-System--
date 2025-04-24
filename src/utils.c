#include "utils.h"
#include "train.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* to_upper(char* string) {
    // Yeni bir char dizisi oluştur
    char* result = (char*)malloc(strlen(string) + 1); //+1 null karakter için
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL; 
    }

    // Orijinal diziyi büyük harflere dönüştürerek kopyala
    for (int i = 0; i < strlen(string); i++) {
        result[i] = toupper(string[i]);
    }
    result[strlen(string)] = '\0'; //null karakter ekle

    return result;
}


int wagon_not_found(struct Train* tr, int wagon_id){
    if(wagon_id > tr->wagon_count){
        printf("No wagon found for this ID number. Please enter a valid number!!\n");
        return 0;
    }
    return 1;
}

int material_not_found(int material_type){
    if(material_type != 1 && material_type != 2 && material_type != 3){
        printf("No material found for this number. Please enter a valid number!!\n");
        return 0;
    }
    return 1;
}