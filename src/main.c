#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"
#include "material.h"
#include "utils.h"
#include "file_ops.h"
 
int main(){

    /*=== Train Loading Management System ===
1. Load train status from file 
2. Load material, starting from first suitable wagon from head of the Train
3. Load material to specific wagon
4. Unload material, starting from first suitable wagon from tail of the Train
5. Unload material from specific wagon 
6. Display train status
7. Display materials status
8. Empty train     
9. Save train status to file   
10. Exit
    */

  int transaction_number;

  Train* tr = create_train();

    printf("\n=== Train Loading Management System ===\n");   
    printf("1. Load train status from file\n");   
    printf("2. Load material, starting from first suitable wagon from head of the Train\n");   
    printf("3. Load material to specific wagon\n");   
    printf("4. Unload material, starting from first suitable wagon from tail of the Train\n");   
    printf("5. Unload material from specific wagon\n");   
    printf("6. Display train status\n");   
    printf("7. Display materials status\n");   
    printf("8. Empty train\n");                 
    printf("9. Save train status to file\n");      
    printf("10. Exit\n");

  while(1){
    printf("\nPlease write the number of the transaction you want to make: ");
    scanf("%d", &transaction_number);

    switch (transaction_number){
    case 1:
      char file_name1[30];
      printf("Please enter file name (must be .txt at the end): ");
      scanf("%29s", file_name1);
      load_file(tr, file_name1);
      break;

    case 2:
      int material_type_case2;
      int material_count_case2;

      while(1){
        printf("1) Large Box (Steel) : 200 kg\n");
        printf("2) Medium Bax (Aluminium) : 150 kg\n");
        printf("3) Small Box (Wood) : 100 kg\n");
        printf("\nSelect the material you want to add: ");
        scanf("%d", &material_type_case2);

        if(material_not_found(material_type_case2)){
          break;
        }
      }

      printf("How many items do you want to add from your chosen material: ");
      scanf("%d", &material_count_case2);

      Material* materyal_case2 = create_material(material_type_case2, material_count_case2);
      add_material(tr, materyal_case2);
      printf("%d %sS ADDED TO THE TRAIN!!\n", material_count_case2, to_upper(materyal_case2->name));

      break;

    case 3: 
      int material_type_case3;
      int material_count_case3;
      int wagon_id_case3;

      while(1){
        printf("1) Large Box (Steel) : 200 kg\n");
        printf("2) Medium Bax (Aluminium) : 150 kg\n");
        printf("3) Small Box (Wood) : 100 kg\n");
        printf("\nSelect the material you want to load: ");
        scanf("%d", &material_type_case3);

        if(material_not_found(material_type_case3)){
          break;
        }
      }

      printf("How many items do you want to load from your chosen material: ");
      scanf("%d", &material_count_case3);

      while(1){
        printf("Enter the ID of the wagon you want to load: ");
        scanf("%d", &wagon_id_case3);

        if(wagon_not_found(tr, wagon_id_case3)){
          break;
        }
      }
      
      Material* materyal_case3 = create_material(material_type_case3, material_count_case3);
      add_material_in_wagon(tr, wagon_id_case3, materyal_case3);
      printf("%d %sS ADDED TO THE TRAIN!!\n", material_count_case3, to_upper(materyal_case3->name));

      break;

    case 4:
      int material_type_case4;
      int material_count_case4;

      while(1){
        printf("1) Large Box (Steel) : 200 kg\n");
        printf("2) Medium Bax (Aluminium) : 150 kg\n");
        printf("3) Small Box (Wood) : 100 kg\n");
        printf("\nSelect the material you want to unload: ");
        scanf("%d", &material_type_case4);

        if(material_not_found(material_type_case4)){
          break;
        }
      }
      printf("How many items do you want to unload from your chosen material: ");
      scanf("%d", &material_count_case4);

      Material* materyal_case4 = create_material(material_type_case4, material_count_case4);
      remove_material(tr, materyal_case4);
      break;

    case 5:
      int material_type_case5;
      int material_count_case5;
      int wagon_id_case5;

      while(1){
        printf("1) Large Box (Steel) : 200 kg\n");
        printf("2) Medium Bax (Aluminium) : 150 kg\n");
        printf("3) Small Box (Wood) : 100 kg\n");
        printf("\nSelect the material you want to unload: ");
        scanf("%d", &material_type_case5);

        if(material_not_found(material_type_case5)){
          break;
        }
      }
      printf("How many items do you want to unload from your chosen material: ");
      scanf("%d", &material_count_case5);

      while(1){
        printf("Enter the ID of the wagon you want to unload: ");
        scanf("%d", &wagon_id_case5);
        
        if(wagon_not_found(tr, wagon_id_case5)){
          break;
        }
      }

      Material* materyal_case5 = create_material(material_type_case5, material_count_case5);
      remove_material_in_wagon(tr, wagon_id_case5, materyal_case5);
      break;

    case 6:
      display_train(tr);
      break;
    
    case 7:
      display_material_status(tr);
      break;
    
    case 8:
      empty_train(tr);
      break;
    
    case 9:
      char file_name[30];
      printf("Please enter file name (must be .txt at the end): ");
      scanf("%29s", file_name);
      save_file(tr, file_name);
      break;
    
    case 10:
      delete_train(tr);
      printf("\nThe application has been exited!! \nIf you want to perform an operation, please restart it.\n\n");
      return 0;
      break;
    
    default:
      printf("Please enter a valid number!");
      break;
    }
  }

  
}
