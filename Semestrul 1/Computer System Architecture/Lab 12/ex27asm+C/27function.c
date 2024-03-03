#include <stdio.h>

// Read a sentence from the keyboard containing different characters 
//(lowercase letters, big letters, numbers, special ones, etc). 
//Obtain a new string with only the small case letters and another 
//string with only the big case letters. Print both strings on the screen.
int modul(int lensir, char mici[], char sir[]);
int modul1(int lensir, char mari[], char sir[]);
int main()
{   char mici[100]={0};
    char mari[100]={0};
    char sir[100]="vasbDFD2Aa";
    int length; 
    length = str_length(sir); 
    mici = modul(length, mici, sir);
    printf("Sirul :\n");
    for(int i = 0; i < length; i++)
        printf("%d ", mici[i]);
    printf("\n");
    
    mari = modul1(length,mari, sir);
    printf("Sirul :\n");
    for(int i = 0; i < length; i++)
        printf("%d ", mari[i]);
    printf("\n");

    return 0;
}