#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

int main(int argc, char* argv[]){
	int arr[]={1,2,3,4,5,6,7};
	int arrSize= sizeof(arr)/sizeof(int);
	int fd[2],fd1[2];
	if(pipe(fd)==-1|| pipe(fd1)==-1){
	return 1;
	}
	int totalSum=0;
	int start=arrSize/3;
	int mid=(arrSize-arrSize/3);
	int first;
	int id=fork();
	int id2;
	int n;
	if(id==0)
	{	first=0;
		n=start;
		
	}
	else
	{	id2=fork();
		if(id2==0){                   
		first=start;
		n=mid;
		    }
		else{first=mid;
		n=arrSize;}
	}
	for(int i=first;i<n;i++){
		totalSum=totalSum+arr[i];
	}
	printf("The sum is: %d\n",totalSum);
	if(id==0){
		close(fd[0]);
		if(write(fd[1],&totalSum,sizeof(int))==-1)
			return 2;
		close(fd[1]);
	}
	else 
	{	if(id2==0){ 
		close(fd1[0]);
   		if(write(fd1[1],&totalSum,sizeof(int))==-1)
			 return 3;
		close(fd1[1]);
		}
		else{
		close(fd[1]);
		close(fd1[1]);
		int sumParent;
		if(read(fd[0],&sumParent,sizeof(int))==-1)
			return 4;
		printf("sum from child %d\n",sumParent);	
		totalSum=totalSum+sumParent;
		if(read(fd1[0],&sumParent,sizeof(int))==-1)
			return 5;
		totalSum=totalSum+sumParent;
		close(fd[0]);
		close(fd1[0]);
		wait(NULL);
		printf("Total from parent sum is : %d\n",totalSum);
		wait(NULL);}
	}
}

