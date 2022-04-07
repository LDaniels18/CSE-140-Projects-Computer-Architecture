// MIPS Single Cycle CPU
// Written by Iveth and LaFrance
// CSE 140 - Spring 2022
// University of California - Merced

/*
Work Distribution:
*/

/*
instructions if using linux... to run you have to compile using gcc
use: gcc LaFrance_Iveth.c --this compiles the program (only use if you dont want to name an executable file)
next we have to create an executable file to show output:
use: gcc LaFrance_Iveth.c -o LaFrance_Iveth (this is prefered and make sure to use everytime you add or delete code)
finally we have to run the program using the executable file which we name after "-o")
use: ./LaFrance_Iveth (always use after compiling to see output, run the executable file that contains output)
*/

/*
Any Used Resources to be Cited:
For the Fetch Function (While Loop Process): https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

*/

#include <stdio.h> //a standard C library that includes the print function
#include <string.h>
#include <stdlib.h>
#include "Decoder.h"
#define MAX_LENGTH 256 // using a length variable to help with reading the line of text

// global variables:
int PC = 0; // Starting Instruction

// never changing filename (obviously change when you recieve a finalized file):
const char *filename = "1_ins.txt";

char CPU_Process();
//void Decode(char instruction);

int main()
{
    char instruction_catcher;

    printf("Welcome to our Single Cycle MIPS CPU!\n");
    // char instruction_catch; //will catch the results after fetch() is called (will be considered int in output)

    printf("Preparing to fectch the 32 bit instruction....\n");
    CPU_Process();

    return 0; //ending the program

} // end of main function

char CPU_Process()
{
    // // we need a bit string (character array) to carry the instruction:

    char instruction[MAX_LENGTH]; // to carry the new 32 bit instruction

    printf("Fetching the Instruction...\n");

    // creating an File Pointer object:
    FILE *file_accessor; // object

    file_accessor = fopen("1_ins.txt", "r"); // using the fopen function to read from a file

    // CONDITIONS:
    if (file_accessor == NULL) // if theres nothing in the text file then we cant continue
    {
        printf("This file is empty, no instruction... now ending process!\n");
        exit(1); // to exit the function with a failure
    }            // end of if

    printf("Instruction Detected... now fetching!\n");

    // to read the file, line by line and add the contents to our carry variable
    while (fgets(instruction, MAX_LENGTH, file_accessor))
    {
        //indicating that instruction was fetched:
         printf("Instruction Fetched!\n");

        // to get rid of the newline (for each line):
        instruction[strcspn(instruction, "\n")] = 0;

        // to print the instruction bit by bit:
        printf("Your 32 bit instruction was: %s\n", instruction);

    } // end of while

   
    fclose(file_accessor); // closing the read file (will need to be controlled by the PC)

    //Running Decoder from Fetch:
    printf("Preparing to Decode the Instruction...\n");
    Decode(instruction);

    return *instruction; // returning the value of instruction which is also going to be a int when used... need to fix to become a string

    // next instruction to be pointed to by the Program Counter:
    // int next_PC = PC + 4;

} // end of fetch function
