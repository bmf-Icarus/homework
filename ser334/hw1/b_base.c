/**
* discription of program here
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

int main(void)
{
	int cNum, i=0;
 	float hei, rad, vol, tVol=0;
	//Add a prompt for the number of cylinders to sum. Make sure to use the control
	//symbol for integers. [2 points]

	printf("how many cylinders to sum? ");
	scanf("%d", &cNum);
	
	//Create a loop based on the number of cylinders the user enters. [2 points]
	while(i<cNum){
		//    Within the loop, prompt for height and radius parameters (allow floating
		//    point numbers), and calculate the volume for that particular cylinder.
		//    [4 points]
	
		printf("height of cylinder: \n");
		scanf("%f", &hei);
		printf("radius of cylinder: \n");
		scanf("%f", &rad);
		vol = 3.14159 * rad * rad * hei;
		tVol += vol;
		i++;
	}
	//Display the total volume sum back to the user. Make sure to use the right control
	//symbol. [2 points]
	printf("total volume of cylinder(s): %f\n", tVol);

	return 0;
}
