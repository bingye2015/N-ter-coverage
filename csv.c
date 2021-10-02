/* this is a program for .csv */
#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

char * buffer;
int size;

int main()
{
	FILE * result;
	
	result = fopen ("result.csv","rt");
	if (result == NULL) { printf("can not open the result.csv\n");
		return ERROR;
	}

	fseek(result,0L,SEEK_END);
	size = ftell(result);
	rewind(result);
	printf("the size of result is %d.\n",size);
	buffer = (char *)malloc(size - 1);
	if (buffer == NULL) return ERROR;
	fread(buffer,size-1, 1, result);
	printf("%s\n",buffer);

	free(buffer);

	fclose(result);
	
	return 0;
}

