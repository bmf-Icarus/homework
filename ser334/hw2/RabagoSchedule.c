////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS



////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
enum Subject { SER = 0, EGR = 1, CSE = 2, EEE = 3 };
struct Course{
	enum Subject mySubject;
	int subjectNum;
	char instructor[1024];
	int credits;

};

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

//number of courses in the collection. also the index of the next empty element.
int courseCount = 0;

//place to store course information
struct Course *CourseCollection = NULL;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);
void course_info();
void course_insert();
void schedule_print();
void course_drop(); 

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {
	char input_buffer;
	printf("\n\nWelcome to ASU Class Schedule\n");

	//menu and input loop
	do {
		printf("\nMenu Options\n");
		printf("------------------------------------------------------\n");
		printf("a: Add a class\n");
		printf("d: Drop a class\n");
		printf("s: Show your classes\n");
		printf("q: Quit\n");
		//printf("\nTotal Credits: %d\n\n", TODO);
		printf("Please enter a choice ---> ");

		scanf(" %c", &input_buffer);

		branching(input_buffer);
	} while (input_buffer != 'q');
	
	free(CourseCollection);
	return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
	switch (option) {
	case 'a':
		course_info();
		break;

	case 'd':
		course_drop();
		break;

	case 's':
		schedule_print();
		break;

	case 'q':
		// main loop will take care of this.
		break;

	default:
		printf("\nError: Invalid Input.  Please try again...");
		break;
	}
}

void course_info(){
	struct Course temp;
	//strcpy(temp.instructor, "");
	memset(temp.instructor,0, sizeof(temp.instructor));
	printf("\nWhat is the subject? ex. SER = 0, EGR = 1, CSE = 2, EEE = 3\n");
	scanf("%u", &temp.mySubject);
	printf("What is the course number? ex. 101\n");
	scanf("%d", &temp.subjectNum);
	printf("What is the name of the instructor?\n");
	scanf("%s", temp.instructor);	
	printf("What is the number of credit hours?\n");
	scanf("%d", &temp.credits);
	
	course_insert(temp);
}
void course_insert(struct Course input){
	courseCount++;
	int x = 0;
	if(courseCount == 1) {
		CourseCollection = (struct Course*) malloc(sizeof(struct Course));
		CourseCollection[0] = input;
	}
	else {
		//printf("list size : %lu\n\n", sizeof(struct Course));
		struct Course * newCourseCollection = (struct Course*)malloc(sizeof(struct Course) * (courseCount));
		for(int i = 0,j = 0; i < courseCount - 1; i++){
			if( x || input.subjectNum < CourseCollection[j].subjectNum ){
				newCourseCollection[j] = input;
				i++;
				x++;
			}

			newCourseCollection[i] = CourseCollection[j];

			j++;
		}
		free(CourseCollection);
		CourseCollection = (struct Course *)malloc(sizeof(struct Course) * (courseCount));
		CourseCollection = newCourseCollection;
		free(newCourseCollection);
		newCourseCollection = NULL;
	}

}	
void schedule_print(){
	printf("\n\nClass Schedule\nCourse\tCredits\tInstructor\n");
	for(int i=0; i<courseCount; i++) {
		if(CourseCollection[i].mySubject % 4 == 0)
			printf("SER");
		else if(CourseCollection[i].mySubject % 4 == 1)
			printf("EGR");
		else if(CourseCollection[i].mySubject % 4 == 2)
			printf("CSE");
		else if(CourseCollection[i].mySubject % 4 == 3)
			printf("EEE");
		printf("%d\t%d\t%s\n",CourseCollection[i].subjectNum,
		CourseCollection[i].credits,CourseCollection[i].instructor);
	}
}
void course_drop(){

}
