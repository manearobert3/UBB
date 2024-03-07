#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
	int fd;
	int arr[5];
	fd=open("myfifo",O_RDONLY);
	printf("Opened file\n");
	if(fd==-1)
		return 1;
	printf("verified fd\n");
	if(read(fd,arr,sizeof(int) * 5)==-1)
	return 2;
	close(fd);
	printf("Did the fd read\n");
	int sum=0;
	for(int i=0;i<5;i++)
		sum=sum+arr[i];
	printf("The sum is %d\n",sum);

	fd=open("myfifo",O_WRONLY);
	if(write(fd,&sum,sizeof(int))==-1)
		return 3;
	return 0;

}
