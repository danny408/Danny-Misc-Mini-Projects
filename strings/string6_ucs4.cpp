//6. Write a function that parses a UTF8 string and sorts characters by value, lowest to highest.
#include "string5.h"

#define MAX_ASCII 1114111

void utf8_sort(const char *byte);
//uint32_t* utf8_sort(const char *byte);
uint8_t indexCheck(uint32_t index);

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
	//const char *d = "abcdfwく郵行くとの封er234fs、ストに一通dfgsd";
	//should be E7A9A2
	//should be 1110 0111 1010 1001 1010 0010

	// int aaa = length(d);
	// printf("Length Should be 39:%u\n",aaa);
	//*/
	
	//uint32_t a = max_occurance("ȔabcȔȔ");
	//printf("Check2%lc\n",a);
	
	utf8_sort(d);
	return 0;
}

void utf8_sort(const char *byte){
//uint32_t* utf8_sort(const char *byte){
	uint32_t temp;
	char extract = 0;
	uint32_t *max = (uint32_t*)malloc(sizeof(uint32_t)*MAX_ASCII);
	printf("\n\n\nFinding Max Occurance...\n");


	while(*byte){
		temp = 0; // clear temp


		if(len_utf8(*byte) == 1){ // its a one byte char store the remaining 7 bits as the code point
			extract = *byte & 255; //extract the byte;
			temp = extract; // extract the 7 bits;			
			max[temp]++;
			byte++;
		}
		
		
		else if(len_utf8(*byte) == 2){ //header is 111xxxxx 2 bytes total
			extract = *byte & 31; // extract last 5 bits
			temp = extract;
			temp = temp << 6; // shift it over 6 for next continue bit
			byte++;
			
			extract = *byte & 63; // take last 6 bits of continuation byte
			//checks 6 bits put extracted 6 bits in 6 most least sig bits of this;
			for (int j = 5; j >= 0; j--){
				(extract & (1<<j)) ? temp |= (1 << j) : temp &= ~(1 << j); // sets the proper bit |= if extracted 1, else 0
			}


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
					//store temp somewhere to keep track of occurances
					max[temp]++;
				}
				byte++;
			}
			
		}
	
		else if(len_utf8(*byte) == 4){ //header is 11110xxx 4 bytes total  3+6+6+6
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

	}

	
	//Find which one was most occuring now
	uint32_t result;
	uint32_t occurance = 0;
	uint32_t i;

	for (i = 0; i < MAX_ASCII ; i++){
		if (max[i] >= occurance){
			result = i; // saves the index corresponding to the value
			occurance = max[i];
		}
	}

	//Cant get rid of these two lines or sorted output bugs out??? 
	printf("Index %i, UTF8 Code Point Hex: %08x\n",result,result);
	printf("Most Occuring Character:%lc\n",result);

	//Rest copied from string5 problem
	//Use the number of occurances to just throw everything in order (occurance) number of times then move on to next occurance
	uint32_t *sortedUTF8 = (uint32_t*)malloc(charLength(byte));
	uint32_t *iterate = sortedUTF8;
	for(i = 0; i < MAX_ASCII; i++){
		if (max[i] != 0){
			while(max[i] > 0){
				max[i]--;
				*iterate = i;
				iterate++;
			}
		}
	}


	printf("SortedString:%lu\n",(unsigned long)sortedUTF8);
	//return sortedUTF8; //4 byte retsult of the most occuring //could be void if u just wanna print it and not save it
}

uint8_t indexCheck(uint32_t index){
	if (index <= 127){
		return 1;
	}
	else if (index <= 2047){
		return 2;
	}
	else if (index <= 65535){
		return 3;
	}
	else{ //(index <= 1114111)
		return 4;
	} 
}