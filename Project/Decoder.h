#ifndef DECODER_H_   /* Include guard */
#define DECODER_H_

//int foo(int x);  /* An example function declaration */

void Decode(char instruction[32]); //function to actually decode
int registers(char binCode[5]); // declaring the helper function by passing the instruction char array
int binToDec(char binCode[]);   // a function to change binary to dec (of any size)


#endif // FOO_H_