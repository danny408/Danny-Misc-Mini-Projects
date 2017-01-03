#include "ds1.h"

//decodes doubleAddr
static struct doubleLinked* XOR (struct doubleLinked *a, struct doubleLinked *b)
{
	#if __SIZEOF_POINTER__ == 8 // 64-bit
	return (struct doubleLinked*) ((uint64_t)a ^ (uint64_t)b);
	#else 
    return (struct doubleLinked*) ((uint32_t)a ^ (uint32_t)b);
	#endif
}

//CAN ONLY PASS HEAD OR TAIL NODE;
void traverse(doubleLinked *start){
	if (start == 0){
		printf("Error Empty LL\n");
	}
	
	doubleLinked *curr = start;
	doubleLinked *prev = NULL;
	doubleLinked *next = NULL;
	while(curr != NULL){
		printf("Current:%i,%p\n",curr->value,curr);
		//printf("%i",curr->value);

		next = XOR(prev,curr->doubleAddr);
		prev = curr;
		curr = next;
		
		if (curr != NULL){
			printf("->");
		}
	}
}



//creates a head node
struct doubleLinked* createDLL(const int value){
	doubleLinked *newLL = (doubleLinked*)malloc(sizeof(doubleLinked));
	newLL->value = value;
	newLL->doubleAddr = NULL;
	return newLL;
}

//can make this append by passing head too but waste of time
struct doubleLinked* append(doubleLinked *tail, const int value){
	doubleLinked *curr = tail;
	doubleLinked *newNode = (doubleLinked*)malloc(sizeof(doubleLinked));
	newNode->value = value;
	newNode->doubleAddr = XOR(0,curr);
	curr->doubleAddr = XOR(XOR(0,curr->doubleAddr),newNode);
	return newNode;
}

void deleteLL(doubleLinked *head){
	doubleLinked *curr = head;
	doubleLinked *prev = NULL;
	while(curr != NULL){
		prev = curr;	
		curr = XOR(prev,curr->doubleAddr);
		free(prev);
	}
}

//free pointer in the DLL if found, otherwise just frees the pointer anyways
void deleteEntry(doubleLinked *head, doubleLinked *value){
	if (head == 0){
		printf("Error Empty LL\n");
	}
	
	doubleLinked *curr = head;
	doubleLinked *prev = NULL;
	doubleLinked *next = NULL;

	while(curr != NULL){
		
		if (curr == value){
			next = XOR(prev,curr->doubleAddr);

			if (XOR(next,curr->doubleAddr) == NULL){
				next->doubleAddr = XOR(XOR(next->doubleAddr,curr),NULL);
			}
			
			else if(XOR(prev,curr->doubleAddr) == NULL){
				prev->doubleAddr = XOR(XOR(prev->doubleAddr,curr),NULL);
			}
			
			else{//If its not a head/tail node
				prev->doubleAddr = XOR(XOR(prev->doubleAddr,curr),XOR(curr->doubleAddr,prev)); // needs before before + after = 2b , 1a
				next->doubleAddr = XOR(XOR(curr->doubleAddr,next),XOR(next->doubleAddr,curr)); // needs before + after after = 2a, 1b
			}
			//move previous to point to next one after, move next one after to point to previous;
			free(value);
			return;
		}
		next = XOR(prev,curr->doubleAddr);	
		prev = curr;
		curr = next;

	}	

	printf("Entry not found in DLL, Pointer Freed!\n");
	free(value);
	return;
}