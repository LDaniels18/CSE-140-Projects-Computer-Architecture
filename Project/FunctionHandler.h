#ifndef FUNCTIONHANDLER_H_   /* Include guard */
#define FUNCTIONHANDLER_H_

//int foo(int x);  /* An example function declaration */

int DecodeAndExecute(char instruction[32], int pc_val); //function to actually decode
int registerfile(char binCode[5]); // declaring the helper function by passing the instruction char array
int binToDec(char binCode[]);   // a function to change binary to dec (of any size)
char RegisterValuestoRegisterFiles(char binCode[5], int value); //take a particular set if RD and RS and do some type of atithmetic to assign a value to a regFile;
int Memory(int address);
int WriteBack(int address, int value);


#endif // FOO_H_