#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/*see header file for methods declaration and behaviour */

DynamicArray* create_array (int initial_capacity){
	DynamicArray *arr = (DynamicArray*) malloc (sizeof(DynamicArray)); //reserve sizeof(DynamicArray) bytes
									   //for obj pointer
	if (arr == NULL) exit(1); //out of memory exception

	arr->data = (int*) malloc(initial_capacity * sizeof(int));
	if (arr->data == NULL){
		free(arr);//out of memory exception, free the memory previously reserved for obj pointer
		exit(1);
	}

	arr->size=0; //array is now empty
	arr->capacity = initial_capacity; //set the initial capacity to param, 
					  //now array has initial_capacity free cells
	return arr; //array successufully created
}//create_array

/*returns idx of first 'value' occurrency, this function returns -1 upon not found instance */
int array_find (DynamicArray *arr, int value){
	for (int i = 0; i<arr->size; i++){
		if (arr->data[i] == value) return i;
	}
	return -1;
}//array_find

int array_delete_at (DynamicArray *arr, int idx){
	if (idx < 0 || idx >= arr->size){
		printf("Index out of bound\n");
		exit(1);
	}
	if (idx == arr->size -1)return array_pop(arr);
	else if(idx == 0) return array_dequeue(arr);
	else {
		int tmp = arr->data[idx];
		for (int i = idx; i<arr->size -1; i++) arr->data[i] = arr->data[i+1];
		arr->size--;
		return tmp;
	}
}//array_delete_at

/*appends value 'value' at the tail */
void array_append (DynamicArray *arr, int value){
	if (arr->size >= arr->capacity){
		arr->capacity *=2;//no more free cells, reallocate 2 * current capacity new cells
		int *temp = (int*) realloc(arr->data, arr->capacity * sizeof(int)); //since we need to check 
										    //for realloc success
		if (temp == NULL) exit(1); //out of memory
		arr->data = temp;
	}

	arr->data[arr->size] = value;
	arr->size++; //size always points to first free cell in arr->data

}//array_append

/*returns the value stored at index 'idx'*/
int array_get (DynamicArray *arr, int idx){
	if( idx < 0 || idx >= arr->size){
	printf("Index out of bound\n");
	exit(1);
	}
	return arr->data[idx];
}//array_get

//start of LIFO policy methods

/*same as array_append (DynamicArray *arr, int value) renaming for LIFO policy*/
void array_push(DynamicArray *arr, int value){
	array_append(arr, value);
}//array_push

/* returns last element stored in arr->data and deletes it*/
int array_pop(DynamicArray *arr){
	if (arr->size == 0){
		printf("Can't pop from empty stack\n");
		exit(1);
	}
	return arr->data[--arr->size];
}//array_pop

/* returns last element stored in arr->data without altering it */
int array_peek(DynamicArray *arr){
	if (arr->size == 0){
		printf("Can't peek from an empty stack\n");
		exit(1);
	}
	return arr->data[arr->size -1];
}//array_peek

//end of LIFO policy methods

//start of FIFO policy methods

/*same as array_append (DynamicArray *arr, int value) renaming for FIFO policy*/
void array_enqueue(DynamicArray *arr, int value){
	array_append(arr,value);
}//array_enqueue

/*returns current head of arr->data and deletes it */
int array_dequeue(DynamicArray *arr){
	if (arr->size == 0){
		printf("Can't dequeue from empty queue\n");
		exit(1);
	}
	int tmp = arr->data[0];
	for (int i = 0; i<arr->size -1; i++) arr->data[i]=arr->data[i+1];
	arr->size--;
	return tmp;
}//array_dequeue

//end of FIFO policy methods

/*frees all the allocated memory to avoid memory leak */
void free_array (DynamicArray *arr){
	if (arr!=NULL){ //if arr is not NULL we destroy it
		free(arr->data); /*we first destroy data array, if we do the other way around we would have
				no more access to this specific pointer since arr would already be destroyed*/
		free(arr);
	}
}
/*clear the array from current data in O(1)*/
void clear (DynamicArray *arr){
	if (arr!=NULL){
		arr->size = 0;	
	}
}

/*safe even for largest integer value*/
char *toString (DynamicArray *arr){
	int max_len = (arr->size * 14)+3;//each elem of arr has 11 char at worst,
					 //1 byte for the comma,
					 //1 byte for the space
					 //which means 13 bytes at worst for each integer
					 //therefore we multiply
					 //size * 14 for some overhead
					 //+3 is for [] and \0 (string null term in c)
	char *str = (char*)malloc(max_len);
	str [0] = '[';
	int offset = 1;
	for (int i = 0; i < arr->size; i++){
		if (i == arr->size-1){
		offset += snprintf(str + offset,max_len-offset,"%d", arr->data[i]);
		break;
		}
		offset += snprintf(str + offset, max_len-offset , "%d, ", arr->data[i]);
	}
	offset += snprintf(str + offset, max_len-offset, "]");
	return str;
}
