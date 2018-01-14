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

typedef struct Derived{

	myClass my_class;

}Derived;

typedef struct Derived2{

	int m_y;
	myClass p;

}Derived2;

void add(myClass* class, int y)
{
	if(class == NULL)
		exit(1);

	class->m_x += y;
}

void add2(myClass* class, int y)
{
	Derived2* class1 = class;

	if(class == NULL)
		exit(1);

	class1->m_y = y;
	class1->p.m_x += y;
}

void xor(myClass* class, int y)
{
	Derived* class1 = class;

	if(class == NULL)
		exit(1);

	class1->my_class.m_x ^= y;
}

int main(void) {

		//part 1
		myClass class;
		class.m_x = 3;
		class.add = &add;
		printf("%d\n",class.m_x);

		(*class.add)(&class,5);
		printf("%d\n",class.m_x);

		//part 2
		Derived class1;
		class1.my_class.m_x = 3;
		class1.my_class.add = &xor;
		printf("%d\n",class1.my_class.m_x);

		(*class1.my_class.add)(&class1,5);
		printf("%d\n",class1.my_class.m_x);

		//part 3
		Derived2 class2;
		class2.p.m_x = 3;
		class2.p.add = &add2;
		printf("%d\n",class2.p.m_x);

		(*class2.p.add)(&class2,5);
		printf("%d\n",class2.p.m_x);

		puts("\nAll is OK"); /* prints All is OK */
		return EXIT_SUCCESS;
}
