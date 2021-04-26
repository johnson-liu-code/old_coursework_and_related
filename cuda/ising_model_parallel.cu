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
#include <fstream>
#include <cuda.h>                   // For CUDA parallelization on GPU.
// =====================================================================================================


void initialize_grid( int *grid, int length )
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
                (grid)[ index ] = -1;
            }
            else
            {
                (grid)[ index ] = 1;
            }
        }
    }
}

void initialize_x1_grid( float a, float q, float r, float m, float *x1_grid, int length )
{
    int i, j, index;
    float x1 = pow( 5.5, 13 );

    for ( i = 0; i < length; i++ )
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;

            x1 = a * fmod( x1, q ) - ( r * x1 ) / q;

            if ( x1 < 0 )
            {
                x1 += m;
            }

            x1_grid[ index ] = x1;
        }
    }
}

void print_grid( int *grid, int length, int t )
{
    int i, j, index, spin;

    int n_zero = 5;
    std::string num_string = std::to_string( t );

    int string_length = num_string.length();

    for ( int k = 0; k < n_zero - string_length; k++ )
    {
        num_string = "0" + num_string;
    }

    std::string filename = "grid_t_" + num_string + ".out";
    std::ofstream outfile ( filename );

    for ( i = 0; i < length; i++)
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            spin = (grid)[ index ];

            if ( spin == 1)
            {
                // std::cout << " " << 1 <<  ", ";
                outfile << " " << 1 <<  ", ";
            }
            else
            {
                // std::cout << -1 <<  ", ";
                outfile << -1 <<  ", ";
            }
        }
        // std::cout << std::endl;
        outfile << std::endl;
    }

    outfile.close();
}

void initialize_ij_grid( int *ij_grid, int length )
{
    int *ij;
    ij = (int *)malloc( sizeof(int) * 4 );

    int i, j, index;

    for ( i = 0; i < length, i++ )
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            determine_ij( i, j, length, ij);
            ij_grid[ index ] = ij;
        }
    }
}

void determine_ij( int i, int j, int length, int *ij )
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

    ij[0] = i_up;
    ij[1] = i_down;
    ij[2] = j_left;
    ij[3] = j_right;
}

void accept_reject( float y, float a, float q, float r, float m, float *x1_grid,
                    float *r1_grid, int index )
{
    float x1 = x1_grid[ index ];

    x1 = a * fmod( x1, q ) - ( r * x1 ) / q;

    if ( x1 < 0 )
    {
        x1 += m;
    }

    float r1 = x1 / m;

    // std::cout << "x1: " << x1 << ", r1: " << r1 << std::endl;

    x1_grid[ index ] = x1;
    r1_grid[ index ] = r1;
}

__global__
void GPUKenel_update_grid( int *grid, int length, float J, float beta, float a, float q,
                            float r, float m, int *ij, float *x1_grid, float *r1_grid,
                            int blockwidth )
{
    // Compute the global location of the active thread.
    int global_id_x = blockIdx.x * blockDim.x + threadIdx.x;
    int global_id_y = blockIdx.y * blockDim.y + threadIdx.y;

    // Declare shared data.
    extern __shared__ int shared[];

    // Populate the shared data array.
    shared[ threadIdx.x * blockwidth + threadIdx.y ] =
        (grid)[ global_id_x * length + global_id_y ];

    // Wait for all threads to finish.
    __syncthreads();

    if ( ( global_id_x < length ) && ( global_id_y < length ) )
    {

    }

}

void update_grid( int *grid, int length, float J, float beta, float a, float q,
                        float r, float m, int *ij_grid, float *x1_grid, float *r1_grid )
{
    int i, j, index, up_index, down_index, left_index, right_index;
    float energy_old, energy_new, y, r1;
    bool change;

    int *ij;
    ij = (int *)malloc( sizeof(int) * 4 );

    for ( i = 0; i < length; i++ )
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            // determine_ij( i, j, length, ij );

            up_index    = length * ij_grid[ index ][0] + j;
            down_index  = length * ij_grid[ index ][1] + j;
            left_index  = length * i + ij_grid[ index ][2];
            right_index = length * i + ij_grid[ index ][3];

            energy_old = -J * (grid)[ index ] * ( (grid)[ up_index ] + (grid)[ down_index ]
                + (grid)[ left_index ] + (grid)[ right_index ] );

            energy_new = - energy_old;

            if ( energy_new <= energy_old )
            {
                change = true;
            }
            else
            {
                y = exp( -beta * ( energy_new - energy_old ) );
                accept_reject( y, a, q, r, m, x1_grid, r1_grid, index );

                r1 = r1_grid[ index ];

                // std::cout << "y: " << y << ", r1: " << r1 << std::endl;

                if ( r1 <= y )
                {
                    change = true;
                }
                else
                {
                    change = false;
                }
            }

            if ( change == true )
            {
                (grid)[ index ] = -(grid)[ index ];
            }
        }
    }
}



int main( int argc, char *argv[] )
{
    if ( argc != 6 )
    {
        // Print out the necessary command line imputs.
        printf( "Arguments for execution: %s <filename> <length> <J> <beta> <trajecs> <blocksize>\n", argv[0] );
    }

    int length = std::stoi( argv[1] );
    int size = length * length;

    float J = std::stof( argv[2] );
    float beta = std::stof( argv[3] );
    int trajecs = std::stoi( argv[4] );

    int blockwidth = std::stoi( argv[5] );
    // The number of thread blocks in the x, y, and z directions.
    dim3 dimGrid( length/blockwidth, length/blockwidth, 1 );
    // The number of threads in the x, y, and z directions of a thread block.
    dim3 dimBlock( blockwidth, blockwidth, 1 );

    int *grid;
    grid = (int *)malloc( sizeof(int) * size );
    float *x1_grid;
    x1_grid = (float *)malloc( sizeof(float) * size );
    float *r1_grid;
    r1_grid = (float *)malloc( sizeof(float) * size );

    int *ij;
    ij = (int *)malloc( sizeof(int) * 4 );

    int *ij_grid;
    ij_grid = (int *)malloc( sizeof(int) * 4 * size );

    float a = pow( 7., 5 );
    float m = pow( 2., 31 ) - 1.;

    float q = m / a;
    float r = fmod( m, a );

    initialize_ij_grid( ij_grid, length );
    initialize_x1_grid( a, q, r, m, x1_grid, length );
    initialize_grid( grid, length );
    print_grid( grid, length, 0 );

    for ( int t = 1; t < trajecs; t++ )
    {
        update_grid( grid, length, J, beta, a, q, r, m, ij, x1_grid, r1_grid );
        print_grid( grid, length, t );
    }










}
