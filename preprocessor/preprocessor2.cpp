//2. Modify strings#1 and strings#2 to use std::string instead of char* for an input if the compiler supports C++. 
//The __cplusplus >= 201103L (C++11) version of this code should use the updated c_str standard if supported. 
//Older versions must do something different. There's obviously going to be some changes necessary to the 
//input/outputs of these functions. You can use -std=c++11 or -std=c++03 to switch between c++ versions with gcc.

//1. Write a function that strips all newlines and double spaces in-place. Do this without iterating through the string more than once.
#include <stdio.h>
#include <cstring>
#include <string>
#include <stdlib.h>

#if __cplusplus >= 201103L	
extern "C" void strip(std::string &str);
extern "C" void reverse(std::string &str);
#else	
extern "C" std::string reverse(std::string &str);
extern "C" std::string strip(std::string &str);
#endif


int main(void){

	std::string test = "th\nis  is\natest  st\nring ";
	printf("Before strip1:%s\n\n",test.c_str());
	#if __cplusplus >= 201103L	
	strip(test);
	printf("\nAfter strip1:\"%s\"\n",test.c_str());
	reverse(test);
	printf("\nAfter reverse1:\"%s\"\n",test.c_str());
	#else	
	printf("\nAfter strip1:\"%s\"\n",strip(test).c_str());
	printf("\nAfter reverse1:\"%s\"\n",reverse(test).c_str());
	#endif
	printf("\n\n--------------\n\n");
	

	std::string test2 = "\n\nhello  is a  \ntest word\n\n  a\n\n";
	printf("Before strip2:%s\n\n",test2.c_str());
	#if __cplusplus >= 201103L	
	strip(test2);
	printf("\nAfter strip2:\"%s\"\n",test2.c_str());
	reverse(test2);
	printf("\nAfter reverse2:\"%s\"\n",test2.c_str());
	#else	
	printf("\nAfter strip2:\"%s\"\n",strip(test2).c_str());
	printf("\nAfter reverse2:\"%s\"\n",reverse(test2).c_str());
	#endif
	printf("\n\n--------------\n\n");
	
	
	std::string test3 = "  \n\nwhat  is that  \ntest number\n\n  a\nafds  ";
	printf("Before strip3:%s\n\n",test3.c_str());
	#if __cplusplus >= 201103L	
	strip(test3);
	printf("\nAfter strip3:\"%s\"\n",test3.c_str());
	reverse(test3);
	printf("\nAfter reverse3:\"%s\"\n",test3.c_str());
	#else	
	printf("\nAfter strip3:\"%s\"\n",strip(test3).c_str());
	printf("\nAfter reverse3:\"%s\"\n",reverse(test3).c_str());
	#endif
	printf("\n\n--------------\n\n");
	
	
	std::string test4 = " this is a perfectly valid string that needs no editing ";
	printf("Before strip4:%s\n\n",test4.c_str());
	#if __cplusplus >= 201103L	
	strip(test4);
	printf("\nAfter strip4:\"%s\"\n",test4.c_str());
	reverse(test4);
	printf("\nAfter reverse4:\"%s\"\n",test4.c_str());
	#else	
	printf("\nAfter strip4:\"%s\"\n",strip(test4).c_str());
	printf("\nAfter reverse4:\"%s\"\n",reverse(test4).c_str());
	#endif
	printf("\n\n--------------\n\n");
	
	printf("Exiting...\n");
	return 0;
}


	

#if __cplusplus >= 201103L	
extern "C" void strip(std::string &str){
	if (str.empty()){
		printf("String is NULL\n");
    	return;
    }
	
	char *cInput = (char*)str.c_str();
	
    char *pr = cInput, *pw = cInput; //read ptr = str, write ptr = str
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
	printf("Result:%s\n",cInput);
}

extern "C" void reverse(std::string &str){
	if (str.c_str() == NULL){
		printf("String is NULL\n");
    	return;
    }
	
	char *cInput = (char*)str.c_str();
	
	
    char *pr = cInput, *pw = cInput; //read ptr = str, write ptr = str
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
	printf("Result:%s\n",cInput);
	
	printf("String Passed to Reverse:%s\n",cInput);
	char *str2 = cInput;
	printf("Test %s\n",str2);
	char *a = str2,*b = str2;
	char temp = 0;
	int len = 0;
	
	
	
	
	while(*str2){
		if (*str2 == ' '){
			//printf("Entered A with length:%i will do:%i iterations\n",len,len/2);
			b = str2-1;
			
			
			
			
			for (int i = 0; i < len/2; i++){
				//printf("String:%s\n",c);
				temp = *a;
				*a = *b;
				*b = temp;
				a++;
				b--;
			}
			
			
			
			
			len = 0;
			a = str2+1;
			str2++;
		}
		
		
		
		
		else{
			len++;
			str2++;
		}
	}
	
	printf("Result:%s\n",str.c_str());

}

#else
extern "C" std::string strip(std::string &str) {
	if (str.c_str() == NULL){
		printf("String is NULL\n");
    	return NULL;
    }
	
	char *cInput = (char*)malloc(str.size()+1);
	std::strcpy(cInput, str.c_str());
	
    char *pr = cInput, *pw = cInput; //read ptr = str, write ptr = str
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
	
	std::string result(cInput);
	free(cInput);
	return result;
}	

extern "C" std::string reverse(std::string &str){
	if (str.c_str() == NULL){
		printf("String is NULL\n");
    	return NULL;
    }
	
	char *cInput = (char*)malloc(str.size()+1);
	std::strcpy(cInput, str.c_str());
	
	
    char *pr = cInput, *pw = cInput; //read ptr = str, write ptr = str
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
	printf("Result:%s\n",cInput);
	
	printf("String Passed to Reverse:%s\n",cInput);
	char *str2 = cInput;
	printf("Test %s\n",str2);
	char *a = str2,*b = str2;
	char temp = 0;
	int len = 0;
	
	
	
	
	while(*str2){
		if (*str2 == ' '){
			//printf("Entered A with length:%i will do:%i iterations\n",len,len/2);
			b = str2-1;
			
			
			
			
			for (int i = 0; i < len/2; i++){
				//printf("String:%s\n",c);
				temp = *a;
				*a = *b;
				*b = temp;
				a++;
				b--;
			}
			
			
			
			
			len = 0;
			a = str2+1;
			str2++;
		}
		
		
		
		
		else{
			len++;
			str2++;
		}
	}
	
	std::string result(cInput);
	printf("Result:%s\n",result.c_str());
	free(cInput);
	return result;
}
#endif

