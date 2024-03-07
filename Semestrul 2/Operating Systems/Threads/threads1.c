#include <stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<time.h>

void* roll_dice(){
	int value = (rand() % 6 ) + 1;
	int *res = malloc(sizeof(int));
	*res=value;
	return (void *) res;
}

int main(int argc,char* argv[]){
	int * res;
	srand(time(NULL));
	pthread_t th[4];
	for(int i =0;i<4;i++){
		if(pthread_create(th + i, NULL, &roll_dice, NULL) !=0)
		{	return 1;
		}
	}
	for(int i=0;i<4;i++){
		if(pthread_join(th[i],(void**) &res)!=0){
			return 2;}
		printf("Dice is : %d \n",* res);
	}
	free(res);
	return 0;

}
