#include <stdio.h> //a standard C library that includes the print function
#include <string.h>
#include <stdlib.h>
#include "Decoder.h"

//do not need main if we have one already....
// int main(){
//     return 0;
// }

void Decode(char instruction[32]){

    printf("Decoding the Instruction...\n");
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
        char jumpImmediate[] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
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
        char jumpImmediate[] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
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
        char immediate[] = "1111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
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
    
}// end of decode function

// a function to get the integer of used register:
int registers(char binCode[5])
{
    // printf("bin code is: %s\n", binCode);

    int reg; // to hold an actual integer to return

    char bin_0[] = "00000";
    char bin_1[] = "00001";
    char bin_2[] = "00010";
    char bin_3[] = "00011";
    char bin_4[] = "00100";
    char bin_5[] = "00101";
    char bin_6[] = "00110";
    char bin_7[] = "00111";
    char bin_8[] = "01000";
    char bin_9[] = "01001";
    char bin_10[] = "01010";
    char bin_11[] = "01011";
    char bin_12[] = "01100";
    char bin_13[] = "01101";
    char bin_14[] = "01110";
    char bin_15[] = "01111";
    char bin_16[] = "10000";
    char bin_17[] = "10001";
    char bin_18[] = "10010";
    char bin_19[] = "10011";
    char bin_20[] = "10100";
    char bin_21[] = "10101";
    char bin_22[] = "10110";
    char bin_23[] = "10111";
    char bin_24[] = "11000";
    char bin_25[] = "11001";
    char bin_26[] = "11010";
    char bin_27[] = "11011";
    char bin_28[] = "11100";
    char bin_29[] = "11101";
    char bin_30[] = "11110";
    char bin_31[] = "11111";

    // make string compare variable and function:
    int bin_value_0;
    int bin_value_1;
    int bin_value_2;
    int bin_value_3;
    int bin_value_4;
    int bin_value_5;
    int bin_value_6;
    int bin_value_7;
    int bin_value_8;
    int bin_value_9;
    int bin_value_10;
    int bin_value_11;
    int bin_value_12;
    int bin_value_13;
    int bin_value_14;
    int bin_value_15;
    int bin_value_16;
    int bin_value_17;
    int bin_value_18;
    int bin_value_19;
    int bin_value_20;
    int bin_value_21;
    int bin_value_22;
    int bin_value_23;
    int bin_value_24;
    int bin_value_25;
    int bin_value_26;
    int bin_value_27;
    int bin_value_28;
    int bin_value_29;
    int bin_value_30;
    int bin_value_31;

    bin_value_0 = strcmp(binCode, bin_0);
    bin_value_1 = strcmp(binCode, bin_1);
    bin_value_2 = strcmp(binCode, bin_2);
    bin_value_3 = strcmp(binCode, bin_3);
    bin_value_4 = strcmp(binCode, bin_4);
    bin_value_5 = strcmp(binCode, bin_5);
    bin_value_6 = strcmp(binCode, bin_6);
    bin_value_7 = strcmp(binCode, bin_7);
    bin_value_8 = strcmp(binCode, bin_8);
    bin_value_9 = strcmp(binCode, bin_9);
    bin_value_10 = strcmp(binCode, bin_10);
    bin_value_11 = strcmp(binCode, bin_11);
    bin_value_12 = strcmp(binCode, bin_12);
    bin_value_13 = strcmp(binCode, bin_13);
    bin_value_14 = strcmp(binCode, bin_14);
    bin_value_15 = strcmp(binCode, bin_15);
    bin_value_16 = strcmp(binCode, bin_16);
    bin_value_17 = strcmp(binCode, bin_17);
    bin_value_18 = strcmp(binCode, bin_18);
    bin_value_19 = strcmp(binCode, bin_19);
    bin_value_20 = strcmp(binCode, bin_20);
    bin_value_21 = strcmp(binCode, bin_21);
    bin_value_22 = strcmp(binCode, bin_22);
    bin_value_23 = strcmp(binCode, bin_23);
    bin_value_24 = strcmp(binCode, bin_24);
    bin_value_25 = strcmp(binCode, bin_25);
    bin_value_26 = strcmp(binCode, bin_26);
    bin_value_27 = strcmp(binCode, bin_27);
    bin_value_28 = strcmp(binCode, bin_28);
    bin_value_29 = strcmp(binCode, bin_29);
    bin_value_30 = strcmp(binCode, bin_30);
    bin_value_31 = strcmp(binCode, bin_31);

    if (bin_value_0 == 0)
    {

        reg = 0;
    }
    else if (bin_value_1 == 0)
    {
        reg = 1;
    }
    else if (bin_value_2 == 0)
    {
    }
    else if (bin_value_3 == 0)
    {
        reg = 3;
    }
    else if (bin_value_4 == 0)
    {
        reg = 4;
    }
    else if (bin_value_5 == 0)
    { // 5
        reg = 5;
    }
    else if (bin_value_6 == 0)
    {
        reg = 6;
    }
    else if (bin_value_7 == 0)
    {

        reg = 7;
    }
    else if (bin_value_8 == 0)
    {
        reg = 8;
    }
    else if (bin_value_9 == 0)
    {
        reg = 9;
    }
    else if (bin_value_10 == 0)
    { // 10
        reg = 10;
    }
    else if (bin_value_11 == 0)
    {
        reg = 11;
    }
    else if (bin_value_12 == 0)
    {
        reg = 12;
    }
    else if (bin_value_13 == 0)
    {
        reg = 13;
    }
    else if (bin_value_14 == 0)
    {
        reg = 14;
    }
    else if (bin_value_15 == 0)
    { // 15
        reg = 15;
    }
    else if (bin_value_16 == 0)
    {
        reg = 16;
    }
    else if (bin_value_17 == 0)
    {
        reg = 17;
    }
    else if (bin_value_18 == 0)
    {
        reg = 18;
    }
    else if (bin_value_19 == 0)
    {
        reg = 19;
    }
    else if (bin_value_20 == 0)
    {
        reg = 20;
    }
    else if (bin_value_21 == 0)
    {
        reg = 21;
    }
    else if (bin_value_22 == 0)
    {
        reg = 22;
    }
    else if (bin_value_23 == 0)
    {
        reg = 23;
    }
    else if (bin_value_24 == 0)
    {
        reg = 24;
    }
    else if (bin_value_25 == 0)
    {
        reg = 25;
    }

    else if (bin_value_26 == 0)
    {
        reg = 26;
    }
    else if (bin_value_27 == 0)
    {
        reg = 27;
    }
    else if (bin_value_28 == 0)
    {
        reg = 28;
    }
    else if (bin_value_29 == 0)
    {
        reg = 29;
    }
    else if (bin_value_30 == 0)
    {
        reg = 30;
    }
    else if (bin_value_31 == 0)
    {
        reg = 31;
    }
    else
    {
        // printf("Error\n");
        return 0;
    }

    return reg; // return the int number to be displayed
} // end of helper function

int binToDec(char binCode[])
{

    // printf("the binary code is: %s\n", binCode);

    while (binCode != NULL)
    {
        int base = strlen(binCode) - 1; // the base of 2 to be multiplied, we start of -1 because we dont account for the last bit here
        int sum = 0;
        //int count_of_zeros = 0;
        for (int i = 0; i < strlen(binCode) - 1; i++) // we do not account for the last bit of the binary code here....
        {
            // printf("the binary code is: %c\n", binCode[i]);

            int decimal = 1;

            if (binCode[i] == '1')
            {
                for (int j = 0; j < base; j++) // we want to just multiply the number of true bits (not including the 1)
                {

                    decimal = decimal * 2;
                    // printf("the decimal is: %d\n", decimal);
                }
                // printf("(outside for)the decimal is: %d\n", decimal);

                base = base - 1; // subtract base by 1 since we are moving down the string by 1
            }
            else // we encounter a zero
            {
                base = base - 1; // subtract a base multiple everytime we encounter a zero...
                continue;        // carry on with the code
            }

            sum += decimal;
            // printf("the sum is: %d\n", decimal); --test

            // base = base - count_of_zeros; // starting from the left (higher power) to the end (lowest power or 1)
        }

        for (int j = strlen(binCode) - 1; j < strlen(binCode) + 1; j++)
        { // accounting for the endian bit that is always 1

            // printf("the last bit is: %c\n ", binCode[j]); --test

            if (binCode[j] == '1')
            {

                sum += 1; // add 1 to the sum total
            }
        }

        return sum; // same as saying break after the for loop, return the sum as an int
    }

    return 0; //so the compiler doesnt shoot an "non-return" warning
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

Enter an instruction:
00110100001001000000000000000000
Instruction Type : I
Operation: ori
Rs: $1
Rt: $4
Immediate: 0 (or 0x0)


Enter an instruction:
00001100000000100000000000000000
Instruction Type : J
Operation: jal
Immediate: 131072 (or 0x0020000)

some more examples to practice output with:
10011000001001010101110010010001

*/

// recommendation by TA:
//  combine together and use switch
//  for every single fieldo do switch case
