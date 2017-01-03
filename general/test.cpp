


#include <stdio.h>
#include "/home/danny/dannyQuestions/data_structures/ds1.h"

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