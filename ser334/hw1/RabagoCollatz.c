/**
* build algorithm from pseudocode given "Collatz"
*
* Completion time: 0.5hr
*
* @author JJ Rabago Jr 
* @version 1.1.22
*
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int termination(int n);

int main(void){

	int num;

	printf("Give me an integer please: ");
	scanf("%d", &num);	
	printf("Given integer was terminated %d times!\n", termination(num));

	return 0;
}


int termination(int n){
	int i=0;			//init counter
	while(n != 1){			//check if argument is 1
		if(!(n % 2))		//check if argument is even
			n /= 2;
		else
			n = (3*n)+1;
	
		i++;			//keep track of loops

	}
	return i;
}
