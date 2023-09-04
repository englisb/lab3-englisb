#include <stdio.h>
#include <stdlib.h>

#include "Questions.h"



char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	
	/*write your implementation here*/

	int str1Index;
	int str2Index;

	//the pointer z points to memory allocated to contain the length of str1,2, plus a null character to end the string
	z = (char*)calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));

	//the contents of str1 are inserted into the memory allocated for it with a loop iterating through each address and character entry
	for(str1Index = 0; str1Index < strlen(str1); str1Index++){
		z[str1Index] = str1[str1Index];
	}

	//picking up at the memory address after where the final character of str1 is,
	//the contents of str2 are inserted into the memory allocated for it with a loop iterating through each address and character entry
	for(str2Index = 0; str2Index < strlen(str2); str1Index++, str2Index++){
		z[str1Index] = str2[str2Index];
	}

	/* finally, return the string*/
	return z;
	
}
