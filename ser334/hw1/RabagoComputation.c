/**
* compute the volume for a # of cylinders and total volume
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

#define PI 3.14159

int main(void)
{
	int num, i=0;
 	float hei, rad, vol, tVol=0;

	printf("how many cylinders to sum? ");
	scanf("%d", &num);
	
	while(i<num){		//loops for the # of cylinders
	
		printf("height of cylinder: ");
		scanf("%f", &hei);
		printf("radius of cylinder: ");
		scanf("%f", &rad);

		vol = PI * rad * rad * hei; 	//formula for calulating
						//area of cylinder
		printf("volume of cylinder: %f\n", vol);

		tVol += vol;			//keep running total vol
		i++;
	}

	printf("total volume of cylinder(s): %f\n", tVol);

	return 0;
}
