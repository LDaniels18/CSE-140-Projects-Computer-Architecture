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
#include "Execute.h"

#define MAX_LENGTH 256 // using a length variable to help with reading the line of text

// global variables:
int PC = 0;                                        // Starting Instruction
char *instruction_counter[MAX_LENGTH][MAX_LENGTH]; // to act as a container pointing to an instruction
// char *instruction[MAX_LENGTH];                     // a universal pointer for instructions
int i = 0;                 // starting location in the instruction counter:
int instruction_index = 0; // the instruction_index to be added by 4 everytime;
int cycles;

// never changing filename (obviously change when you recieve a finalized file):
const char *filename = "sample_ins.txt";

void CPU_Process(); // to act as the main CPU function
int fetch();        // to fetch instructions for the PC counter

int main()
{
    printf("Welcome to our Single Cycle MIPS CPU!\n");
    // char instruction_catch; //will catch the results after fetch() is called (will be considered int in output)

    CPU_Process(); //start the CPU

    return 0; // ending the program

} // end of main function

void CPU_Process()
{
    printf("Preparing to fectch the 32 bit instruction....\n");
    printf("\n");

    fetch();

} // end of CPU Process Function

// A function to both fetch and decode a given instruction:
int fetch()
{
    // we need a bit string (character array) to carry the instruction:
    char instruction[MAX_LENGTH]; // to carry the new 32 bit instruction

    printf("Fetching the Instruction...\n");

    // creating an File Pointer object:
    FILE *file_accessor; // object

    file_accessor = fopen(filename, "r"); // using the fopen function to read from a file

    // CONDITIONS:
    if (file_accessor == NULL) // if theres nothing in the text file then we cant continue
    {
        printf("This file is empty, no instruction... now ending process!\n");
        exit(1); // to exit the function with a failure
    }            // end of if

    printf("Instruction Detected... now fetching!\n");
    printf("\n");

    // to read the file, line by line and add the contents to our carry variable
    while (fgets(instruction, MAX_LENGTH, file_accessor))
    { // going to the line

        // indicating that instruction was fetched:
        printf("\n");
        printf("Instruction Fetched!\n");

        // to get rid of the newline (for each line):
        instruction[strcspn(instruction, "\n")] = 0;

        instruction_counter[instruction_index][32] = instruction; // the instruction gets loaded at a particular location 4 spaces from one another or PC(4)

        printf("\n");
        printf("Loading instruction onto table....\n");

        // to print the instruction bit by bit -- tests:
        // printf("Your 32 bit instruction was: %s\n", instruction_counter[i][32]);
        // printf("\n");
        // printf("Instruction counter position: %d\n", i);

        // the first instruction to always be decoded be decoded:
        printf("\n");
        printf("Decoding the Instruction.....");
        Decode(instruction_counter[PC][32]);

        instruction_index = instruction_index + 4; // updating the instruction_index by 4 to place it in the instruction counter
        i = i + 1;                                 // Relates to the instruction that was just fetched
        PC = 4 * i;                                // points to the current instruction
        int next_PC = PC + 4;                      // always update the PC everytime you read an instruction

        printf("\n");
        printf("Instruction loaded!\n");

    } // end of while

    fclose(file_accessor); // closing the read file (will need to be controlled by the PC)

    
    //a quick test to see i can decode from a set place
    // printf("\n");
    // printf("Decoding the Instruction.....");
    // Decode(instruction_counter[PC][32]);

    return 0; // ending the instruction
} // end of fetch
