#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int primes[10]={1, 2 ,3,4,5,6,7,8,9,10};

void* routine(void* arg){
	int number=*(int*)arg;
	printf("%d ", number);
	
}

int main(int argc, char* argv[]){
	pthread_t th[10];
	int i =0;
	for(i=0;i<10;i++){
		if(pthread_create(&th[i],NULL,&routine,primes + i)!=0){
			return 1;
				}
	}
	for(i=0;i<10;i++){
		if(pthread_join(th[i],NULL)!=0){
			perror("Joining threads");
		}
	}
return 0;

}
