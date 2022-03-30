#include "Decoder.h"


// a function exclusive for R Type Instructions:
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
        int count_of_zeros = 0;
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
