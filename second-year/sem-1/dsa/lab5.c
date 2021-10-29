#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    int note;
    char gender;
    char name[255];
} STUDENT;

STUDENT x[100];
int numberOfStudents;

void readInput(int numberOfStudents){
    int noteAux;
    char genderAux;
    char nameAux[255];
    for(int i = 0; i < numberOfStudents; i++){
        scanf("%d %c %[^\n]255s", &noteAux,&genderAux,nameAux);
        x[i].note = noteAux;
        x[i].gender = genderAux;
        strcpy(x[i].name,nameAux);
    }
}

void bubbleSort_alfabetic(STUDENT arr[], int numberOfStudents)
{
   for (int i = 0; i < numberOfStudents; i++)       
       for (int j = 0; j < numberOfStudents-i; j++)
           if (strcmp(arr[j].name,arr[j+1].name) > 0){
                STUDENT temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
}

int main(){

    printf("nr de studenti:\n");
    scanf("%d", &numberOfStudents);

    readInput(numberOfStudents);


    printf("1 for a or 2 for b?\n");
    int comanda;
    scanf("%d",&comanda);
    

    printf("%d\n",comanda);
    if (comanda == 1) {
        bubbleSort_alfabetic(x,numberOfStudents);
    } 
    else if (comanda == 2){


    } else {
        printf("Wrong command.\n");
        exit(-1);
    }

    for(int i = 1; i <= numberOfStudents;i++){
        printf("note: %d gender: %c, name: %s\n", x[i].note, x[i].gender,x[i].name);
    }
    
    return 0;
}