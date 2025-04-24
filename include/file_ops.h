#ifndef FILE_OPS_H
#define FILE_OPS_H
#include "train.h"

void save_file(struct Train* train, char* file_name);  //girilen file ismine (yoksa yenisi oluşturulur) tren durumu kaydedilir
void load_file(struct Train* train, char* file_name);  //girilen file isminde (yoksa error mesajı verir) kayıtlı olan şekilde tren yüklenir

#endif