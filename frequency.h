#include <stdio.h>
int * frequency (char *input_encode) 
{   static int outputarr[100];
    outputarr[0]=0;
    int i,k; //iterative quantity
    int check=0; //check if the current character is in character array or not
    int length=1; //count the length of character array 
    for (i=0; input_encode[i]!='\0'; i++){ //iterative through each character of input
        check=0;
        for (k=0; k<=length; k++){
            if (outputarr[k]==input_encode[i]){ //if we can find this character in output array
                outputarr[k+1]++; //frequency of this character will be added by 1 
                check++;      
            }
        }
        if (check==0){ // if we cannot find this character inside the output array
                outputarr[length]=input_encode[i]; //add this character to the array 
                outputarr[length+1]=1; // increase the legth
                length +=2;
             }
        }
    outputarr[0]=length; //put the length at the beginning of the array
    return outputarr;
};