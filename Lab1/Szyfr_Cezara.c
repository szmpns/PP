#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char tekst[100];
    char zmienna , e;
    int klucz;

    printf("Podaj tekst, ktory chcesz zaszyfrowac, a nastepnie rozmiar klucza: \n");
    scanf("%[^\n]s" , tekst);

    scanf("%d" , &klucz);

//    printf("%s\n" , tekst);

    for( int i = 0 ; i < strlen(tekst) ; i++){
        zmienna = tekst[i];
        if(isalnum(zmienna)){
            if(islower(zmienna)){
                if(zmienna + klucz > 122){
                    e = zmienna + klucz - 122;
                    zmienna = e + 96;
                }
                else{
                    zmienna = zmienna + klucz;
                }
            }
            if(isupper(zmienna)){
                if(zmienna + klucz > 90){
                    e = zmienna + klucz - 90;
                    zmienna = e + 64;
                }
                else{
                    zmienna = zmienna + klucz;
                }
            }
        }
        else{
            zmienna = 32;
        }
        tekst[i] = zmienna;
//        printf("%d\n" , i);
    }
    printf("%s" , tekst);
    return 0;
}