#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
    //loops
    int xx;
    for(xx = 5 ; xx < 15 ; xx = xx + 1){
        if(xx == 8)
        break;
        printf("Este bucle se ejecuta cuando xx es menor de 8,"
        "ahora xx es %d\n", xx);
    }
    for(xx = 5 ; xx < 15 ; xx = xx + 1){
        if(xx == 8)
        continue;
        printf("Ahora xx es diferente de 8, xx tiene el valor de %d\n", xx);
    }

    //string
    char msg[]="Hola Mundo";
    printf("%s\n",msg);
    printf("%c\n",msg[0]);
    printf("%c\n",msg[strlen(msg)-1]);


    char msg_2[]="Hola Mundo";
    msg_2[4] = '\0';
    printf("%s\n",msg_2);

    //matrices
    int bidimension[10][20];
    short int tridimension[2][3][4];
    char tridimensionc[2][2][3] = {
                    { {'A','B','C'}, {'D','E','F' } },
                    { {'G','H','I'}, {'J','K','L' } }};
    printf("%i", tridimensionc);

    return 0;
};

