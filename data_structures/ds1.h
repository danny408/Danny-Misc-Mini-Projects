//1. Write a linked list which uses one pointer to traverse from either direction. 
//What bitwise function allows you to do this? Are there any limitations of that design?

#include <stdio.h> //printf shit
#include <stdint.h> // for uint32/64
#include <stdlib.h> //malloc

//use xor to use one pointer only
//can encode two pointes a,b as c = (a xor b);
//recover a and b by a = c xor b and , b = c xor a ;
//can only traverse from head or tail node
//to make it start from anywhere in the linked list you would need to index all LL addresses somewhere and find an
//adjacent one to theo ne ur passing depending on direction = more overhead = bad? (ex store addr of LL A,B,C)
//pass B into function, and look up A if u wanna go backwards, C if u wanna go forward and use A/C to decode B's twowayADDR

struct doubleLinked{
	int value;
	struct doubleLinked* doubleAddr;
};

void traverse(doubleLinked *start);
struct doubleLinked* createDLL(const int value);
struct doubleLinked* append(doubleLinked *head,const int value);
void deleteEntry(doubleLinked *head, doubleLinked *value);
void deleteLL(doubleLinked *head);
//static struct doubleLinked* XOR (struct doubleLinked *a, struct doubleLinked *b);


/*
int main(void){
	doubleLinked *head = createDLL(1);
	doubleLinked *tail = head;
	doubleLinked *del = head;
	
	
	tail = append(tail,2);
	tail = append(tail,3);
	//del = tail; //Tests Deleting a Middle
	tail = append(tail,4);
	tail = append(tail,5);	
	del = tail; //Tests Deleting a Node with no prevprev or nextnext node
	tail = append(tail,6);
	//del = tail; //Tests Deleting a Tail Node
	
	
	printf("Forward:");
	traverse(head); //forward
	printf("\nBackward:");
	traverse(tail);
	printf("\n");

	deleteEntry(head,del);
	//deleteLL(head);
	traverse(head);

	return 1;
}
*/

