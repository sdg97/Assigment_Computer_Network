#include <ctype.h>

void printData(char *str, size_t numBytes){
	for(int i = 0; i < numBytes; i++){
	printf("%c", str[i]);
	}
	printf("\n");
}

size_t countStrLen(char *str){
	size_t c = 0;
	while(*str != '\0'){
		c += 1;
		str++;
	}
	return c;
}
