#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

/* a dynamic, resizable array in the c language*/
typedef struct DynamicArray{

int *data; //actual array, stored in the heap thanks to malloc
int size; //current number of elements
int capacity; //number of total cells in the array

}DynamicArray;

//functions signatures

DynamicArray* create_array(int initial_capacity); //such as the constructor in OOP languages
void array_append (DynamicArray *arr, int value); //appends in tail the value 'value'
int array_get(DynamicArray *arr, int idx); //gets value stored at arr[idx]
void free_array(DynamicArray *arr); //frees the memory destroying the array
void clear(DynamicArray *arr); //clears array
char *toString(DynamicArray *arr);//toString method

#endif
