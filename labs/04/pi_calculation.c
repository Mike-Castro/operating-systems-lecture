/**
*
* Miguel Angel Castro Martinez
* A01283439
*
* Pi Calculation
*
* Link grafica:
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#define SEED 42

int philos;

void *monteC(void *t_id){
	double x,y,z;
	int *cont = (int *)malloc(sizeof(int));
	*cont = 0;
	srand(SEED);

	for(int i=0; i<philos; i++){
		x=(double)rand()/((double)(unsigned) RAND_MAX+1);
		y=(double)rand()/((double)(unsigned) RAND_MAX+1);
		z=(x*x + y*y);

		if(z <= 1){
			*cont +=1;
		}
	}
	
	pthread_exit((void *) cont);
}

int main(int argc, char* argv[]){
	int npoints = 10000;
	int nhilos;
	clock_t start, end;
	double cpu_time_used;
	int d;
	double pi;
	start = clock();

	nhilos = atoi(argv[1]);	

	pthread_t hilos[nhilos];
	philos = npoints / nhilos;
	for(int i=0; i<nhilos; i++){
		if(pthread_create(&hilos[i], NULL, monteC, (void *)(intptr_t) i)){
			printf("Error in threads \n ");
			return 1;
		}
	}

	void *ptshilo;

	for(int i=0; i<nhilos; i++){
		pthread_join(hilos[i], &ptshilo);
		d += *(long *)ptshilo;
	}

	pi=(4.00*(double)d) / ((double)philos * nhilos);

	printf("El valor de Pi es %f \n", pi);

	end = clock();
	cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;
	printf("Time is %.4f\n", cpu_time_used);


	return 0;
}
