#ifndef FUNCTIONHANDLER_H_   /* Include guard */
#define FUNCTIONHANDLER_H_

//int foo(int x);  /* An example function declaration */

int DecodeAndExecute(char instruction[32]); //function to actually decode
int registerfile(char binCode[5]); // declaring the helper function by passing the instruction char array
int binToDec(char binCode[]);   // a function to change binary to dec (of any size)
int RegisterValuestoRegisterFiles(char binCode[5], int value); //take a particular set if RD and RS and do some type of atithmetic to assign a value to a regFile;



#endif // FOO_H_