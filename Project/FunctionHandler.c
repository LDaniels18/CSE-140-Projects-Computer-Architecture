#include <stdio.h> //a standard C library that includes the print function
#include <string.h>
#include <stdlib.h>
#include "FunctionHandler.h"

/*
This File includes all functions necessary to run, decode and run memory processes for the Single Cycle MIPS CPU
This File contains our original HW3 (MIPS Decoder File, which can be found in the Unused Files Folder) and other
code written by LaFrance and Iveth for the CSE 140 Final Project
*/

// Global Variables:
int registerFile[32] = {0}; // RegisterFile initialized to 0
char aluOp[4];              // ALU Operation binary code (only 2 bits)
int d_mem[32] = {0};        // D MemoryFile -- represents memory of 32 bits
int alu_zero = 0;           // if the alu operation is a complete zero
int label = 0;              // place to branch to
int jumpAddress = 0;        // a place to jump to
// char jump_target[26];     //place to jump to

/*
        --schema for the ALU OP (Does not need to be very sepcific)
            aluOp[0] = "00"; //Load Word Instruction
            aluOp[1] = "01"; //Store Word Instruction/ Branching Instructions / Jump
            aluOp[2] = "11"; //Primarily I Type
            aluOp[3] = "10"; //Primarily R Type
*/

int DecodeAndExecute(char instruction[32], int pc_val)
{

    // to hold integers representing the Register values - using MIPS nomenclature:
    int rsValue = 0;
    int RegDestValue = 0;
    int rtValue = 0;

    // variable to hole the value from memory:
    int valueFromMemory;

    // Begining the Decoding Process:
    printf("\n");
    printf("/////////////////////////// -- Decoder -- //////////////////////////////////\n");
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
    printf("the opCode is: %s\n", opCode); // test to display the bits

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
    char RegStart[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        RegStart[j] = instruction[j + 6];
        // printf("Transferred RS is: %c\n ", RegStart[j]); // test to print out bits
    }

    // printf("\n");
    printf("the RS is: %s\n", RegStart); // test to display the transferred code

    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Target Register-- ///////////////////////////////
    // This is a 5 bit field after the Rs:
    char RegTarget[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        RegTarget[j] = instruction[j + 11];
        // printf("Transferred RT is: %c\n ", RegTarget[j]); // test to print out bits
    }

    // printf("\n");
    printf("the RT is: %s\n", RegTarget); // test to display the transferred code

    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////-- Destination Register-- ///////////////////////////////
    // This is a 5 bit field after the Rt:
    char RegDest[] = "11111";

    for (int j = 0; j < 5; j++)
    {
        RegDest[j] = instruction[j + 16]; // an intermedite fix for the RD
        // printf("Transferred RD is: %c\n ", RegDest[j]); // test to print out bits
    }

    // printf("\n");
    printf("the RD is: %s\n", RegDest); // test to display the transferred code

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
    printf("Shift Amount is: %s\n", shiftAmount); // test to print out bits

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
    printf("Function Code is: %s\n", functCodeTransfer); // test to display the transferred code

    ////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////--Immediate (Type I)--/////////////////////////////////////////
    char immediate[16] = "1111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
    printf("Immediate: ");
    for (int j = 0; j < 17; j++)
    {
        immediate[j] = instruction[j + 16];
        printf("%c", immediate[j]); // test to print out bits
    }

    printf("\n");
    // printf("Immediate: %s\n", immediate); // test to display the bits
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("\n");
    // Assigning the RS and RT values:
    printf("Finding RS and RT Values.... \n");

    rsValue = binToDec(RegStart);
    printf("Rs Value = %d\n", rsValue);

    rtValue = binToDec(RegTarget);
    printf("Rt value = %d\n", rtValue);

    printf("\n");
    printf("Displaying Decoded Parts....\n");

    // Determining Type of Instruction:
    // creating logical loops to determine type by opCode:
    if (value_R_Check == 0) //  only R types are == 000000
    {

        // function for R
        // printf("This is an R-Type instruction!\n");
        printf("\nInstruction Type : R\n");

        // registerfile(instruction); // passing the char array to the helper functions

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
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            RegDestValue = rsValue + rtValue;
            RegWrite(RegDest, RegDestValue);
            printf("Executing the Instruction...\n");

            printf("Register Destination: $ %d", binToDec(RegDest));
            printf(", RD Register Value: %d", RegDestValue);
        }
        else if (value_unsignAdd_check == 0) // 00000001000010011000100000100001 for test
        {
            printf("Operation: addu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well
        }
        else if (value_And_Check == 0) // 00000001000010011000100000100100 for test
        {
            printf("Operation: and\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU OPeration....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            RegDestValue = rsValue & rtValue;
            RegWrite(RegDest, RegDestValue);
            printf("Executing the Instruction...\n");

            printf("Register Destination: $ %d", binToDec(RegDest));
            printf(", RD Register Value: %d", RegDestValue);
        }
        else if (value_JumpR_Check == 0) // 00000001000010011000100000001000 for test
        {
            printf("Operation: jr\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU OPeration....\n");
            strcpy(aluOp, "01");
            printf("ALU OP Code is: %s\n", aluOp);

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");

            jumpAddress = RegGet("11111");
        }
        else if (value_Nor_Check == 0) // 00000001000010011000100000100111 for test
        {
            printf("Operation: nor\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            // specific to nor:
            RegDestValue = rsValue | rtValue;
            RegDestValue = ~RegDestValue;
            RegWrite(RegDest, RegDestValue);
            printf("Executing the Instruction...\n");

            printf("Register Destination: $ %d", binToDec(RegDest));
            printf(", RD Register Value: %d", RegDestValue);
        }
        else if (value_Or_Check == 0) // 00000001000010011000100000100101 for test
        {
            printf("Operation: or\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            RegDestValue = rsValue | rtValue;
            RegWrite(RegDest, RegDestValue);
            printf("Executing the Instruction...\n");

            printf("Register Destination: $ %d", binToDec(RegDest));
            printf(", RD Register Value: %d", RegDestValue);
        }
        else if (value_SLT_Check == 0) // 00000001000010011000100000101010 for test
        {
            printf("Operation: slt\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            printf("Executing the Instruction...\n");

            // we need to compare Rd to Rs (values)
            if (rsValue < rtValue)
            {

                RegDestValue = 1;
                RegWrite(RegDest, RegDestValue);
                printf("Register Destination: $ %d", binToDec(RegDest));
                printf(", RD Register Value: %d", RegDestValue);
            }
            else
            {

                RegDestValue = 0;
                RegWrite(RegDest, RegDestValue);
                printf("Register Destination: $ %d", binToDec(RegDest));
                printf(", RD Register Value: %d", RegDestValue);
            }
        }
        else if (value_SLTU_Check == 0) // 00000001000010011000100000101011 for test
        {
            printf("Operation: sltu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SLL_Check == 0) // 00000001000010011000100000000000 for test
        {
            printf("Operation: sll\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_SRL_Check == 0) // 00000001000010011000100000000010 for test
        {
            printf("Operation: srl\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));
        }
        else if (value_Subtract_Check == 0) // 00000001000010011000100000100010 for test
        {
            printf("Operation: sub\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU OPeration....\n");
            strcpy(aluOp, "10");
            printf("ALU OP Code is: %s\n", aluOp);

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this R-Type Instruction........\n");
            RegDestValue = rsValue - rtValue;
            RegWrite(RegDest, RegDestValue);
            printf("Executing the Instruction...\n");

            printf("Register Destination: $ %d", binToDec(RegDest));
            printf(", RD Register Value: %d", RegDestValue);
        }
        else if (value_SubU_Check == 0) // 00000001010000111011000000100011 for test
        {
            printf("Operation: subu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Rd: $%d\n", registerfile(RegDest));
            printf("Shamt: %d\n", registerfile(shiftAmount));                                          // need to work on this as well
            printf("Funct: %d (or 0x%x)\n", binToDec(functCodeTransfer), binToDec(functCodeTransfer)); // need to work on this as well
        }
        else
        {
            // printf("This is an error! No operation found");
            // return 0;
        }
    }
    // where the op code is equal to Jump or JAL -- since there is only 2 we can knock that out right now!
    /*
    NOTE J AND JAL ARE SIMPLY SIMULATING WHAT WOULD HAPPEN IN THE CPU, THIS VERSION IS NOT AS IN DEPTH AS AN ACTUAL CPU
    */
    else if (value_J_Check1 == 0)
    {

        //////////////////////////////////////////--Jump Immediate (Address - Type J)--/////////////////////////////////////////
        // a field for a total of 26 bits
        char jump_target[26] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 0; j < 27; j++)
        {
            jump_target[j] = instruction[j + 6];
            // printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        // printf("\n");
        // printf("the Jump Immediate is: %s\n", jump_target); // test to display the bits
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        printf("Instruction Type : J\n");
        printf("Operation: j\n ");
        printf("Immediate: %d (or 0x%x)\n", binToDec(jump_target), binToDec(jump_target));

        printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
        // Adding work for ALU and then to execute:

        printf("Determining the ALU OPeration....\n");
        strcpy(aluOp, "01");
        printf("ALU OP Code is: %s\n", aluOp);

        // Assigning RD Register based off ALU OP:
        printf("Preparing to Execute this J-Type Instruction........\n");

        // the PC value carried from the Fetch Function needs to be applied to the label
        jumpAddress = binToDec(jump_target);

        // making the pc value the address + 4:
        pc_val = jumpAddress + 4;

        printf("The PC is now pointing to the address of the label + 4: 0x%d\n", pc_val);
    }
    else if (value_J_Check2 == 0) // 00001100000000100000000000000000   --to test
    {

        //////////////////////////////////////////--Jump Immediate (Address - Type J)--/////////////////////////////////////////
        // a field for a total of 26 bits
        char jump_target[26] = "11111111111111111111111111"; // this is a general setting for the opCode (to not leave blank)... will be set by the for loop below:
        for (int j = 0; j < 27; j++)
        {
            jump_target[j] = instruction[j + 6];
            // printf("Immediate bit: %c\n ", immediate[j]); // test to print out bits
        }

        // printf("\n");
        printf("the Jump Immediate is: %s\n", jump_target); // test to display the bits
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        printf("Instruction Type : J\n");
        printf("Operation: jal\n");
        printf("Immediate: %d (or 0x%x)\n", binToDec(jump_target), binToDec(jump_target));

        printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
        // Adding work for ALU and then to execute:

        printf("Determining the ALU OPeration....\n");
        strcpy(aluOp, "01");
        printf("ALU OP Code is: %s\n", aluOp);

        // Assigning RD Register based off ALU OP:
        printf("Preparing to Execute this J-Type Instruction........\n");

        // the PC value carried from the Fetch Function needs to be applied to the label
        jumpAddress = binToDec(jump_target);

        // making the pc value the address + 4:
        pc_val = jumpAddress + 4;

        printf("The PC is now pointing to the address of the label + 4: 0x%x\n", pc_val);
        printf("\n");

        // needing to update the $ra register with pc_val
        printf("Updating the $ra register with the new PC value....\n");
        RegWrite("11111", pc_val);
    }
    // we can assume this since its not fitting the other criteria
    else
    {

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
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_unAdd_Check == 0)
        {
            printf("Operation: addiu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_and_Imm == 0)
        {
            printf("Operation: andi\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_branch_Equal == 0)
        {
            printf("Operation: beq\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU OPeration....\n");
            strcpy(aluOp, "01");
            printf("ALU OP Code is: %s\n", aluOp);

            // Assigning RD Register based off ALU OP:
            printf("Preparing to Execute this I-Type Instruction........\n");

            if (rtValue == rsValue) // we need to check if both registers are equal to branch to label (next pc)
            {
                // the PC value carried from the Fetch Function needs to be applied to the label
                pc_val = pc_val + binToDec(immediate);

                // making the label the next PC value + 4:
                label = pc_val + 4;
                // since we dont need to update the $ra we dont necessarily have to do anything:
                printf("The label points to the next instruction: 0x%d\n", pc_val);
            }
        }
        else if (value_branch_Not_equal == 0)
        {
            printf("Operation: bne\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Byte_Unsign == 0)
        {
            printf("Operation: ibu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Halfword_Unsign == 0) // 10010101010000110000000000101010  --to test
        {
            printf("Operation: lhu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Linked == 0)
        {
            printf("Operation: ll\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Upper_Imm == 0)
        {
            printf("Operation: lui\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Load_Word == 0)
        {
            printf("Operation: lw\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "00");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RT Register based off ALU OP:
            printf("Preparing to Execute this I-Type Instruction........\n");

            printf("Now assigning a value from memory memory....\n");
            rsValue = rsValue + binToDec(immediate) / 4;

            // needing to immediately assign a value found from memory:
            valueFromMemory = Memory(rsValue);
            printf("Value from memory: %d\n", valueFromMemory); // test
            printf("\n");

            // grabbing the new register and assigning it to the rt register:

            ///// --- need to work on this --- /////
            // char *RTValue;
            // strcpy(RTValue, RegWrite(RegTarget,valueFromMemory));
            // RTValue = RegWrite(RegTarget,valueFromMemory);
            // printf("Value of RTVALUE: %s\n", RTValue);
            //////////////////---///////////////////

            printf("Executing the Instruction...\n");

            printf("Target Register: $%d", binToDec(RegTarget));
            printf(", Value loaded: %d", valueFromMemory);
        }
        else if (value_Or_Imm == 0)
        {
            printf("Operation: ori\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Less_Than_Imm == 0)
        {
            printf("Operation: slti\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Less_Than_Unsign == 0)
        {
            printf("Operation: sltiu\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Byte == 0)
        {
            printf("Operation: sb\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Cond == 0)
        {
            printf("Operation: sc\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_Halfword == 0)
        {
            printf("Operation: sh\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));
        }
        else if (value_Store_word == 0)
        {
            printf("Operation: sw\n");
            printf("Rs: $%d\n", registerfile(RegStart));
            printf("Rt: $%d\n", registerfile(RegTarget));
            printf("Immediate: %d (or 0x%x)\n", binToDec(immediate), binToDec(immediate));

            printf("///////////////////////////// -- Execute -- ///////////////////////////////////\n");
            // Adding work for ALU and then to execute:

            printf("Determining the ALU Operation....\n");
            strcpy(aluOp, "01");
            printf("ALU OP Code is: %s\n", aluOp);
            printf("\n");

            // Assigning RT Register based off ALU OP:
            printf("Preparing to Execute this I-Type Instruction........\n");

            printf("Now writing a value onto memory....\n");
            rsValue = rsValue + binToDec(immediate) / 4;

            // //needing to immediately assign a value found from memory:
            // valueFromMemory = Memory(rsValue);

            // Writing the value onto memory:
            WriteBack(rtValue, rsValue);

            printf("Executing the Instruction...\n");

            printf("Target Register: $ %d", binToDec(RegTarget));
            printf(", Value loaded: %d", rsValue);
        }
        else
        {
            // printf("This is an error! No operation found");
            // return 0;
        }
    }

    printf("\n");
    printf("\n");
    printf("Project Criteria: \n");
    printf("PC is modified to 0x%x\n",pc_val);
   
    return 0; // ends function

} // end of decode function

// a function to get the integer of used register:
int registerfile(char binCode[5])
{
    // to test:
    // printf("/////////////////// -- Within Register File Function -- //////////////////\n");
    // printf("Binary Code currently looked at is: %s\n", binCode);

    int reg; // to hold an actual integer to return

    // each char array represents a real register in MIPS
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

    // Register Files:

    int $zero;
    int $at;
    int $v0;
    int $v1;
    int $a0;
    int $a1;
    int $a2;
    int $a3;
    int $t0;
    int $t1;
    int $t2;
    int $t3;
    int $t4;
    int $t5;
    int $t6;
    int $t7;
    int $s0;
    int $s1;
    int $s2;
    int $s3;
    int $s4;
    int $s5;
    int $s6;
    int $s7;
    int $t8;
    int $t9;
    int $k0;
    int $k1;
    int $gp;
    int $sp;
    int $fp;
    int $ra;

    // comparing two binary values to then place the int 1 or 0 into corresponding RegFile:

    $zero = strcmp(binCode, bin_0);
    $at = strcmp(binCode, bin_1);
    $v0 = strcmp(binCode, bin_2);
    $v1 = strcmp(binCode, bin_3);
    $a0 = strcmp(binCode, bin_4);
    $a1 = strcmp(binCode, bin_5);
    $a2 = strcmp(binCode, bin_6);
    $a3 = strcmp(binCode, bin_7);
    $t0 = strcmp(binCode, bin_8);
    $t1 = strcmp(binCode, bin_9);
    $t2 = strcmp(binCode, bin_10);
    $t3 = strcmp(binCode, bin_11);
    $t4 = strcmp(binCode, bin_12);
    $t5 = strcmp(binCode, bin_13);
    $t6 = strcmp(binCode, bin_14);
    $t7 = strcmp(binCode, bin_15);
    $s0 = strcmp(binCode, bin_16);
    $s1 = strcmp(binCode, bin_17);
    $s2 = strcmp(binCode, bin_18);
    $s3 = strcmp(binCode, bin_19);
    $s4 = strcmp(binCode, bin_20);
    $s5 = strcmp(binCode, bin_21);
    $s6 = strcmp(binCode, bin_22);
    $s7 = strcmp(binCode, bin_23);
    $t8 = strcmp(binCode, bin_24);
    $t9 = strcmp(binCode, bin_25);
    $k0 = strcmp(binCode, bin_26);
    $k1 = strcmp(binCode, bin_27);
    $gp = strcmp(binCode, bin_28);
    $sp = strcmp(binCode, bin_29);
    $fp = strcmp(binCode, bin_30);
    $ra = strcmp(binCode, bin_31);

    if ($zero == 0)
    {
        reg = 0;
    }
    else if ($at == 0)
    {
        reg = 1;
    }
    else if ($v0 == 0)
    {
        reg = 2;
    }
    else if ($v1 == 0)
    {
        reg = 3;
    }
    else if ($a0 == 0)
    {
        reg = 4;
    }
    else if ($a1 == 0)
    { // 5
        reg = 5;
    }
    else if ($a2 == 0)
    {
        reg = 6;
    }
    else if ($a3 == 0)
    {

        reg = 7;
    }
    else if ($t0 == 0)
    {
        reg = 8;
    }
    else if ($t1 == 0)
    {
        reg = 9;
    }
    else if ($t2 == 0)
    { // 10
        reg = 10;
    }
    else if ($t3 == 0)
    {
        reg = 11;
    }
    else if ($t4 == 0)
    {
        reg = 12;
    }
    else if ($t5 == 0)
    {
        reg = 13;
    }
    else if ($t6 == 0)
    {
        reg = 14;
    }
    else if ($t7 == 0)
    { // 15
        reg = 15;
    }
    else if ($s0 == 0)
    {
        reg = 16;
    }
    else if ($s1 == 0)
    {
        reg = 17;
    }
    else if ($s2 == 0)
    {
        reg = 18;
    }
    else if ($s3 == 0)
    {
        reg = 19;
    }
    else if ($s4 == 0)
    {
        reg = 20;
    }
    else if ($s5 == 0)
    {
        reg = 21;
    }
    else if ($s6 == 0)
    {
        reg = 22;
    }
    else if ($s7 == 0)
    {
        reg = 23;
    }
    else if ($t8 == 0)
    {
        reg = 24;
    }
    else if ($t9 == 0)
    {
        reg = 25;
    }

    else if ($k0 == 0)
    {
        reg = 26;
    }
    else if ($k1 == 0)
    {
        reg = 27;
    }
    else if ($gp == 0)
    {
        reg = 28;
    }
    else if ($sp == 0)
    {
        reg = 29;
    }
    else if ($fp == 0)
    {
        reg = 30;
    }
    else if ($ra == 0)
    {
        reg = 31;
    }
    else
    {
        printf("Error - No RegisterFile Accessed\n");
        exit(1);
    }

    
    return reg; // return the int number to be displayed
} // end of helper function

// Function used to change binary character strings to integers
int binToDec(char binCode[])
{

    // printf("the binary code is: %s\n", binCode);

    while (binCode != NULL)
    {
        int base = strlen(binCode) - 1; // the base of 2 to be multiplied, we start of -1 because we dont account for the last bit here
        int sum = 0;
        // int count_of_zeros = 0;
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

    return 0; // so the compiler doesnt shoot an "non-return" warning
}

// Function used to write an int value to a register File
char RegWrite(char binCode[5], int value)
{

    // test
    //printf("/////////////////// -- Within Value to Register Write Function -- //////////////////\n");
    //printf("Binary Code currently looked at is: %s\n", binCode);

    // each char array represents a real register in MIPS
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

    // Register Files:

    int $zero;
    int $at;
    int $v0;
    int $v1;
    int $a0;
    int $a1;
    int $a2;
    int $a3;
    int $t0;
    int $t1;
    int $t2;
    int $t3;
    int $t4;
    int $t5;
    int $t6;
    int $t7;
    int $s0;
    int $s1;
    int $s2;
    int $s3;
    int $s4;
    int $s5;
    int $s6;
    int $s7;
    int $t8;
    int $t9;
    int $k0;
    int $k1;
    int $gp;
    int $sp;
    int $fp;
    int $ra;

    // comparing two binary values to then place the int 1 or 0 into corresponding RegFile:

    $zero = strcmp(binCode, bin_0);
    $at = strcmp(binCode, bin_1);
    $v0 = strcmp(binCode, bin_2);
    $v1 = strcmp(binCode, bin_3);
    $a0 = strcmp(binCode, bin_4);
    $a1 = strcmp(binCode, bin_5);
    $a2 = strcmp(binCode, bin_6);
    $a3 = strcmp(binCode, bin_7);
    $t0 = strcmp(binCode, bin_8);
    $t1 = strcmp(binCode, bin_9);
    $t2 = strcmp(binCode, bin_10);
    $t3 = strcmp(binCode, bin_11);
    $t4 = strcmp(binCode, bin_12);
    $t5 = strcmp(binCode, bin_13);
    $t6 = strcmp(binCode, bin_14);
    $t7 = strcmp(binCode, bin_15);
    $s0 = strcmp(binCode, bin_16);
    $s1 = strcmp(binCode, bin_17);
    $s2 = strcmp(binCode, bin_18);
    $s3 = strcmp(binCode, bin_19);
    $s4 = strcmp(binCode, bin_20);
    $s5 = strcmp(binCode, bin_21);
    $s6 = strcmp(binCode, bin_22);
    $s7 = strcmp(binCode, bin_23);
    $t8 = strcmp(binCode, bin_24);
    $t9 = strcmp(binCode, bin_25);
    $k0 = strcmp(binCode, bin_26);
    $k1 = strcmp(binCode, bin_27);
    $gp = strcmp(binCode, bin_28);
    $sp = strcmp(binCode, bin_29);
    $fp = strcmp(binCode, bin_30);
    $ra = strcmp(binCode, bin_31);

    // Decided to not return anything to the recieving variable, C is weird about returning characters:

    if ($zero == 0 || value == 0)
    {

        registerFile[0] = value;
        // return $zero;
    }
    else if ($at == 0)
    {
        registerFile[1] = value;
        // return $at;
    }
    else if ($v0 == 0)
    {
        registerFile[2] = value;
        // return $v0;
    }
    else if ($v1 == 0)
    {
        registerFile[3] = value;
        // return $v1;
    }
    else if ($a0 == 0)
    {
        registerFile[4] = value;
        // return $a0;
    }
    else if ($a1 == 0)
    { // 5
        registerFile[5] = value;
        // return $a1;
    }
    else if ($a2 == 0)
    {
        registerFile[6] = value;
        // return $a2;
    }
    else if ($a3 == 0)
    {

        registerFile[7] = value;
        // return $a3;
    }
    else if ($t0 == 0)
    {
        registerFile[8] = value;
        // return $t0;
    }
    else if ($t1 == 0)
    {
        registerFile[9] = value;
        // return $t1;
    }
    else if ($t2 == 0)
    { // 10
        registerFile[10] = value;
        // return $t2;
    }
    else if ($t3 == 0)
    {
        registerFile[11] = value;
        // return $t3;
    }
    else if ($t4 == 0)
    {
        registerFile[12] = value;
        // return $t4;
    }
    else if ($t5 == 0 || value == 13)
    {
        registerFile[13] = value;
        // return $t5;
    }
    else if ($t6 == 0)
    {
        registerFile[14] = value;
        // return $t6;
    }
    else if ($t7 == 0)
    { // 15
        registerFile[15] = value;
        // return $t7;
    }
    else if ($s0 == 0)
    {
        registerFile[16] = value;
        // return $s0;
    }
    else if ($s1 == 0)
    {
        registerFile[17] = value;
        return $s1;
    }
    else if ($s2 == 0)
    {
        registerFile[18] = value;
        //  return $s2;
    }
    else if ($s3 == 0)
    {
        registerFile[19] = value;
        // return $s3;
    }
    else if ($s4 == 0)
    {
        registerFile[20] = value;
        // return $s4;
    }
    else if ($s5 == 0)
    {
        registerFile[21] = value;
        // return $s5;
    }
    else if ($s6 == 0)
    {
        registerFile[22] = value;
        // return $s6;
    }
    else if ($s7 == 0)
    {
        registerFile[23] = value;
        // return $s7;
    }
    else if ($t8 == 0)
    {
        registerFile[24] = value;
        // return $t8;
    }
    else if ($t9 == 0)
    {
        registerFile[25] = value;
        // return $t9;
    }

    else if ($k0 == 0)
    {
        registerFile[26] = value;
        // return $k0;
    }
    else if ($k1 == 0)
    {
        registerFile[27] = value;
        // return $k1;
    }
    else if ($gp == 0)
    {
        registerFile[28] = value;
        /// return $gp;
    }
    else if ($sp == 0)
    {
        registerFile[29] = value;
        // return $sp;
    }
    else if ($fp == 0)
    {
        registerFile[30] = value;
        // return $fp;
    }
    else if ($ra == 0)
    {
        registerFile[31] = value;
        // return $ra;
    }
    else
    {
        printf("Error - No RegisterFile Accessed\n");
        exit(1);
    }

    printf("\n");
    printf("Project Criteria: \n");
    printf("$%d is modified to 0x%x\n",binToDec(binCode), registerFile[binToDec(binCode)]);
    printf("\n");
    return 0;
}

// Function to return an address from memory:
int Memory(int address)
{
    // we can return some int number directly from the memory array;
    printf("Loading the address from memory...\n");
    return d_mem[address] = address;
}

// Function to write back a value onto memory:
int WriteBack(int address, int value)
{
    // assigning the value directly to memory;
    d_mem[address] = value;
    printf("////////////////////////////// -- Write Back -- ///////////////////////////\n");
    printf("Address is: 0x%x and value is: %d\n", address, value);
    printf("\n");
    return 0;
}

// Function that gets the value from a register -- same as RegWrite for simplicity sake:
int RegGet(char binCode[5])
{

    // test
    // printf("/////////////////// -- Within RegGet Function -- //////////////////\n");
    // printf("Binary Code currently looked at is: %s\n", binCode);

    char bin_31[] = "11111";

    // Register File:
    int $ra;

    // comparing two binary values to then place the int 1 or 0 into corresponding RegFile:

    $ra = strcmp(binCode, bin_31);

    if ($ra == 0)
    {
        // registerFile[31] = value;
        return registerFile[31];
    }
    else
    {
        printf("Error - No RegisterFile Accessed\n");
        exit(1);
    }

    return 0;
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
