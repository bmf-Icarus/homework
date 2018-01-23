/**
* utilize bit manipulation to decrypt message
*
* Completion time: 1hr
*
* @author JJ Rabago Jr, Prof Acuna(base code)
* @version 1.1.23
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <string.h>

//macros: constants
#define CHUNK_LENGTH (20+1)  	//each chunk has twenty characters, we add 1 so
                           	//there is space for the null terminator.
#define NUMBER_OF_CHUNKS 4 	//the message is spread across 4 chunks.
#define DECRYPTION_SHIFT 5 	//this is the ASCII table shift used for decryption.

//forward declarations
void sort_chunks();
void decrypt_chunks();
void display_chunks();

char chunks[NUMBER_OF_CHUNKS][CHUNK_LENGTH];
char *ptr;

int main() {

	strcpy(chunks[0], "2i1%fsi%fs%jstwrtzx%");
	strcpy(chunks[1], "1'H%nx%vznwp~1%kqf|j");
	strcpy(chunks[2], "4R3%Wnyhmnj%%%%%%%%%");
	strcpy(chunks[3], "3xzhhjxx3'%2%Ijssnx%");

	sort_chunks();

	decrypt_chunks();

	display_chunks();

	return 0; 
}

//given two strings, swaps their contents in memory.
void swap_strings(char* x, char* y) {
	//create a temporary holding place for the data so we don't lose it.

	char temp[CHUNK_LENGTH];

	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

//sorts the strings the global chunks variable by the first character they contain.
void sort_chunks() {

	for(int i=0;i<NUMBER_OF_CHUNKS;i++){
		for(int j=i+1;j<NUMBER_OF_CHUNKS;j++){ 
			if(chunks[i][0] > chunks[j][0])
				swap_strings(chunks[i],chunks[j]);
		}
	}
}

//for each string in the global chunks variable, shifts the characters in it by
//DECRYPTION_SHIFT.
void decrypt_chunks() {

	for(int i=0;i<NUMBER_OF_CHUNKS;i++){
		ptr=chunks[i];
		for(int j=0;j<CHUNK_LENGTH-2;j++){
			ptr++;
			*ptr-=DECRYPTION_SHIFT; 
		}	
	}
}


//displays the strings in the global chunks variable
void display_chunks() {

	for(int i=0;i<NUMBER_OF_CHUNKS;i++){
		ptr=chunks[i];
		for(int j=0;j<CHUNK_LENGTH-1;j++){
			ptr++;
			printf("%c",*ptr);		
		}	
	}
	printf("\n");
}
