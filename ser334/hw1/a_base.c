/**
* (basic description of the program or class)
*
* Completion time: (estimation of hours spent on this program)
*
* @author (your name), (anyone else, e.g., Acuna, whose code you used)
* @version (a version number or a date)
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int main(void)
{
	int multi_array[2][6] = {{10000, 2, 3, 9, 10, 10}, {7, 8, 9, 9, 1999, 0}};
	int size = sizeof(multi_array);
	printf("%d",size);
	//Add a prompt for the number of cylinders to sum. Make sure to use the control
	//symbol for integers. [2 points]

	//Create a loop based on the number of cylinders the user enters. [2 points]

	//    Within the loop, prompt for height and radius parameters (allow floating
	//    point numbers), and calculate the volume for that particular cylinder.
	//    [4 points]

	//Display the total volume sum back to the user. Make sure to use the right control
	//symbol. [2 points]

	return 0;
}
