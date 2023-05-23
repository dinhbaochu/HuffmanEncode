#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"
#include "binarytree.h"
// A node in Huffman tree

char input_encode [100]; // create an string to store the input

int main () {
    int *freqarr;
    //open the original file to translate
    FILE *fptr;
    fptr = fopen("original.txt", "r");
    // Store the content of the file
    fgets(input_encode, 100, fptr);

    freqarr=frequency(input_encode);

    //convert the frequency function 's output to the input of encode function
    int i;
    int length = (*freqarr-1)/2;
    char arr[length];
    int freq[length];
    for (i=1; i<(*freqarr); i+=2){
       
        arr[(i-1)/2]=*(freqarr+i);
    }

    for (i=2; i<(*freqarr); i+=2){
        freq[i/2-1]=*(freqarr+i);
    }
    //end of converter

    int size = sizeof(arr)/sizeof(arr[0]);

    HuffmanCodes1(arr,freq,size, input_encode); //this one write the encoded string 
    HuffmanCodes(arr,freq,size); //this one is for dictionary
  
    return 0;
}