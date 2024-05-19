#include "array.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int findMinimum( int *array, int size ){
    int minimum = array[0];

    for (int i = 0; i < size; i++)
    {
            if ( array[i] < minimum )
            {
               minimum = array[i];
            }
    }

    return minimum;
}

int findMaximum( int *array, int size ){
    int maximum = array[0];

    for (int i = 0; i < size; i++)
    {
            if ( array[i] > maximum )
            {
               maximum = array[i];
            }
    }

    return maximum;
}

double calcAverage( int *array, int size ){
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += array[i];
    }

    return ((double)total)/((double)size);
}

double findMedian( int *array, int size ){
    bubbleSort( array, size );

    if( size % 2 != 0 ){
        return array[ size/2 ];
    }
    else{
        return ( array[size/2 - 1] + array[size/2] )/2;
    }
}

void swapElements( int *array, int size, int a, int b ){
    if( a >= size || b >= size )
        return;

    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

void randomizeArray( int *array, int size, unsigned int maxValue ){
    time_t t;
    srand( time(&t) );

    for (int i = 0; i < size; i++)
    {
        array[i] = ( rand() % maxValue ) + 1;
    }
}

int* resizeArray( int *array, int size, int newSize ){
    int *newArray = (int*)realloc( array, newSize );

    if( NULL == newArray ){
        return 0;
    }

    // Wypelnij wolne miejsce zerami
    if( newSize > size )
        memset( newArray+size, 0, newSize);
    
    return newArray;
}

int loadFromFile( int *array, char *filename ){
    FILE *fp;
    int number;
    int i = 0;

    fp = fopen (filename, "r");

    if( NULL == fp ){
        printf ("Blad pliku\n");
        return 0;
    }

    // Szukanie liczby elementów
    while( !feof(fp) ){
        fscanf(fp, "%d\n", &number);
        i++;
    }

    // Zmiana rozmiaru tablicy
    void *newArray = realloc( array, i );

    if( NULL == newArray ){
        printf("Blad alokacji\n");
        fclose( fp );

        return 0;
    }

    // Wczytanie elementow z pliku do nowej tablicy
    i=0;
    // Powrot do poczatku
    fseek( fp, 0, SEEK_SET );
    while( !feof(fp) ){
        fscanf(fp, "%d\n", &number);
        ((int*)(newArray))[i] = number;
        i++;
    }
    // Przepisanie wskaznika w przypadku jego zmiany
    array=(int*)newArray;

    fclose( fp );

    return i;
}

unsigned int saveToFile( int *array, int size, char *filename ){
    FILE *fp;
    int i;
    fp = fopen (filename, "w");

    if( NULL == fp ){
        printf ("Blad pliku\n");
        return 0;
    }

    // Zapis tablicy do pliku
    for(i=0;i<size;i++){
        fprintf( fp, "%d\n", array[i] );
    }

    fclose( fp );

    return i;
}

void bubbleSort( int *array, int size ){
    for( int i=0; i<size; i++ ){
        for( int j=0; j<size-i; j++ ){
            if( array[j] > array[j+1] ){
                swapElements( array, size, j, j+1 );
            }
        }
    }
}