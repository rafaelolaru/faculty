#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct cor {
    int rank;
    int code;
    char occ[255];
}COR;
 
COR x[4250];
int comparisons = 0;
int numberOfPeople = 0;
 
void readFile(FILE *f){
 
    int rankAux;
    int codeAux;
    char occAux[255];
 
    while (fscanf(f,"%d %d %[^\n]s",&rankAux,&codeAux,occAux) == 3){
 
        x[numberOfPeople].rank = rankAux;
        x[numberOfPeople].code = codeAux;
        occAux[strlen(occAux)-1] = '\0';
        strcpy(x[numberOfPeople].occ,occAux);
 
        numberOfPeople++;
    }
}
 
int search_bin(int left, int right, char* job){
 
    while(left <= right){
        comparisons++;
 
        int mid = left + (right - left) / 2;
 
        if(strcmp(x[mid].occ, job) == 0)
            return mid;
 
        if(strcmp(x[mid].occ, job) < 0)
            left = mid + 1;
 
        else
            right = mid - 1;
    }
    return -1;
}
 
void search_lin(int codeAux){
 
    for(int i = 0; i < numberOfPeople; i++){
        if(x[i].code == codeAux)
            printf("code:%d,job:%s\n",x[i].code,x[i].occ);
    }
}
 
void find_job(){
    printf("enter job\n");
    char job[255];
    scanf("%255s",job);
    int res = search_bin(0,numberOfPeople-1,job);
    if(res == -1)
        printf("not found\n");
    else
        printf("%d %s\n", x[res].code, x[res].occ);
}
 
void find_code(){
    printf("enter code\n");
    int codeAux;
    scanf("%d",&codeAux);
    search_lin(codeAux);
}
 
int main(int argc, char** argv){
 
    ///Open the file
    FILE *f;
    if(!(f = fopen(argv[1],"r"))){
        printf("Error loading file\n");
        exit(-1);
    }
 
    ///Read the file
    readFile(f);
    printf("number of ppl is: %d\n",numberOfPeople);
    
    ///Get the command
    printf("command:\n1(search by job) \nOR \n2(search by code)\n");
    int command;
    scanf("%d", &command);
    switch(command){
        case 1:{
            find_job();
            break;
        }
        case 2:{
            find_code();
            break;
        }
        default:{
            printf("Wrong command! Press either 1 or 2\n");
            exit(-1);
            break;
        }
    }
 
}