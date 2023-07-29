#include "pch.h"

float Q_rsqrt(float); // prototype for the function.

int reallyNotmain () 
{
	int x {0}, y {0};	// x and y are initialized to 0. this are braced initialization. 
						// this kind of initialization is more efficient than the other kind of initialization.
						// it was introduced in C++11.

	for (int i{0}; i < 100; i++)	// this is a for loop with braced initialization
	{
		x += i;
		y += i;
	}

	sizeof(int*); // this returns the size of a pointer to int. 
				  // in 32 bit systems, this is 4 bytes. 
				  // in 64 bit systems, this is 8 bytes.

	sizeof(int); // this returns the size of an int. 
				 // in 32 bit systems, this is 4 bytes. 
				 // in 64 bit systems, this is 4 bytes.

	int** a2d = new int*[10];	// this is a 2d array with 10 pointers to int arrays. 
								// (this reserves memory for the 10 pointers. the type only determines the size of the memory reserved for each row)
								// the size of this array is 10 * sizeof(int*) = 10 * 8 = 80 bytes
	for (int i{0}; i < 10; i++)
	{
		a2d[i] = new int[10]; // this allocates memory for a new 10 element array and stores the pointer to its location. 
							  // (this reserves memory for each row. the type only determines the size of the memory reserved for each element)
							  // the size of each row is 10 * sizeof(int) = 10 * 4 = 40 bytes
	}

	for (int i{0}; i < 10; i++)
	{
		for (int j{0}; j < 10; j++)
		{
			a2d[i][j] = i * j;	// initializing each element of the 2d array
		}
	}
	
	for (int i{0}; i < 10; i++)
	{
		delete[] a2d[i];	// deleting each row
	}
	delete[] a2d;	// deleting the 2d array


	// all of the above can be done with a 1-dimensional array:
	int* a1d = new int[10 * 10];	// this is a 1d array with 100 elements. 
									// (this reserves memory for the 100 elements. the type only determines the size of the memory reserved for each element)
									// the size of this array is 100 * sizeof(int) = 100 * 4 = 400 bytes

	for (int i{0}; i < 10; i++)
	{
		for (int j{0}; j < 10; j++)
		{
			a1d[i * 10 + j] = i * j;	// initializing each element of the 1d array
		}
	}

	delete[] a1d;	// deleting the 1d array


	// Handling multi-dimensional arrays in a single contigous array is called row-major order.
	// The first index is the row, and the second index is the column.
	// This is more efficient in terms of speed and memory usage, because the memory is allocated in a single contigous block.
	// This reduces the number of memory allocations and deallocations, and also reduces the number of cache misses.
	 
	float inverseSqRoot = Q_rsqrt(2.0f); // this is a function call. 
										 // the function is defined in src\InvFastSqrt.cpp
	float inverseSqRoot2 = Q_rsqrt(2.0f); // this is a function call. 
										  // the function is defined in src\InvFastSqrt.cpp

	return 0;
}