//1. Write a function that strips all newlines and double spaces in-place.
#include <stdio.h>

void strip(char *str);

int main(void){
	char test[26] = "th\nis  is\natest  st\nring ";
	printf("Before strip1:%s\n\n",test);
	strip(test);
	printf("\nAfter strip1:\"%s\"\n",test);
	printf("\n\n--------------\n\n");
	
	
	
	
	char test2[34] = "\n\nhello  is a  \ntest word\n\n  a\n\n";
	printf("Before strip2:%s\n",test2);
	strip(test2);
	printf("After strip2:\"%s\"\n",test2);
	printf("\n\n--------------\n\n");
	
	
	
	
	char test3[46] = "  \n\nwhat  is that  \ntest number\n\n  a\nafds  ";
	printf("Before strip3:%s\n",test3);
	strip(test3);
	printf("After strip3:\"%s\"\n",test3);
	printf("\n\n--------------\n\n");
	
	
	
	
	
	char test4[70] = " this is a perfectly valid string that needs no editing ";
	printf("Before strip4:%s\n",test4);
	strip(test4);
	printf("After strip4:\"%s\"\n",test4);
	printf("\n\n--------------\n\n");
	printf("Exiting...\n");
	return 0;
}

void strip(char *str) {
	if (str == NULL){
		printf("String is NULL\n");
    	return;
    }
	
	
	
	
    char *pr = str, *pw = str; //read ptr = str, write ptr = str
    bool dblSpace = false; //to check if the space is a second space or not
	
	
	
	
    while (*pr) { //while index isnt null
        *pw = *pr++; //copies current pr value to current index of pw then increments pr;
		
		
		
		
        if (*pw == ' ' && dblSpace == false){ //if current index is a space but the first space
        	dblSpace = true;
        	pw += 1; //increments to next index without changing anything
        }
		
		
		
		
        else{
        	dblSpace = false; //current index is either a 2nd space or not will make false in either scenario
       		pw += (*pw != ' ' && *pw != '\n'); // will increment write pointer if not a null or second space
    	}
    }
    *pw = '\0'; // null terminates after shifting(if any) new string

}
