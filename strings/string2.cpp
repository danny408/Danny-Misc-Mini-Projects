//2. Write a function that uses #1 to clean up a string. Now reverse all space-separated words (abc -> cba) in-place.
#include <stdio.h>

void strip(char *str);
void reverse(char *str);

int main(void){
	char test[26] = "th\nis  is\natest  st\nring ";
	printf("Before strip1:%s\n\n",test);
	strip(test);
	printf("\nAfter strip1:\"%s\"\n",test);
				//Output="this isatest string "
	printf("Before reverse1:%s\n\n",test);
	reverse(test);
	printf("\nAfter reverse1:\"%s\"\n",test);
				//Output="siht tsetasi gnirts "
	printf("\n\n--------------\n\n");
	
	
	
	
	
	char test2[34] = "\n\nhello  is a  \ntest word\n\n  a\n\n";
	printf("Before strip2:%s\n",test2);
	strip(test2);
	printf("After strip2:\"%s\"\n",test2);
				//Output="hello is a test word a"
	printf("Before reverse2:%s\n\n",test2);
	reverse(test2);
	printf("\nAfter reverse2:\"%s\"\n",test2);
				//Output="olleh si a tset drow a"
	printf("\n\n--------------\n\n");
	
	
	
	
	
	char test3[46] = "  \n\nwhat  is that  \ntest number\n\n  a\nafds  ";
	printf("Before strip3:%s\n",test3);
	strip(test3);
	printf("After strip3:\"%s\"\n",test3);
				//Output=" what is that test number aafds "
	printf("Before reverse3:%s\n\n",test3);
	reverse(test3);
	printf("\nAfter reverse3:\"%s\"\n",test3);
				//Output=" tahw si taht tset rebmun sdfaa "
	printf("\n\n--------------\n\n");
	
	
	
	
	
	char test4[70] = " this is a perfectly valid string that needs no editing ";
	printf("Before strip4:%s\n",test4);
	strip(test4);
	printf("After strip4:\"%s\"\n",test4);
				//Output=" this is a perfectly valid string that needs no editing "
	printf("Before reverse4:%s\n\n",test4);
	reverse(test4);
	printf("\nAfter reverse4:\"%s\"\n",test4);
				//Output=" siht si a yltcefrep dilav gnirts taht sdeen on gnitide "
	printf("\n\n--------------\n\n");
	
	
	
	
	
	printf("Exiting...\n");
	return 0;
}

void strip(char* str) {
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

void reverse(char *str){
	char *a = str,*b = str;
	char temp = 0;
	int len = 0;
	
	
	
	
	while(*str){
		if (*str == ' '){
			//printf("Entered A with length:%i will do:%i iterations\n",len,len/2);
			b = str-1;
			
			
			
			
			for (int i = 0; i < len/2; i++){
				//printf("String:%s\n",c);
				temp = *a;
				*a = *b;
				*b = temp;
				a++;
				b--;
			}
			
			
			
			
			len = 0;
			a = str+1;
			str++;
		}
		
		
		
		
		else{
			len++;
			str++;
		}
	}
}






 

