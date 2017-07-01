#include <stdio.h>
#include <stdlib.h>    
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

       

struct QW{
    char sumbl;
    short coll;
    char around[7];
}qw[28];


char ArrayBuffer[466549][51];


#define MAXHASHARRAY 500000
int HashArray[MAXHASHARRAY];
int CountHash = 0;


char compare(char chB, char chNext){
    char ch[2];
    for(int i = 0; i < qw[chB-97].coll; i++ ){
        
        ch[0] = (char)qw[chB-97].around[i];
        if(chNext==qw[chB-97].around[i]){
            return 1;
        }
    }
    return 0;
}

/*Создаем массив в который будем добавлять только те элементы которых он еще не содержит*/
char includeInHash(int CX){
    for(int mHash = 0; mHash < CountHash; mHash++){
        if( HashArray[mHash] == CX) { return 0;}       
    }
    HashArray[CountHash] = CX;
    CountHash++;
    return 1;
}

/* Здесь рекурсивынй поиск */
int recursion(int start, int end, char *chBais, int baisArray, int size){
    int result = 0;
    int localEnd = 0;
    baisArray++;
    for(;(start < end) && (ArrayBuffer[start][baisArray] != chBais[0]) ; start++ ){}
    for(localEnd=start; (localEnd < end)  && (ArrayBuffer[localEnd][baisArray] == chBais[0]) && (ArrayBuffer[localEnd][baisArray] != 10)  ; localEnd++){ result++; }
    if(result == 0) {return -1;}
        


    if(size>1){
        size--;        
        char ch[2]; ch[0] = chBais[0];
        if(*(chBais+1) !=0 ) chBais++;
        if((ArrayBuffer[localEnd][baisArray] == 10) || (result == 0 )){ printf("ArrayBuffer[start][baisArray] == 10"); return -2; }
        recursion(start, localEnd, chBais, baisArray, size);
    }else if(result > 0){
        for(int iStart = start; iStart < localEnd; iStart++){
            if(ArrayBuffer[iStart][baisArray+1] == 10){
                includeInHash(iStart);
            }
        }
        for(int coll = 0; coll < qw[chBais[0]-97].coll; coll++){
            char localchBais = qw[chBais[0]-97].around[coll];
            char ch[2]; ch[0] = localchBais;
            recursion(start, localEnd, &localchBais, baisArray, size);
        }        

    }


    return result;
}





int main (int argc, char **argv[])
{
    if(argc < 2){ exit(0); }
    

    printf("---\n");

    int descriptor = open("WordEnglisSortUniq.txt", O_RDONLY);  // ЗдесьХранитсяОтсортированный Список Английских слов без поторейни
    FILE *file = fdopen(descriptor, "rb");
    int x=0;
    while(fgets (ArrayBuffer[x++], 50, file) != NULL){}
    char *resorting = "abcdefghijklmnopqrstuvwxy";
    fclose(file);
    close(descriptor);


    for(int i = 0; i < 27; i++){
        qw[i].coll = 0;
    }

    /*Так выглядитт qwerty клавиатура*/
    char qwerty[3][10]={"qwertyuiop","asdfghjkl-","zxcvbnm---"};  
    char ch[2];

    int alpha=0;

    /* Привязываем к каждой букве из QWERTY-клавиатуры, её соседей и размещаем все в алфафитном порядке*/
    for(int line = 0; line < 3; line++){        
        for(int sumb = 0; sumb < 10; sumb++){
            if( (alpha) >= 26) { break; }
            if(qwerty[line][sumb] != '-'){
                qw[qwerty[line][sumb]-97].sumbl = qwerty[line][sumb];
                if(((line - 1) >= 0 && (line - 1) < 3)&&((sumb) >= 0 && (sumb) < 10)){
                    ch[0] = qwerty[line - 1][sumb];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }
                }
                if(((line - 1) >= 0 && (line - 1) < 3)&&((sumb + 1) >= 0 && (sumb + 1) < 10)){
                    ch[0] = qwerty[line - 1][sumb + 1];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }

                }
                if(((line) >= 0 && (line) < 3)&&((sumb - 1) >= 0 && (sumb - 1) < 10)){
                    ch[0] = qwerty[line][sumb - 1];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }

                }
                if(((line) >= 0 && (line) < 3)&&((sumb + 1) >= 0 && (sumb + 1) < 10)){  
                    ch[0] = qwerty[line][sumb+1];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }
                }
                if(((line + 1) >= 0 && (line + 1) < 3)&&((sumb - 1) >= 0 && (sumb - 1) < 10)){ 
                    ch[0] = qwerty[line+1][sumb - 1];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }
                }
                if(((line + 1) >= 0 && (line + 1) < 3)&&((sumb) >= 0 && (sumb) < 10)){ 
                    ch[0] = qwerty[line+1][sumb];
                    if(ch[0] != '-'){
                        qw[qwerty[line][sumb]-97].around[qw[qwerty[line][sumb]-97].coll] = ch[0];
                        qw[qwerty[line][sumb]-97].coll++;
                    }
                }               
                alpha++;
            }  
        }      
    }

    char *ar = (char *)argv[1];
    for(int i = 0; i < strlen(ar)-1; i++){        
        char ch[2];
        ch[0] = (char)ar[i];
        if(compare(ch[0],ar[i+1])!=1){ printf("Введена не верная последовательность букв"); exit(0); }        
    }

    recursion(0, 466549, (char *)argv[1], -1, (int)strlen((const char *)argv[1]));

    /*Выводи то что в итоге получилось на экран*/
    for(int mHash=0; mHash < CountHash; mHash++){
        printf("%s", ArrayBuffer[HashArray[mHash]]);
    }

    printf("\n------------------------------- \n");
    printf("CountWords %d \n", CountHash);






/*
    Маска окружени для любой буквы на клавиатуре

               [0][1]1    [0][2]2 
    [1][0]3    [1][1]     [1][2]4 
    [2][0]5    [2][1]6    


    qwertyuiop
    asdfghjkl
    zxcvbnm

    [0][0]    [0][1]    [0][2] 
    [1][0]    [1][1]    [1][2] 
    [2][0]    [2][1]    [2][2]

              [0][1]    [0][2] 
    [1][0]    [1][1]    [1][2] 
    [2][0]    [2][1]    


    ++
    a+
    +

    we
   asd
   zx

    er
   sdf   
   xc

    rt    
   dfg 
   cv



*/

    return 0;
}