//6. Write a function that parses a UTF8 string and sorts characters by value, lowest to highest.
#include "string5.h"
#include <inttypes.h>

#define MAX_ASCII 1114111

void utf8_sort(const char *byte);
//uint32_t* utf8_sort(const char *byte);
uint8_t indexCheck(uint32_t index);

int main(void){	
	setlocale(LC_ALL,"");
	const char *d = "家族はみんな出掛けていて、家には自分一人。\
何をするでもなく、ただぼんやりと外の景色を見て過ごしていた日……。\
家の前に止まったバイクの音に、おそらく郵便だろうと思って出て行くと、案の定ポストに一通の封書が届けられていた。\
―入学案内……？\
『こが久我みちる満琉様』\
確かに自分宛だった。\
でも差出人である学園の名前にはまるで心当たりがない。\
首を傾げながらも、封を切ってみる。\
『私立天秤瑠璃学園』\
『LibraLapisLazuli』と記されたマークが表紙に印刷されている、学園の校舎らしき建物を写したパンフレット。\
入学手続きのための書類。\
一見普通の案内書のようだけど……。\
―これは……？\
書類の間に、小さく折りたたまれた手紙が差し込まれている。\
『あなたの叶えたい望みはなんですか』\
望み――ふと兄の顔が脳裏をよぎる。\
他に望みなんて無い。\
何故なら、自分のせいで今も病院に……\
―あっ……\
ふわりと、いい匂いが鼻先をくすぐったと思うと、手紙からあふれ出した淡い光が青い鳥に姿を変えた。\
青い鳥たちはくるり、くるりと頭上で弧を描く。\
…。\
そして、やがて遠い空の向こうへと飛び去って行った……。\
―望み………\
叶えてくれる、とでも言うのだろうか。\
あの鳥たちは望みが心に浮かんだ途端、それに応えるように現れたように見えた。\
そうであって欲しい、という、それは幻想だったのかもしれない。\
だけど……。\
―この学園に行けば……本当に……？\
…すがってみたかった。\
本当だったら、もし本当に叶えてくれると言うのだったら。\
―……どこにだって行く。\
もう一度空を見上げてみたけれど、鳥たちの姿は空の向こうに溶けるように消えていた。\
満琉「……あれ、あった」\
その学園は、唐突に姿を現した。";
	utf8_sort(d);
	return 0;
}

void utf8_sort(const char *byte){
//uint32_t* utf8_sort(const char *byte){
	uint32_t temp;
	char extract = 0;
	uint32_t *max = (uint32_t*)calloc(MAX_ASCII,sizeof(uint32_t));
	printf("\n\n\nFinding Max Occurance...\n");
	uint32_t cLen = charLength(byte);
	
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

	
	int abc = 0;
	for (i = 0; i < MAX_ASCII ; i++){
		if (max[i] != 0){
			abc += max[i];
		}
	}
	printf("Total Chars %i\n",abc);
	
	//Use the number of occurances to just throw everything in order (occurance) number of times then move on to next occurance
	uint32_t *sortedUTF8 = (uint32_t*)malloc((cLen+1) * sizeof(uint32_t));
	printf("CharLength:%i\n",cLen);

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
	++*iterate = '\0';


	printf("SortedString:%ls\n", (wchar_t*)sortedUTF8);
	free(max);
	free(sortedUTF8);
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
