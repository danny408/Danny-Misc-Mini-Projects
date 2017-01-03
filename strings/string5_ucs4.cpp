	//5. Parse a UTF-8 string and identify the character which appears the most.

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_ASCII 1114111

#define USE_UCS4 1

//char * parse_utf8(char *string);
uint32_t length(const char *byte);
int len_utf8(const unsigned char byte);


uint32_t max_occurance(const char *byte);


int main(void){	
	setlocale(LC_ALL,"");
	///* Test Stuff
	//const char *b = "穢翼のユースティア";
	// int a = length(b);
	// printf("Length Should be 27:%u\n",a);
	
	//int uint32_t = max_occurance(b);
	
	//const char *c = " nodvd patch";
	//int aa = length(c);
	//printf("Length Should be 12:%u\n",aa);
	
	//int uint32_t = max_occurance(c);

	const char *d = "家の前に止まったバイクの音に、おそらく郵便だろうと思って出て行くと、案の定ポストに一通の封書が届けられていた。";
	//const char *d = "穢";
	//const char *d = "ȔabcȔȔ";
	//should be E7A9A2
	//should be 1110 0111 1010 1001 1010 0010

	// int aaa = length(d);
	// printf("Length Should be 39:%u\n",aaa);
	//*/
	
	//uint32_t a = max_occurance("ȔabcȔȔ");
	//printf("Check2%lc\n",a);
	uint32_t a = max_occurance(d);
	printf("Check2:%lc\n",a);
	return 0;
}


uint32_t length(const char *byte){ //assumes the utf8 string is valid
	int len = 0;
	
	while(*byte){
		printf("Byte:%i--",*byte);
		printf("%i--",len_utf8(*byte));
		if(len_utf8(*byte) == 1){
			printf("1\n");
			len++;
			byte++;
		}
		

		
		else if(len_utf8(*byte) == 2){ 
			printf("2\n");
			len+=2;
			byte+=2;
		}
		
		
		else if(len_utf8(*byte) == 3){
			printf("3\n");
			len+=3;
			byte+=3;
		}
		
		
		else if(len_utf8(*byte) == 4){
			printf("4\n");
			len+=4;
			byte+=4;
		}
		
		
		else if(len_utf8(*byte) == 5){
			printf("5\n");
			len+=5;
			byte+=5;
		}
		
		
		else{
			printf("6\n");
			len+=6;
			byte+=6;
		}
		
		
	}
	return len;
}

int len_utf8(const unsigned char byte){
	
	if (byte < 192){
		return 1;
	}
	
	
	else if (byte < 224){
		return 2;
	}
	
	
	else if (byte < 240){
		return 3;
	}
	
	
	else if (byte < 248){
		return 4;
	}
	
	
	else if (byte < 252){
		return 5;
	}
	
	
	else {
		return 6;
	}
}

uint32_t max_occurance(const char *byte){
	uint32_t temp;
	char extract = 0;
	unsigned int max[MAX_ASCII] = {0};
	printf("\n\n\nFinding Max Occurance...\n");


	while(*byte){
		temp = 0; // clear temp

		if(len_utf8(*byte) == 1){ // its a one byte char store the remaining 7 bits as the code point
			printf("1\n");
			extract = *byte & 255; //extract the byte;
			temp = extract; // extract the 7 bits;			
			printf("The Code Segment of this unicode char is:%08x\n",temp);
			max[temp]++;
			byte++;
		}
		
		
		else if(len_utf8(*byte) == 2){ //header is 111xxxxx 2 bytes total
			printf("2\n");
			extract = *byte & 31; // extract last 5 bits
			temp = extract;
			temp = temp << 6; // shift it over 6 for next continue bit
			byte++;
			
			extract = *byte & 63; // take last 6 bits of continuation byte
			//checks 6 bits put extracted 6 bits in 6 most least sig bits of this;
			for (int j = 5; j >= 0; j--){
				(extract & (1<<j)) ? temp |= (1 << j) : temp &= ~(1 << j); // sets the proper bit |= if extracted 1, else 0
			}


			printf("The Code Segment of this unicode char is:%08x\n",temp);
			max[temp]++;
			byte++;
		}
		
		
		else if(len_utf8(*byte) == 3){ //header is 1110xxxx 3 bytes total  4+6+6
			extract = *byte & 15; //extract last 4 bits
			temp = extract;
			temp = temp << 6; // shift it over 6 for next continue bit
			byte++;


			for (int i = 2; i >= 1; i--){
				extract = 0;
				extract = *byte & 63; // take last 6 bits of continuation byte
				//checks 6 bits put extracted 6 bits in 6 most least sig bits of this;


				for (int j = 5; j >= 0; j--){
					(extract & (1<<j)) ? temp |= (1 << j) : temp &= ~(1 << j); // sets the proper bit |= if extracted 1, else 0
				}


				if (i != 1){
					temp = temp << 6;
				}


				if (i == 1){
					printf("The Code Segment of this unicode char is:%08x\n",temp);
					//store temp somewhere to keep track of occurances
					max[temp]++;
				}
				byte++;
			}
			
		}
	
		else if(len_utf8(*byte) == 4){ //header is 11110xxx 4 bytes total  3+6+6+6
			printf("4\n");
			extract = *byte & 7; //extract last 3 bits
			temp = extract;
			temp = temp << 6; // shift it over 6 for next continue bit
			byte++;
			

			for (int i = 3; i >= 1; i--){
				extract = *byte & 63; // take last 6 bits of continuation byte
				//checks 6 bits put extracted 6 bits in 6 most least sig bits of this;


				for (int j = 5; j >= 0; j--){
					(extract & (1<<j)) ? temp |= (1 << j) : temp &= ~(1 << j); // sets the proper bit |= if extracted 1, else 0
				}


				if (i != 1){
					temp = temp << 6;
				}


				if (i == 1){
					printf("The Code Segment of this unicode char is:%08x\n",temp);
					max[temp]++;
				}
				byte++;
			}			
		}
		
		
		else if(len_utf8(*byte) == 5){ //shouldnt happen for now
			printf("5 shouldnt happen for now\n");
			//same pattern as above
		}
		
		
		else{ //shouldnt happen for now
			printf("6 shouldnt happen for now\n");
			//same pattern as above
		}
		printf("One Char Processed\n\n");
	}

	#if USE_UCS4
	printf("Hello1\n");
	//Find which one was most occuring now
	uint32_t result;
	uint32_t occurance = 0;


	for (uint32_t i = 0; i < MAX_ASCII ; i++){
		if (max[i] >= occurance){
			result = i; // saves the index corresponding to the value
			occurance = max[i];
		}
	}


	printf("Index %i, UTF8 Code Point Hex: %08x\n",result,result);
	printf("Most Occuring Character:%lc\n",result);
	return result; //4 byte retsult of the most occuring //could be void if u just wanna print it and not save it
	#else
	printf("Hello2\n");
	#endif

}