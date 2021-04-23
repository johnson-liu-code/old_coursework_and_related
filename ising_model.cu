// ################################################################################################## //
//                                     ising_model.cu                                                 //
// ################################################################################################## //
/*
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Johnson Liu ( j_liu21@u.pacific.edu ) 20210422                                                     //
// University of the Pacific                                                                          //
// CA USA                                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////////
########################################################################################################
--------------------------------------------------------------------------------------------------------
Functions of the code: ---------------------------------------------------------------------------------
    1)

--------------------------------------------------------------------------------------------------------
Notes: -------------------------------------------------------------------------------------------------
    1)

--------------------------------------------------------------------------------------------------------
Input: -------------------------------------------------------------------------------------------------
    1)

--------------------------------------------------------------------------------------------------------
Output: ------------------------------------------------------------------------------------------------
    A) To screen:
        1)

    B) Printed to ... :
        1)
--------------------------------------------------------------------------------------------------------
########################################################################################################
--------------------------------------------------------------------------------------------------------
1st Update

--------------------------------------------------------------------------------------------------------

########################################################################################################
*/
// =====================================================================================================
// Import libraries to use various functions.
#include <time.h>                   // For measuring runtimes.
#include <sys/time.h>               // For measuring runtimes.
#include <stdlib.h>                 /* srand, rand */
#include <stdio.h>                  // For interaction with console.
#include <iostream>                 // For printing to screen (std::cout, std::endl).
#include <cuda.h>                   // For CUDA parallelization on GPU.
// =====================================================================================================




// float accept_reject( float x1, float y, float a, float q, float r, float m ):
// {
//     // Generate random number.
//     x1 = a*(x1 % q) - (r*x1)/q
//
//     if x1 < 0:
//         x1 += m
//
//     r1 = x1/m
//
//     // If random number is less than y, change the spin.
//     if r1 <= y:
//         change = True
//     else:
//         change = False
//
//     return x1
// }

void initialize_lattice( float *grid, int length )
{
    int i, j, index;
    float r;
    for ( i = 0; i < length; i++ )
    {
        for ( j = 0; j < length; j++ )
        {
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            index = length * i + j;

            if ( r <= 0.5 )
            {
                (grid)[index] = -1;
            }
            else
            {
                (grid)[index] = 1;
            }
        }
    }
}


int main( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        // Print out the necessary command line imputs.
        printf( "Arguments for execution: %s <filename> <length>\n", argv[0] );
    }

    int length = std::stoi( argv[1] );
    int size = length * length;

    // float a = pow( 7., 5. );
    // float m = pow( 2., 31. ) - 1;
    // float c = 0;
    //
    // float q = m / a;
    // float r = m % a;

    // float x1 = pow( 5.5, 13. ) ;

    int *grid;
    grid = (int *)malloc( sizeof(int) * size );

    // int i, j, index;
    // float r;
    // for ( i = 0; i < length; i++ )
    // {
    //     for ( j = 0; j < length; j++ )
    //     {
    //         r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //         index = length * i + j;
    //
    //         if ( r <= 0.5 )
    //         {
    //             grid[index] = -1;
    //         }
    //         else
    //         {
    //             grid[index] = 1;
    //         }
    //
    //     }
    // }

    int i, j, index;
    for ( i = 0; i < length; i++)
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            std::cout << &grid[index] << std::endl;
        }
    }








}
