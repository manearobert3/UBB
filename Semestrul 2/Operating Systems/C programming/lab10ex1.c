#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>



int main()
{
	FILE* fptr;
	int matrix1[100][100],n;
	int row=0,col=0;
	fptr=fopen("a.txt","r");
	char string[100];
	while(fgets(string,sizeof(string),fptr)){
		int number;
		char* str;
		col=0;
		str=strtok(string," ");
		if(str!=NULL){
			n=atoi(str);
			str=strtok(NULL," ");
		if((n==0) && (str==NULL))
			break;
		}
		while(str!=NULL){
			number=atoi(str);
			str=strtok(NULL," ");
			if((number==0) && (str==NULL))
				break;
			else
			{	matrix1[row][col]=number;
				col=col+1;}
		}row=row+1;
	}
	fclose(fptr);
	printf("%d %d %d \n",n,row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			printf("%d ",matrix1[i][j]);
		}
	printf("\n");
	
	}}
