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

#include <stdio.h> //a standard C library that includes the print function
#include <string.h>
#include <stdlib.h>
#include "Decoder.h"

//global variables:
int PC = 0;
int next_PC = PC + 4;

//never changing filename: 
const char* filename = "1_ins.txt";

void Decode(char instruction[32]);
char Fetch();

int main()
{

    printf("Fetching Instruction....");
    Fetch();

    //printf(Decode);


    return 0;

} // end of main function

char Fetch(){
    // // we need a bit string (character array) to carry the instruction:
    char instruction[32];

    //need to use FOpen to open the text file:

}

void Decode(char instruction[32]){

    ///////////////////////////////////////--Operation Code--/////////////////////////////////////
    // we need to first check the first 6 bits of an instruction to determine its type:
    char opCode[] = "111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
    for (int j = 0; j < 6; j++)
    {
        opCode[j] = instruction[j];
        // printf("OpCode bit: %c\n ", opCode[j]); // test to print out bits
    }

    // printf("\n");
    // printf("the opCode is: %s\n", opCode); // test to display the bits

    // to compare strings we need to create strings to compare to:
    char R_Check[] = "000000";  // A General R Type opCode
    char J_Check1[] = "000010"; // J - in MIPS Reference Sheet
    char J_Check2[] = "000011"; // JAL - in MIPS Reference Sheet

    // We also need value holders for each of the comparisons
    int value_R_Check;
    int value_J_Check1;
    int value_J_Check2;

    // the comparison functions, 0 = true, 1 = false
    value_R_Check = strcmp(opCode, R_Check);
    value_J_Check1 = strcmp(opCode, J_Check1);
    value_J_Check2 = strcmp(opCode, J_Check2);

    /////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Source Register-- ///////////////////////////////
    // This is a 5 bit field after the OpCode:
    char rsCodeTransfer[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        rsCodeTransfer[j] = instruction[j + 6];
        // printf("Transferred RS is: %c\n ", rsCodeTransfer[j]); // test to print out bits
    }

    // printf("\n");
    // printf("the Transferred RS is: %s\n", rsCodeTransfer); // test to display the transferred code

    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Target Register-- ///////////////////////////////
    // This is a 5 bit field after the Rs:
    char rtCodeTransfer[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        rtCodeTransfer[j] = instruction[j + 11];
        // printf("Transferred RT is: %c\n ", rtCodeTransfer[j]); // test to print out bits
    }

    // printf("\n");
    // printf("the Transferred RT is: %s\n", rtCodeTransfer); // test to display the transferred code

    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Destination Register-- ///////////////////////////////
    // This is a 5 bit field after the Rt:
    char rdCodeTransfer[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        rdCodeTransfer[j] = instruction[j + 16]; // an intermedite fix for the RD
        // printf("Transferred RD is: %c\n ", rdCodeTransfer[j]); // test to print out bits
    }

    // printf("\n");
    // printf("the Transferred RD is: %s\n", rdCodeTransfer); // test to display the transferred code

    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Shift Amount-- ///////////////////////////////
    // right after RD - 5 bits long
    char shiftAmount[] = "11111";

    for (int i = 0; i < 5; i++)
    {

        shiftAmount[i] = instruction[i + 21];
        // printf("Shift Amount bit is: %c\n ", shiftAmount[i]); // test to print out bits
    }

    // printf("\n");
    // printf("Shift Amount is: %s\n ", shiftAmount); // test to print out bits

    /////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////--Function Code --/////////////////////////////////////////////////////
    // we need to detirmine the correct operation based off the function code (last 6 bits 0-5):
    char functCodeTransfer[] = "111111";

    for (int j = 0; j < 6; j++)
    {
        functCodeTransfer[j] = instruction[j + 26];
        // printf("Transferred Function Code bit: %c\n ", functCodeTransfer[j]); // test to print out bits
    }

    // printf("\n");
    // printf("The Transferred Function Code is: %s\n", functCodeTransfer); // test to display the transferred code

    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Determining Type of Instruction:
    // creating logical loops to determine type by opCode:

    if (value_R_Check == 0) //  only R types are == 000000
    {

        // function for R
        // printf("This is an R-Type instruction!\n");
        printf("\nInstruction Type : R\n");

        // registers(instruction); // passing the char array to the helper functions

        // create various function codes to compare instructions (R-Types):
        char Add_Check[] = "100000";
        char UnsignAdd_Check[] = "100001";
        char And_Check[] = "100100";
        char JumpRegister_Check[] = "001000";
        char Nor_Check[] = "100111";
        char Or_check[] = "100101";
        char SLT_Check[] = "101010";
        char SLTU_Check[] = "101011";
        char SLL_Check[] = "000000";
        char SRL_Check[] = "000010";
        char Subtract_Check[] = "100010";
        char SubtractUnsign_Check[] = "100011";

        // make string compare variable and function:
        int value_Add_Check;
        int value_unsignAdd_check;
        int value_And_Check;
        int value_JumpR_Check;
        int value_Nor_Check;
        int value_Or_Check;
        int value_SLT_Check;
        int value_SLTU_Check;
        int value_SLL_Check;
        int value_SRL_Check;
        int value_Subtract_Check;
        int value_SubU_Check;

        value_Add_Check = strcmp(functCodeTransfer, Add_Check);             // For Add
        value_unsignAdd_check = strcmp(functCodeTransfer, UnsignAdd_Check); // For unsigned Add
        value_And_Check = strcmp(functCodeTransfer, And_Check);
        value_JumpR_Check = strcmp(functCodeTransfer, JumpRegister_Check);
        value_Nor_Check = strcmp(functCodeTransfer, Nor_Check);
        value_Or_Check = strcmp(functCodeTransfer, Or_check);
        value_SLT_Check = strcmp(functCodeTransfer, SLT_Check);
        value_SLTU_Check = strcmp(functCodeTransfer, SLTU_Check);
        value_SLL_Check = strcmp(functCodeTransfer, SLL_Check);
        value_SRL_Check = strcmp(functCodeTransfer, SRL_Check);
        value_Subtract_Check = strcmp(functCodeTransfer, Subtract_Check);
        value_SubU_Check = strcmp(functCodeTransfer, SubtractUnsign_Check);

        // printf("the check value is: %d\n", value_Add_Check); //test to check the compare function

        // make a series of nested loops to figure out the correct instruction:
        if (value_Add_Check == 0) // 00000001001010011000101110100000 for test
        {

            printf("Operation: and\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well
        }
        else if (value_unsignAdd_check == 0) // 00000001000010011000100000100001 for test
        {
            printf("Operation: addu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well
        }
        else if (value_And_Check == 0) // 00000001000010011000100000100100 for test
        {
            printf("Operation: and\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_JumpR_Check == 0) // 00000001000010011000100000001000 for test
        {
            printf("Operation: jr\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_Nor_Check == 0) // 00000001000010011000100000100111 for test
        {
            printf("Operation: nor\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_Or_Check == 0) // 00000001000010011000100000100101 for test
        {
            printf("Operation: or\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SLT_Check == 0) // 00000001000010011000100000101010 for test
        {
            printf("Operation: slt\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SLTU_Check == 0) // 00000001000010011000100000101011 for test
        {
            printf("Operation: sltu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SLL_Check == 0) // 00000001000010011000100000000000 for test
        {
            printf("Operation: sll\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SRL_Check == 0) // 00000001000010011000100000000010 for test
        {
            printf("Operation: srl\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_Subtract_Check == 0) // 00000001000010011000100000100010 for test
        {
            printf("Operation: sub\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SubU_Check == 0) // 00000001010000111011000000100011 for test
        {
            printf("Operation: subu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Rd: $%d\n", registers(rdCodeTransfer));
            printf("Shamt: %d\n", registers(shiftAmount));      // need to work on this as well
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well
        }
        else
        {
            // printf("This is an error! No operation found");
            //return 0;
        }
    }
    // where the op code is equal to Jump or JAL -- since there is only 2 we can knock that out right now!
    else if (value_J_Check1 == 0)
    {

        //////////////////////////////////////////--Jump Immediate (Address - Type J)--/////////////////////////////////////////
        // a field for a total of 26 bits
        char jumpImmediate[26] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 0; j < 27; j++)
        {
            jumpImmediate[j] = instruction[j + 6];
            // printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        // printf("\n");
        // printf("the Jump Immediate is: %s\n", jumpImmediate); // test to display the bits
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        printf("Instruction Type : J\n");
        printf("Operation: j\n ");
        printf("Immediate: %d (or 0x%x)\n", binToDec(jumpImmediate), binToDec(jumpImmediate));
        // printf("\n");
    }
    else if (value_J_Check2 == 0) // 00001100000000100000000000000000   --to test
    {

        //////////////////////////////////////////--Jump Immediate (Address - Type J)--/////////////////////////////////////////
        // a field for a total of 26 bits
        char jumpImmediate[26] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 0; j < 27; j++)
        {
            jumpImmediate[j] = instruction[j + 6];
            // printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        // printf("\n");
        // printf("the Jump Immediate is: %s\n", jumpImmediate); // test to display the bits
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        printf("Instruction Type : J\n");
        printf("Operation: jal\n");
        printf("Immediate: %d (or 0x%x)\n", binToDec(jumpImmediate), binToDec(jumpImmediate));
        // printf("\n");
    }
    // we can assume this since its not fitting the other criteria
    else
    {

        //////////////////////////////////////////--Immediate (Type I)--/////////////////////////////////////////
        char immediate[16] = "1111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 0; j < 17; j++)
        {
            immediate[j] = instruction[j + 16];
            // printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        // printf("\n");
        // printf("the Immediate is: %s\n", immediate); // test to display the bits
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Function for I
        printf("Instruction Type: I\n");

        char Add_Immediate[] = "001000";
        char Add_unsign_Immediate[] = "001001";
        char And_Immediate[] = "001100";
        char Branch_equal[] = "000100";
        char Branch_Not_Equal[] = "000101";
        char Load_Byte_Unsigned[] = "100100";
        char Load_Halfword_Unsigned[] = "100101";
        char Load_Linked[] = "110000";
        char Load_Upper_Imm[] = "001111";
        char Load_Word[] = "100011";
        char Or_Imm[] = "001101";
        char Less_Than_Imm[] = "001010";
        char Less_Than_Imm_Unsign[] = "001011";
        char Store_Byte[] = "101000";
        char Store_Cond[] = "111000";
        char Store_Halfword[] = "101001";
        char Store_Word[] = "101011";

        //========================================
        int value_add_Imm_Check;
        int value_unAdd_Check;
        int value_and_Imm;
        int value_branch_Equal;
        int value_branch_Not_equal;
        int value_Load_Byte_Unsign;
        int value_Halfword_Unsign;
        int value_Load_Linked;
        int value_Load_Upper_Imm;
        int value_Load_Word;
        int value_Or_Imm;
        int value_Less_Than_Imm;
        int value_Less_Than_Unsign;
        int value_Store_Byte;
        int value_Store_Cond;
        int value_Store_Halfword;
        int value_Store_word;
        //=======================================================================
        value_add_Imm_Check = strcmp(opCode, Add_Immediate);
        value_unAdd_Check = strcmp(opCode, Add_unsign_Immediate);
        value_and_Imm = strcmp(opCode, And_Immediate);
        value_branch_Equal = strcmp(opCode, Branch_equal);
        value_branch_Not_equal = strcmp(opCode, Branch_Not_Equal);
        value_Load_Byte_Unsign = strcmp(opCode, Load_Byte_Unsigned);
        value_Halfword_Unsign = strcmp(opCode, Load_Halfword_Unsigned);
        value_Load_Linked = strcmp(opCode, Load_Linked);
        value_Load_Upper_Imm = strcmp(opCode, Load_Upper_Imm);
        value_Load_Word = strcmp(opCode, Load_Word);
        value_Or_Imm = strcmp(opCode, Or_Imm);
        value_Less_Than_Imm = strcmp(opCode, Less_Than_Imm);
        value_Less_Than_Unsign = strcmp(opCode, Less_Than_Imm_Unsign);
        value_Store_Byte = strcmp(opCode, Store_Byte);
        value_Store_Cond = strcmp(opCode, Store_Cond);
        value_Store_Halfword = strcmp(opCode, Store_Halfword);
        value_Store_word = strcmp(opCode, Store_Word);
        //=======================================================================
        if (value_add_Imm_Check == 0) // 00100000001001000000010010010000  --to test
        {

            printf("The operation is Addi\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_unAdd_Check == 0)
        {
            printf("Operation: addiu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_and_Imm == 0)
        {
            printf("Operation: andi\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_branch_Equal == 0)
        {
            printf("Operation: beq\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_branch_Not_equal == 0)
        {
            printf("Operation: bne\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Byte_Unsign == 0)
        {
            printf("Operation: ibu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Halfword_Unsign == 0) // 10010101010000110000000000101010  --to test
        {
            printf("Operation: lhu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Linked == 0)
        {
            printf("Operation: ll\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Upper_Imm == 0)
        {
            printf("Operation: lui\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Word == 0)
        {
            printf("Operation: lw\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Or_Imm == 0)
        {
            printf("Operation: ori\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Less_Than_Imm == 0)
        {
            printf("Operation: slti\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Less_Than_Unsign == 0)
        {
            printf("Operation: sltiu\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Byte == 0)
        {
            printf("Operation: sb\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Cond == 0)
        {
            printf("Operation: sc\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Halfword == 0)
        {
            printf("Operation: sh\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_word == 0)
        {
            printf("Operation: sw\n");
            printf("Rs: $%d\n", registers(rsCodeTransfer));
            printf("Rt: $%d\n", registers(rtCodeTransfer));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else
        {
            // printf("This is an error! No operation found");
            //return 0;
        }
    }

    //return 0; // ends function
}

