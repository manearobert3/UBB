#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void f(int n){
	if(n>0 && fork()==0){
		if(n%2==0){
			fork();
		}
		printf("123%d\n",getpid());
		f(n-1);
		exit(0);
	}
	wait(0);wait(0);
}

int main(){
f(3);
printf("123%d\n",getpid());
//	f(3);}
}
