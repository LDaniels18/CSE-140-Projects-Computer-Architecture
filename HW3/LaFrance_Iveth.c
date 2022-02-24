// MIPS Decoder C Program
// Written by Iveth and LaFrance
// CSE 140 - Spring 2022
// University of California - Merced

/*
instructions if using linux... to run you have to compile using gcc
use: gcc LaFrance_Iveth.c --this compiles the program (only use if you dont want to name an executable file)
next we have to create an executable file to show output:
use: gcc LaFrance_Iveth.c -o LaFrance_Iveth (this is prefered and make sure to use everytime you add or delete code)
finally we have to run the program using the executable file
use: ./LaFrance_Iveth (always use after compiling to see output)
*/

#include <stdio.h> //a standard C library that includes the print function
#include <string.h>

int main()
{

    // we need a bit string (character array) to carry the instruction:
    char instruction[32];

    printf("Hello, welcome to our MIPS Decoder! \n");
    printf("Please enter a 32 bit instruction: ");
    // printf("\n");

    scanf("%s", instruction); // looks for input and assigns it to the variable

    // test to check if the instruction was recorded
    printf("Your 32 bit instruction was: %s\n", instruction);

    // test to see if we can check bits:
    // lets see if we can grab each bit individually:
    int count = 1; // a counter for each bits entry in the array
    for (int i = 0; i < 32; i++)
    {
        printf("element: %d and bit: %c\n ", count, instruction[i]);
        count++;
    }

    // we need to first check the first 6 bits of an instruction to determine its type:
    char opCode[6];
    for (int j = 0; j < 6; j++)
    {
        opCode[j] = instruction[j];
        printf("OpCode bit: %c\n ",opCode[j]);
    }

    
    printf("the opCode is: %s\n", opCode); //why doesnt this display the 6 bits??


    // once that is determined, we can detirmine what the type may be, then move over to 1 of 3 functions

    //function for R

    //Function for I

    //Function for J


    return 0; // ends main
}

/*
Example of what output should look like (taken from PDF)

Enter an instruction:
00000001000010011000100000100000
Instruction Type: R
Operation: add
Rs: $8
Rt: $9
Rd: $17
Shamt: 0
Funct: 32

*/

//combine together and use switch 
//for every single fieldo do switch case
//