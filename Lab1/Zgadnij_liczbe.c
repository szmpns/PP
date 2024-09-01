#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    int x =  rand() % 100; // 0 ≤ X < 100
    int n = rand() % 100;
    int min = 0;
    int max = 100;
    printf("Szukamy: ");
    printf("%d\n", x);

    while( x != n ){
//        printf("%d\n" , min );
//        printf("%d\n" , max);
        printf("Nasz aktualny przedzial jest od: ");
        printf("%d\n" , min);
        printf("do: ");
        printf("%d\n" , max);
        if( x > n ){
            min = n;
            n = min + rand() % (max - min);
        }
        if( x < n ){
            max = n;
            n = min + rand() % (max - min);
        }
    }
    printf("Szukana liczba to:");
    printf("%d\n" , n);
    return 0;
}