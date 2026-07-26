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
int array_find(DynamicArray *arr, int value); //returns idx of first 'value' occurency
int array_delete_at(DynamicArray *arr, int idx);//deletes the value stored at arr->data[idx]
void array_append (DynamicArray *arr, int value); //appends in tail the value 'value'
int array_get(DynamicArray *arr, int idx); //gets value stored at arr[idx]

//start of LIFO policy methods
void array_push(DynamicArray *arr, int value);//pushes value, LIFO policy
int array_pop(DynamicArray *arr);//pops last value from the array, LIFO policy
int array_peek(DynamicArray *arr); //returns next value that will be popped without deleting it
//end of LIFO policy methods

//start of FIFO policy methods
void array_enqueue (DynamicArray *arr, int value);//queues the value 'value', appending to tail, FIFO policy
int array_dequeue (DynamicArray *arr);//returns current head and deletes it, FIFO policy
//end of LIFO policy methods

void free_array(DynamicArray *arr); //frees the memory destroying the array
void clear(DynamicArray *arr); //clears array
char *toString(DynamicArray *arr);//toString method

#endif
