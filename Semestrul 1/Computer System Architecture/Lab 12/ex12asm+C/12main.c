#include <stdio.h>

//Two strings of characters of equal length are given. 
//Calculate and display the results of the interleaving of the letters, 
//for the two possible interlaces (the letters of the first string in an even position, 
//respectively the letters from the first string in an odd positions)
int modul(int lensir, char D[], char sir[]);
int modul1(int lensir, char D[], char sir[]);
int main()
{   char D[100]={0};
    char sir[100]="abcd";
    char sir2[100]="efgh";
    int length; 
    int length2;
    length = str_length(sir); 
    length2 = str_length(sir2);
    D = modul(length, D, sir);
    printf("Sirul :\n");
    for(int i = 0; i < length; i++)
        printf("%d ", D[i]);
    printf("\n");
    
    D = modul1(length, D, sir2);
    printf("Sirul :\n");
    for(int i = 0; i < length; i++)
        printf("%d ", D[i]);
    printf("\n");


    D = modul1(length, D, sir);
    D = modul(length, D, sir2);
    printf("Sirul :\n");
    for(int i = 0; i < length; i++)
        printf("%d ", D[i]);
    printf("\n");
    
    return 0;
}