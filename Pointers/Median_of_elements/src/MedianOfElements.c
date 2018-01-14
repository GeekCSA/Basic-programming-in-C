/*
 ============================================================================
 Name        : Median_of_elements.c
 Author      : Moshe
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int* arr = NULL;
int countOfElements = 0;

void insertNewDataIntoArray(int data)
{
	countOfElements++;

	if(arr == NULL)
		arr = (int*)malloc(countOfElements * sizeof(int));
	else
	{
		arr = (int*)realloc(arr,countOfElements * sizeof(int));
	}

	arr[countOfElements - 1] = data;
}

int cmpfunc (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

void quickSort(int* arr,int size)
{
	qsort(arr, size, sizeof(int), cmpfunc);
}

int take2(int data)
{
	insertNewDataIntoArray(data);

	quickSort(arr,countOfElements);

	int median = arr[(int)(countOfElements/2)];

	return median;
}

int main(void) {

	for(int i = 0; i < 5; i++)
	{
		printf("The new value is: %d.\n The new median is: %d.\n",i, take2(i));
	}

	puts("\n");

	puts("All is OK"); /* prints All is OK */
	return EXIT_SUCCESS;
}
