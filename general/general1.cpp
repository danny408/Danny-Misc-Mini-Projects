//1. Implement your own MT-safe queue class in c++.

/*
Need a lock to prevent multiple threads from accesing it at the same time.
*/

#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <pthread.h>


/*
[2:18:32 PM] gamer26: anyway its a job queue
[2:18:38 PM] gamer26: so just an int
[2:18:39 PM] gamer26: doesnt cut it
[2:18:43 PM] gamer26: you have to run remove functions
[2:19:00 PM] gamer26: so i'd write a c++11 lambda callback system
[2:19:02 PM] gamer26: or do it the pthread way
[2:19:12 PM] gamer26: where you throw void pointers into your void functions
*/
struct singlyLL{
	void *task;
	struct singlyLL *next;
};


class mtQueue{
	private:
		singlyLL *front;
		singlyLL *back;
		pthread_mutex_t lock;
		unsigned int size;
		
	public:
		mtQueue();
		~mtQueue(void);
		void push(void *task);
		void* pop();
		inline unsigned int getSize();
		inline bool isEmpty();
};


int main(void){
	return 1;
}

mtQueue::mtQueue(){
	front = NULL;
	back = NULL;
	size = 0;
}
void mtQueue::push(void *task){
	
	
	if (size == 0){
		front->value = value;
		front->next = NULL;
		back = front;
	}
	
	
	else{
		singlyLL *next = new(singlyLL);
		next->value = value;
		next->next = NULL;
		back->next = next;
	}
	
	
	size++;

}

void* mtQueue::pop(){
	if(size == 0){
		printf("Cannot not pop empty queue");
	}
	
	
	else if (size == 1){
		void* task= front->value;
		front = NULL;
		return task;
		//need to free popped LL that just disappears???
	}
	else{
		void* task = front->value;
		singlyLL *p = front;
		front = front->next;
		free(p);
		return task;
	}
}

inline bool mtQueue::isEmpty(){
	if (size == 0){
		return true;
	}
	else {
		return false;
	}
}

inline unsigned int mtQueue::getSize(){
	return size;
}
