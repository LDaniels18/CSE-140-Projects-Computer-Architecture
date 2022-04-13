#include <stdio.h>

int main()
{

    // declare the 2D array: data type array name[num of rows][num of columns]
    int num_row = 2;
    int num_col = 2;

    int A[num_row][num_col]; // empty array
    int B[num_row][num_col]; // non empty 2x3 matric (value content = no.row x no.col)
    // B[0][0] = 0;

    printf("Filling in B: ");
    // logic to fill in the second array:
    for (int I = 0; I < num_row; I++)
    {
        for (int J = 0; J < num_col; J++)
        {
            if (J == 0)
            {
                B[I][J] = 0;             // incrementing by 1 to fill in the B array
                printf("|%d|", B[I][J]); // printing out the contents of the matrixes
            }
            else if (J > 0)
            {
                B[I][J]++;               // increment by 1
                printf("|%d|", B[I][J]); // printing out the contents of the matrixes
            }
            if (J == num_col - 1) // to space out the half of the matrix.... looks better to the viewer!
            {
                printf("\n");
            }
        }
    }

    printf("Filling in A: ");
    // logic to fill in first array:
    for (int I = 0; I < num_row; I++)
    {
        for (int J = 0; J < num_col; J++)
        {
            A[I][J] = (B[I][J] * 4); // math that will be applied to elements of B array

            printf("|%d|", A[I][J]); // printing out the contents of the matrixes

            if (J == num_col - 1) // to space out the half of the matrix.... looks better to the viewer!
            {
                printf("\n");
            }
        }
    }

    return 0; // end the program
}