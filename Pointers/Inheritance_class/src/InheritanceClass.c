/*
 ============================================================================
 Name        : InheritanceClass.c
 Author      : Moshe
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct myClass{

	int m_x;
	void (*add)(struct myClass*, int);

}myClass;

void add(myClass* class, int y)
{
	if(class == NULL)
		exit(1);

	class->m_x += y;
}

int main(void) {

	myClass class;
	class.m_x = 3;
	class.add = &add;
	printf("%d\n",class.m_x);

	(*class.add)(&class,5);
	printf("%d\n",class.m_x);

	puts("\nAll is OK"); /* prints All is OK */
	return EXIT_SUCCESS;
}
