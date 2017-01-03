/*3. Write a function which finds the length of a file without counting bytes and returns a pointer with the file included. 
There must be a length output to this function so binary data is supported.
Normally you'd just make certain functions available or unavailable instead of changing their arguments. 
Probably worth saying. From now on, any library function you write should declare extern "C" if the compiler is a c++ compiler. 
Figure out why this is important (or not). Consider starting a "danny library" so you can reuse useful code. 
#3 is exceptionally useful for future problems. UTF8 code may be useful as well. */

// Using Extern "C" in a cpp source folder to not mangle the name
#include <sys/stat.h>
#include <stdio.h>

extern "C" FILE* fileLen(const char* fileName);


int main(void){
	printf("Enter a file name to open\n");
	char fileName[100];
	scanf("%s",fileName);
	FILE *fp;
	fp = fileLen(fileName);
	fclose(fp);
	return 0;
}


extern "C" FILE* fileLen(const char* fileName){
FILE *fp;
	printf("Trying to open:%s\n",fileName);
	fp = fopen(fileName,"rb+");
	
	
	if (!fp){
		printf("Error File Does Not Exist!\n");
	}
	
	
	int fd = fileno(fp);
	if (!fd){
		printf("Error\n");
	}
	
	
	#ifdef _WIN32
	long len = _filelength(fd);
	printf("File Length %zu\n",len);
	
	
	#elif __unix__
	struct stat info;
	fstat(fd, &info);
	printf("File Length %zu\n",info.st_size);
	
	
	#else
		#error "Unknown Compler"
	#endif
	
	
	return fp;
}
