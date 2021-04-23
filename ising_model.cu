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


void initialize_lattice( int *grid, int length )
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

void print_lattice( int *grid, int length )
{
    int i, j, index;
    for ( i = 0; i < length; i++)
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            std::cout << (grid)[index] << std::endl;
        }
    }
}

void determine_ij( int i, int j, int length, int *ij ):
{
    int i_up, i_down, j_left, j_right;

    if ( i == 0 )
    {
        i_up = 1;
        i_down = length - 1;
    }
    else if ( i == length - 1)
    {
        i_up = 0;
        i_down = i - 1;
    }
    else
    {
        i_up = i + 1;
        i_down = i - 1;
    }
    if ( j == 0 )
    {
        j_left = length - 1;
        j_right = 1;
    }
    else if ( j == length - 1)
    {
        j_left = j - 1;
        j_right = 0;
    }
    else
    {
        j_left = j - 1;
        j_right = j + 1;
    }

    // int *ij;
    // ij = (int *)malloc( sizeof(int) * 4 );
    ij[0] = i_up;
    ij[1] = i_down;
    ij[2] = j_left;
    ij[3] = j_right;
}

void update_lattice( int *grid, int length )
{
    int i, j, index;
    int *ij;
    ij = (int *)malloc( sizeof(int) * 4 );

    for ( i = 0; i < length; i++)
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            determine_ij( i, j, length, ij );

            std::cout << "up: " << ij[0] << ", down: " << ij[1] << ", left: " << ij[2] << ", right: " << ij[3] << std::endl;
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

    int *grid;
    grid = (int *)malloc( sizeof(int) * size );

    initialize_lattice( grid, length );
    print_lattice( grid, length );










}
