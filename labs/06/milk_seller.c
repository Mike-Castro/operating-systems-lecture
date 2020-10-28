//Miguel Angel Castro Martinez
//A01283439
//Milk seller

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

int totBottles = 1000;
int bSold = 0;
int seller[5];
int sellers = 5;
int randomB[5]; 

bool b[6] = {false, false, false, false, false, false};
pthread_mutex_t mutex;

void bottlesSold(intptr_t *t_id){
	intptr_t t_id1 = (intptr_t)t_id;
	
	int sell = t_id1;
	for(int i=1; i<6 || b[sell]!=true; i++){
		if(randomB[i-1] + seller[sell] <= 200 && randomB[i-1] != 0){
			seller[sell] += randomB[i-1];
			bSold += randomB[i-1];
			randomB[i-1]=0;
			printf("Seller: %d sold %d bottles \n", sell, seller[sell]);
			b[sell] = true;
			break;
		}
		b[sell] = true;
	}
}

void *threadFunc(void *i){
	intptr_t t_id = (intptr_t) i;
	pthread_mutex_lock(&mutex);

	if(bSold < 1000 && b[t_id]==false){
		bottlesSold((intptr_t *)t_id);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}


void randomNumber(){
	for(int i=0; i<5; i++){
		randomB[i] = (rand()%(200)+1);
	}
}

int main(void){
	pthread_mutex_init(&mutex, NULL);
	srand(time(0));
	
	for(int i=0; i<5; i++){
		randomNumber();
		b[1]=false, b[2]=false, b[3]=false, b[4]=false, b[5]=false;
		pthread_t threads[sellers];
		
		for(int j=0; j<sellers; j++){
			pthread_create(&threads[j],NULL,threadFunc,(void *)(intptr_t)(j+1));	
		}
		for(int j=0; j<sellers; j++){
			pthread_join(threads[j],NULL);
		}
	}
	printf("Results \n");
	for(int i=0; i<sellers; i++){
		printf("The seller %d sold %d bottles \n", i+1, seller[i+1]);
	}
	
	printf("The total bottles sold of the day is %d \n", bSold);
}
