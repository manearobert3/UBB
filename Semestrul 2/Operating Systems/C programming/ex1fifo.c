#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
int main(int argc, char* argv[]){
	int fd;
//	fd=open("myfifo",O_WRONLY);
	int arr[5];
	srand(time(NULL));
	int i;
	for(i=0;i<5;i++){
	arr[i]=rand() % 10;
	printf("Generated %d\n",arr[i]);
	}
	fd=open("myfifo",O_WRONLY);
	if(fd==-1)
		return 1;
	if(write(fd,arr,sizeof(int) * 5)==-1){
		return 2;
	}
	close(fd);
	int sum;
	fd=open("myfifo",O_RDONLY);
	if(read(fd,&sum,sizeof(int))==-1)
		return 2;
	close(fd);
	printf("the sum is : %d\n",sum);
	return 0;
}
