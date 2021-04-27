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
            index = ( length * i ) + j;

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

            index = ( length * i ) + j;

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
            index = ( length * i ) + j;
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

void print_other_grid( float *other_grid, int length, int t, std::string type )
{
    int i, j, index, other;

    int n_zero = 5;
    std::string num_string = std::to_string( t );

    int string_length = num_string.length();

    for ( int k = 0; k < n_zero - string_length; k++ )
    {
        num_string = "0" + num_string;
    }

    std::string filename = type + "_grid_t_" + num_string + ".out";
    std::ofstream outfile ( filename );

    for ( i = 0; i < length; i++)
    {
        for ( j = 0; j < length; j++ )
        {
            index = ( length * i ) + j;
            other = (other_grid)[ index ];

            outfile << other << ", ";
        }
        // std::cout << std::endl;
        outfile << std::endl;
    }

    outfile.close();
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

__device__
void accept_reject( float a, float q, float r, float m, float *x1_grid,
                    float *r1_grid, int index_global )
{
    float x1 = x1_grid[ index_global ];

    x1 = a * fmod( x1, q ) - ( r * x1 ) / q;

    if ( x1 < 0 )
    {
        x1 += m;
    }

    float r1 = x1 / m;

    x1_grid[ index_global ] = x1;
    r1_grid[ index_global ] = r1;
}

__global__
void GPUKernel_update_grid( int *d_grid, int length, float J, float beta, float a,
                                float q, float r, float m, float *d_x1_grid,
                                float *d_r1_grid, float *d_y_grid )
{
    // Compute the global location of the active thread.
    int x_global = blockIdx.x * blockDim.x + threadIdx.x;
    int y_global = blockIdx.y * blockDim.y + threadIdx.y;
    int index_global = ( length * x_global ) + y_global;

    int x_local = threadIdx.x;
    int y_local = threadIdx.y;
    int index_local = ( blockDim.y * x_local ) + y_local;

    // Declare shared data.
    extern __shared__ int shared[];

    // Populate the shared data array.
    (shared)[ index_local ] = (d_grid)[ index_global ];
    // shared[ ( blockDim.y * threadIdx.x ) + threadIdx.y ] =
    //     (d_grid)[ ( length * x_global ) + y_global ];

    // Wait for all threads to finish.
    __syncthreads();

    int x_up_local, x_down_local, x_up_global, x_down_global;
    int y_left_local, y_right_local, y_left_global, y_right_global;

    float up_index_energy, down_index_energy, left_index_energy, right_index_energy;

    // float energy_old, energy_new, y, x1, r1;
    float energy_old, energy_new, y, r1;
    bool change;

    // If the thread is within the bounds of the grid ...
    if ( ( x_global < length ) && ( y_global < length ) )
    {
        // Compute local neighboring indices.

        // If the thread is in the first row of threads in the local grid ...
        if ( threadIdx.x == 0 )
        {
            // There is no local memory going upwards.
            x_up_local = NULL;

            // If the upward neighbor is out of bounds of the global grid ...
            if ( ( x_global - 1 ) < 0 )
            {
                // Wrap around to the last row in the global grid.
                x_up_global = x_global - 1;
            }
            // Otherwise ...
            else
            {
                // Access the memory in the global grid one row above.
                x_up_global = x_global - 1;
            }

            // The downward neighbor is always at row 1 in the local grid.
            x_down_local = 1;
            // The downward global memory does not need to be accessed.
            x_down_global = NULL;

            up_index_energy   = (d_grid)[ length     * x_up_global  + y_global ];
            down_index_energy = (shared)[ blockDim.y * x_down_local + y_local  ];

        }
        // Else if the thread is in the last row of threads in the local grid ...
        else if ( threadIdx.x == ( blockDim.x - 1 ) )
        {
            // The upwards neighbor is in the row above in the local grid.
            x_up_local = blockDim.x - 2;
            // The global memory does not need to be accessed.
            x_up_global = NULL;

            // There is no local memory going downwards.
            x_down_local = NULL;

            // If the downwards neighbor is out of bounds of the global grid ...
            if ( ( x_global + 1 ) > ( length - 1 ) )
            {
                // Wrap around to the first row of the global grid.
                x_down_global = 0;
            }
            // Otherwise ...
            else
            {
                // Access the memory in the global grid one row below.
                x_down_global = x_global + 1;
            }

            up_index_energy   = (shared)[ blockDim.y * x_up_local    + y_local  ];
            down_index_energy = (d_grid)[ length     * x_down_global + y_global ];

        }
        // Else if the thread is neither in the first row nor the last row of the
        //  local grid.
        else
        {
            // The upwards neighbor is in the row above in the local grid.
            x_up_local = threadIdx.x - 1;
            // The global memory does not need to be accessed.
            x_up_global = NULL;

            // The downwards neighbor is in the row below in the local grid.
            x_down_local = threadIdx.x + 1;
            // The global memory does not need to be accessed.
            x_down_global = NULL;

            up_index_energy   = (shared)[ blockDim.y * x_up_local   + y_local ];
            down_index_energy = (shared)[ blockDim.y * x_down_local + y_local ];
        }

        // If the thread is in the first column of threads in the local grid ...
        if ( threadIdx.y == 0 )
        {
            // There is no local memory going leftwards.
            y_left_local = NULL;

            // If the leftwards neighbor is out of bounds of the global grid ...
            if ( ( y_global - 1 ) < 0 )
            {
                // Wrap around to the last column in the global grid.
                y_left_global = y_global - 1;
            }
            // Otherwise ...
            else
            {
                // Access the memory in the global grid one column to the left.
                y_left_global = y_global - 1;
            }

            // The rightwards neighbor is always at column 1 in the local grid.
            y_right_local = 1;
            // The global memory does not need to be accessed.
            y_right_global = NULL;

            left_index_energy  = (d_grid)[ length     * x_global + y_left_global ];
            right_index_energy = (shared)[ blockDim.y * x_local  + y_right_local ];
        }
        // Else if the thread is in the last column of threads in the local grid ...
        else if ( threadIdx.y == ( blockDim.y - 1 ) )
        {
            // The leftwards neighbor is in the column to the left in the local grid.
            y_left_local = blockDim.y - 2;
            // The global memory does not need to be accessed.
            y_left_global = NULL;

            // There is no local memory going rightwards.
            y_right_local = NULL;

            // If the rightwards neighbor is out of bounds of the global grid ...
            if ( ( y_global + 1 ) > ( length - 1 ) )
            {
                // Wrap around to the first column of the global grid.
                y_right_global = 0;
            }
            // Otherwise ...
            else
            {
                // Access the memory in the global grid one column to the right.
                y_right_global = y_global + 1;
            }

            left_index_energy  = (shared)[ blockDim.y * x_local  + y_left_local   ];
            right_index_energy = (d_grid)[ length     * x_global + y_right_global ];

        }
        // Else if the thread is neither in the first column nor the last column
        //  of the local grid.
        else
        {
            // The leftwards neighbor is in the column to the left in the local grid.
            y_left_local = threadIdx.y - 1;
            // The global memory does not need to be accessed.
            y_left_global = NULL;

            // The rightwards neighbor is in the column to the right in the local grid.
            y_right_local = threadIdx.y + 1;
            // The global memory does not need to be accessed.
            y_right_global = NULL;

            left_index_energy  = (shared)[ blockDim.y * x_local + y_left_local  ];
            right_index_energy = (shared)[ blockDim.y * x_local + y_right_local ];
        }

        energy_old = -J * (shared)[ index_local ] * ( up_index_energy + down_index_energy
            + left_index_energy + right_index_energy );

        energy_new = - energy_old;

        if ( energy_new <= energy_old )
        {
            change = true;
        }
        else
        {
            y = exp( -beta * ( energy_new - energy_old ) );

            d_y_grid[ index_global ] = y;

            accept_reject( a, q, r, m, d_x1_grid, d_r1_grid, index_global );

            r1 = d_r1_grid[ index_global ];

            // printf( "r1: %f, y: %f", r1, y );

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
            (d_grid)[ index_global ] = -(d_grid)[ index_global ];
        }



    }

}

// void update_grid( int *grid, int length, float J, float beta, float a, float q,
//                         float r, float m, float *x1_grid, float *r1_grid )
// {
//     int i, j, i_up, i_down, j_left, j_right;
//     int index, up_index, down_index, left_index, right_index;
//     float energy_old, energy_new, y, r1;
//     bool change;
//
//     for ( i = 0; i < length; i++ )
//     {
//         for ( j = 0; j < length; j++ )
//         {
//             index = ( length * i ) + j;
//
//             if ( i == 0 )
//             {
//                 i_up = 1;
//                 i_down = length - 1;
//             }
//             else if ( i == length - 1)
//             {
//                 i_up = 0;
//                 i_down = i - 1;
//             }
//             else
//             {
//                 i_up = i + 1;
//                 i_down = i - 1;
//             }
//             if ( j == 0 )
//             {
//                 j_left = length - 1;
//                 j_right = 1;
//             }
//             else if ( j == length - 1)
//             {
//                 j_left = j - 1;
//                 j_right = 0;
//             }
//             else
//             {
//                 j_left = j - 1;
//                 j_right = j + 1;
//             }
//
//             up_index    = ( length * i_up )   + j;
//             down_index  = ( length * i_down ) + j;
//             left_index  = ( length * i )      + j_left;
//             right_index = ( length * i )      + j_right;
//
//             energy_old = -J * (grid)[ index ] * ( (grid)[ up_index ] + (grid)[ down_index ]
//                 + (grid)[ left_index ] + (grid)[ right_index ] );
//
//             energy_new = - energy_old;
//
//             if ( energy_new <= energy_old )
//             {
//                 change = true;
//             }
//             else
//             {
//                 y = exp( -beta * ( energy_new - energy_old ) );
//                 accept_reject( y, a, q, r, m, x1_grid, r1_grid, index );
//
//                 r1 = r1_grid[ index ];
//
//                 if ( r1 <= y )
//                 {
//                     change = true;
//                 }
//                 else
//                 {
//                     change = false;
//                 }
//             }
//
//             if ( change == true )
//             {
//                 (grid)[ index ] = -(grid)[ index ];
//             }
//         }
//     }
// }



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

    float a = pow( 7., 5 );
    float m = pow( 2., 31 ) - 1.;

    float q = m / a;
    float r = fmod( m, a );

    int *h_grid;
    h_grid = (int *)malloc( sizeof(int) * size );
    int *d_grid;
    cudaMalloc( (void **)&d_grid, sizeof(int) * size );

    float *h_x1_grid;
    h_x1_grid = (float *)malloc( sizeof(float) * size );
    float *d_x1_grid;
    cudaMalloc( (void **)&d_x1_grid, sizeof(float) * size );

    float *h_r1_grid;
    h_r1_grid = (float *)malloc( sizeof(float) * size );
    float *d_r1_grid;
    cudaMalloc( (void **)&d_r1_grid, sizeof(float) * size );

    float *h_y_grid;
    h_y_grid = (float *)malloc( sizeof(float) * size );
    float *d_y_grid;
    cudaMalloc( (void **)&d_y_grid, sizeof(float) * size );

    initialize_x1_grid( a, q, r, m, h_x1_grid, length );
    initialize_grid( h_grid, length );
    // print_grid( h_grid, length, 0 );

    cudaMemcpy( d_grid, h_grid, sizeof(int) * size, cudaMemcpyHostToDevice );
    cudaMemcpy( d_x1_grid, h_x1_grid, sizeof(float) * size, cudaMemcpyHostToDevice );
    cudaMemcpy( d_r1_grid, h_r1_grid, sizeof(float) * size, cudaMemcpyHostToDevice );

    // print_other_grid( h_x1_grid, length, 0, "x1" );

    float *d2h_x1_grid;
    d2h_x1_grid = (float *)malloc( sizeof(float) * size );

    // cudaMemcpy( d2h_x1_grid, d_x1_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );

    // print_other_grid( d2h_x1_grid, length, 1, "x1");

    for ( int t = 1; t < trajecs; t++ )
    {
        GPUKernel_update_grid<<< dimGrid, dimBlock, sizeof(int) * blockwidth * blockwidth >>>
            ( d_grid, length, J, beta, a, q, r, m, d_x1_grid, d_r1_grid, d_y_grid );
        cudaDeviceSynchronize();

        // update_grid( grid, length, J, beta, a, q, r, m, x1_grid, r1_grid );

        // cudaMemcpy( h_grid, d_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );
        // print_grid( h_grid, length, t );

        // print_grid( grid, length, t );

        cudaMemcpy( d2h_x1_grid, d_x1_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );
        print_other_grid( d2h_x1_grid, length, t, "x1" );

        cudaMemcpy( h_r1_grid, d_r1_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );
        print_other_grid( h_r1_grid, length, t, "r1" );

        cudaMemcpy( h_y_grid, d_y_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );
        print_other_grid( h_y_grid, length, t, "y" );
    }

    // cudaMemcpy( h_grid, d_grid, sizeof(int) * size, cudaMemcpyDeviceToHost );
    //
    // print_grid( h_grid, length, 999999 );










}
