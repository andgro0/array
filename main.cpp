#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void displayMenu();
void printArray( int *array, int size );

int main(){
    int aSize;
    int *array;
    char filename[50];

    printf( "Ile liczb losowych chcesz zapisac w tablicy? ");
    scanf( "%d", &aSize );

    array = (int *) malloc( aSize * sizeof(int ));

    if ( !array )
    {
        printf("Nie udało się alokować tablicy!\n");
        exit(1);
    }

    randomizeArray( array, aSize, 500 );

    int selection=0;
    do{
        displayMenu();
        scanf( "%d", &selection );
        printf( "Wybrano: %d\n", selection );

        switch( selection ){
            case 0:
                printf( "Wyjscie\n" );

                break;
            case 1:
                printArray( array, aSize );

                break;
            case 2:
                printf( "Podaj element: \n" );
                int argument;
                scanf( "%d", &argument );
                if( argument >= aSize ){
                    printf( "Element poza zakresem tablicy \n" );
                    break;
                }
                printf( "array[%d]=%d\n", argument, array[argument]);

                break;
            case 3:
                unsigned int element;
                int value;

                printf( "Jaki element chcesz zmienic:\n" );
                scanf( "%d", &element );
                if(element >= aSize){
                    printf( "Element poza zakresem tablicy\n" );
                    break;
                }
                printf( "Podaj wartosc elementu:\n" );
                scanf( "%d", &value );

                array[element] = value;

                break;
            case 4:
                printf( "Srednia: %.2f\n", calcAverage( array, aSize ) );

                break;
            case 5:
                printf( "Mimimum: %d\n", findMinimum( array, aSize ) );

                break;
            case 6:
                printf( "Maximum: %d\n", findMaximum( array, aSize ) );

                break;
            case 7:
                int a,b;

                printf( "Podaj a i b\n" ); 
                scanf( "%d %d", &a, &b );

                swapElements( array, aSize, a, b );

                break;
            case 8:
                printf( "Sortowanie\n" );

                bubbleSort( array, aSize );

                break;
            case 9:
                printf( "Mediana: %.2f\n", findMedian( array, aSize ) );

                break;
            case 10:
                int maxValue;

                printf( "Podaj limit wartosci losowych\n" );
                scanf( "%d", &maxValue );

                randomizeArray( array, aSize, maxValue );

                break;
            case 11:
                printf( "Podaj nowy rozmiar tablicy\n" );
                int newSize;
                int *newArray;
                scanf( "%d", &newSize);
                newArray = resizeArray( array, aSize, newSize );
                if( newArray == 0 )
                    printf("Blad alokacji\n");
                else
                    array=newArray;

                break;
            case 12:
                printf( "Podaj nazwe pliku\n" );
                scanf( "%s", &filename );
                int writeCount;
                writeCount = saveToFile( array, aSize, filename );
                if( writeCount == aSize )
                    printf( "Zapisano: %d elementow\n", writeCount );
                else
                    printf( "Blad zapisu\n" );

                break;
            case 13:
                printf( "Podaj nazwe pliku\n" );
                scanf( "%s", &filename );
                int readCount;
                readCount = loadFromFile( array, filename );
                if( readCount )
                    printf( "Wczytano: %d elementow\n", readCount );
                else
                    printf( "Blad odczytu\n", readCount );

                break;
            default:
                printf( "Zły wybor:\n" );
        }
    }
    while( selection );

    free( array );

    return( 0 );

}

void displayMenu(){
    printf( "\nWybierz element z menu:\n" );
    printf( "1. Drukuj tablice\n" );
    printf( "2. Drukuj element\n" );
    printf( "3. Zmien element\n" );
    printf( "4. Oblicz srednia\n" );
    printf( "5. Znajdz minimum\n" );
    printf( "6. Znajdz maximum\n" );
    printf( "7. Zamien elementy\n" );
    printf( "8. Sortuj\n" );
    printf( "9. Znajdz mediane\n" );
    printf( "10. Losuj tablice\n" );
    printf( "11. Zmien rozmiar tablicy\n" );
    printf( "12. Zapisz do pliku\n" );
    printf( "13. Odczytaj z pliku\n" );
    printf( "0. Wyjdż\n" );
    printf( "\n" );
}

void printArray( int *array, int size ){
    for(int i=0; i<size; i++ ){
        printf( "array[%d]=%d\n", i, array[i] );
    }
}