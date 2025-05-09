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
#include <stdlib.h>
#include <stdio.h>
#include <iostream>                 // For printing to screen.
#include <math.h>                   // For sqrt and atan2.
#include <unistd.h>
#include <fstream>
// #include <cuda.h>                   // For CUDA parallelization on GPU.
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
                (grid)[ index ] = -1;
            }
            else
            {
                (grid)[ index ] = 1;
            }
        }
    }
}

void print_lattice( int *grid, int length, int t )
{
    int i, j, index, spin;

    // std::string new_string = std::string(n_zero - old_string.length(), '0') + old_string;

    // std::string filename = "data/20210423_001_grid_t_" + std::to_string( t ) + ".out";

    // std::string filename = "grid_t_" + std::to_string( t ) + ".out";

    int n_zero = 5;
    std::string num_string = std::to_string( t );
    // std::string padded_num_string = std::string( n_zero - num_string.length(), '0' ) + num_string;
    // std::string filename = "grid_t_" + padded_num_string;
    // std::ofstream outfile ( num_string );

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

    // int *ij;
    // ij = (int *)malloc( sizeof(int) * 4 );
    ij[0] = i_up;
    ij[1] = i_down;
    ij[2] = j_left;
    ij[3] = j_right;
}

void accept_reject( float y, float a, float q, float r, float m, float *x1r1 )
{

    float x1 = x1r1[0];
    x1 = a * fmod( x1, q ) - ( r * x1 ) / q;

    if ( x1 < 0 )
    {
        x1 += m;
    }

    float r1 = x1 / m;

    x1r1[0] = x1;
    x1r1[1] = r1;

    // std::cout << "x1: " << x1 << ", r1: " << r1 << std::endl;

}

void update_lattice( int *grid, int length, float J, float beta,
                        float a, float q, float r, float m, int *ij, float *x1r1 )
// void update_lattice( int *grid, int length, float J, float beta, int *ij )
{
    int i, j, index, up_index, down_index, left_index, right_index;
    // float n;
    float energy_old, energy_new, y, r1;
    // float energy_old, energy_new, y;
    bool change;

    for ( i = 0; i < length; i++ )
    {
        for ( j = 0; j < length; j++ )
        {
            index = length * i + j;
            determine_ij( i, j, length, ij );

            up_index    = length * ij[0] + j;
            down_index  = length * ij[1] + j;
            left_index  = length * i + ij[2];
            right_index = length * i + ij[3];

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
                accept_reject( y, a, q, r, m, x1r1 );
                // n = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                // x1 = x1r1[0];
                r1 = x1r1[1];

                // std::cout << "y: " << y << ", r1: " << r1 << std::endl;

                if ( r1 <= y )
                // if ( n <= y )
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

            // std::cout << "up: " << ij[0] << ", down: " << ij[1] << ", left: " << ij[2] << ", right: " << ij[3] << std::endl;
        }
    }
}



int main( int argc, char *argv[] )
{
    if ( argc != 5 )
    {
        // Print out the necessary command line imputs.
        printf( "Arguments for execution: %s <filename> <length> <J> <beta> <trajecs>\n", argv[0] );
    }

    int length = std::stoi( argv[1] );
    int size = length * length;

    float J = std::stof( argv[2] );
    float beta = std::stof( argv[3] );
    int trajecs = std::stoi( argv[4] );

    int *grid;
    grid = (int *)malloc( sizeof(int) * size );

    int *ij;
    ij = (int *)malloc( sizeof(int) * 4 );

    float *x1r1;
    x1r1 = (float *)malloc( sizeof(float) * 2 );

    float a = pow( 7., 5 );
    float m = pow( 2., 31 ) - 1.;

    float q = m / a;
    float r = fmod( m, a );

    float x1 = pow( 5.5, 13 );
    x1r1[0] = x1;

    // std::cout << "a: " << a << ", m: " << m << ", q: " << q << ", r: " << r << ", x1: " << x1 << std::endl;

    // std::cout << "fmod(3.5, 2): " << fmod(3.5, 2) << std::endl;

    initialize_lattice( grid, length );
    // print_lattice( grid, length, 0 );

    /*
    struct timeval comp_start, comp_end;
    gettimeofday( &comp_start, NULL );
    */

    for ( int t = 1; t < trajecs; t++ )
    {
        update_lattice( grid, length, J, beta, a, q, r, m, ij, x1r1 );
        print_lattice( grid, length, t );
    }

    /*
    gettimeofday( &comp_end, NULL );

    float comp_time_microseconds = ( comp_end.tv_sec * 1000000 + comp_end.tv_usec )
        - ( comp_start.tv_sec * 1000000 + comp_start.tv_usec );
    float comp_time_milliseconds = comp_time_microseconds / 1000.;

    printf( "%d, %f, %f, %d, ", length, J, beta, trajecs );
    printf( "%lf\n", comp_time_milliseconds );
    */







}
