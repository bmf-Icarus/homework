/**
* build algorithm from pseudocode given "Collatz"
*
* Completion time: (estimation of hours spent on this program)
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

	int num, ans;

	printf("Give me an integer please: ");
	scanf("%d\n", &num);	
	ans = termination(num);
	printf("Given integer was terminated %d times!\n", ans);

	return 0;
}


int termination(int n){
	int i=0;
	while(n != 1){
		printf("while loop\n");
		if(!(n % 2)){
			printf("n is %d\n", n);
			n = n/2;
		}else{
			printf("n is %d\n", n);
			n = (3*n)+1;
		}
	
		i++;

	}
	return i;
}
