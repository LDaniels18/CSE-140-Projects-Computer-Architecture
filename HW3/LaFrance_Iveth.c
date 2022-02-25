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
#include <stdlib.h>

void r_Instructions(char instruction[]); //declaring the helper function by passing the instruction char array 
void i_Instructions(char instruction[]); //declaring the helper function by passing the instruction char array 

int main()
{

    // // we need a bit string (character array) to carry the instruction:
    char instruction[32];

    printf("Hello, welcome to our MIPS Decoder! \n");
    printf("Please enter a 32 bit instruction: ");
    // printf("\n");

    scanf("%s", instruction); // looks for input and assigns it to the variable

    // test to check if the instruction was recorded
    printf("Your 32 bit instruction was: %s\n", instruction);

    // we need to first check the first 6 bits of an instruction to determine its type:
    char opCode[] = "111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
    for (int j = 0; j < 6; j++)
    {
        opCode[j] = instruction[j];
        printf("OpCode bit: %c\n ", opCode[j]); // test to print out bits
    }

    printf("\n");
    printf("the opCode is: %s\n", opCode); // test to display the bits

    // once that is determined, we can detirmine what the type may be, then move over to 1 of 3 functions

    // to compare strings we need to create strings to compare to:
    char R_Check[] = "000000";  // A General R Type opCode
    char I_Check1[] = "000010"; // J - in MIPS Reference Sheet
    char I_Check2[] = "000011"; // JAL - in MIPS Reference Sheet

    // We also need value holders for each of the comparisons
    int value_R_Check;
    int value_I_Check1;
    int value_I_Check2;

    // the comparison functions, 0 = true, 1 = false
    value_R_Check = strcmp(opCode, R_Check);
    value_I_Check1 = strcmp(opCode, I_Check1);
    value_I_Check2 = strcmp(opCode, I_Check2);

    // creating logical loops to determine type by opCode:
    //  only R types are == 000000
    if (value_R_Check == 0)
    {
        // function for R
        // printf("This is an R-Type instruction!\n");
        printf("\nInstruction Type : R\n");

        r_Instructions(instruction); //passing the char array to the helper functions


    }
    // where the op code is equal to Jump or JAL -- since there is only 2 we can knock that out right now!
    else if (value_I_Check1 == 0)
    {

        // printf("This is an J-Type instruction!\n");
        // begin displaying output:
        printf("Instruction Type : J\n");
        printf("Operation: j\n ");

        char immediate[27] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 6; j < 31; j++)
        {
            immediate[j] = instruction[j];
            printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        printf("\n");
        printf("the Immediate is: %s\n", immediate + 6); // test to display the bits
        //enter math to obtain the value of the immediate:
        // printf("Immediate: %d\n", immediate);
    }
    else if (value_I_Check2 == 0)
    {
        // printf("This is an J-Type instruction!\n");
        // begin displaying output:
        printf("Instruction Type : J\n");
        printf("Operation: jal\n ");

        char immediate[27] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 6; j < 31; j++)
        {
            immediate[j] = instruction[j];
            printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        printf("\n");
        printf("the Immediate is: %s\n", immediate + 6); // test to display the bits

        //enter math to obtain the value of the immediate:
        //printf("Immediate: %d\n", immediate);
    }
    // we can assume this since its not fitting the other criteria
    else
    {
        // Function for I
        // printf("This is an I-Type instruction!\n");
        printf("Instruction Type : I\n");
    }


    return 0; // ends main

} //end of main function 

//a function exclusive for R Type Instructions:
void r_Instructions(char instruction[]){ 

    printf("\n");
    printf("The instruction is (from helper function): %s\n" , instruction); //test to see if passing works
} //end of helper function 

//a function exclusive for I Type Instrctions:
void i_Instructions(char instruction[]){

    printf("The instruction is (from helper function): %s\n" , instruction); //test to see if passing works

} //end of helper function 

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

// combine together and use switch
// for every single fieldo do switch case
//