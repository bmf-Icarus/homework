#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	FILE *fp;
	char *line = NULL;
	char *end = NULL;
	int pInfo[2];
	int order[2];
	int count = 0;
	int wTime = 0;
	int eError = 0;
	double clock = 0;
	size_t len = 0;
	ssize_t read;

	//open file and read-in data
	fp = fopen(argv[1], "r");
	//the first two elements describe the
	// following data
	for( int i=0; i<2; i++){
		getline(&line, &len, fp);
		pInfo[i]= atoi(line);
	}
	//make a 2d array of processes and their data
	double **rey;
	rey = malloc(sizeof(int)*pInfo[1]);
	//populate array	
	for(int j=0; j<pInfo[1]; j++){	
		rey[j] = malloc((sizeof(double)*(pInfo[0]+2)));
		for( int i=0; i<3+pInfo[0]; i++){
			getline(&line, &len, fp);
			rey[j][i] = strtod(line,&end);
			//printf("j=%d i=%d cpuT=%lf\n",j,i,rey[j][i]);
		}
	}
	fclose(fp);
	free(line);

	//shortest job first
	printf("++Shortest_Job_First++\n");
	while(count < pInfo[0]){
		// compares the runtime of both processes to determine order
		if((int)rey[0][count+3]<(int)rey[1][count+3]){
			order[0] = 0;
			order[1] = 1;
		}else{
			order[0] = 1;
			order[1] = 0;
		}

		printf("Simulating round %d of processes @ time %3.0lf:\n", count+1, clock);
		printf("  process %d took %d\n", order[0], (int)rey[order[0]][count+3] );	
		wTime += (int)rey[order[0]][count+3];
		clock += rey[order[0]][count+3];
		printf("  process %d took %d\n", order[1], (int)rey[order[1]][count+3] );	
		clock += rey[order[1]][count+3];

		count++;
	}
	
	printf("Turnaround Time: %d\n", ((int)clock+wTime));
	printf("Waiting Time: %d\n", wTime);


	//shortest job first live
	printf("\n\n++Shortest_Job_First_Live++\n");
	count=0,clock=0,wTime=0;
	while(count < pInfo[0]){
		// compares the tau of each process to determine which runs first
		if(rey[0][1]<=rey[1][1]){
			order[0] = 0;
			order[1] = 1;
		}else{
			order[0] = 1;
			order[1] = 0;
		}

		printf("Simulating round %d of processes @ time %3.0lf:\n", count+1, clock);

		printf("  process %d was estimated for %d and took %d\n"
		, order[0], (int)rey[order[0]][1], (int)rey[order[0]][count+3] );	
		eError += abs(rey[order[0]][1] - rey[order[0]][count+3]);
		rey[order[0]][1] = (int)((rey[order[0]][1] + rey[order[0]][count+3]) / 2);
		wTime += (int)rey[order[0]][count+3];
		clock += rey[order[0]][count+3];

		printf("  process %d was estimated for %d and took %d\n"
		, order[1], (int)rey[order[1]][1], (int)rey[order[1]][count+3] );	
		eError += abs(rey[order[1]][1] - rey[order[1]][count+3]);
		rey[order[1]][1] = (int)((rey[order[1]][1] + rey[order[1]][count+3]) / 2);
		clock += rey[order[1]][count+3];

		count++;
	}
	
	printf("Turnaround Time: %d\n", ((int)clock+wTime));
	printf("Waiting Time: %d\n", wTime);
	printf("Estimation Error: %d\n", eError);
	free(rey);
	return 0;
}
