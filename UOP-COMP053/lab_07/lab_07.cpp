#include<iostream>
#include<stdlib.h>


// Return true if every element is larger than the previous. Return false otherwise.
bool isAscending(int* array, int array_size, int i)
{
    if ( i+1 >= array_size )
    {
        return true;
    }
    if ( array[i+1] < array[i] )
    {
        return false;
    }

    isAscending(array, array_size, i+1);
}

// Return true if two arrays are the same. Return false otherwise.
bool Compare(int* array1, int* array2, int array1_size, int i)
{
    if (i > array1_size)
    {
        return true;
    }
    if (array1[i] != array2[i])
    {
        return false;
    }

    Compare(array1, array2, array1_size, i+1);
}

// Return the sum of the elements in an array.
int getTotal(int* array, int array_size, int i, int total)
{
    if (i > array_size)
    {
        return total;
    }

    total = total + array[i] + getTotal(array, array_size, i+1, total);
}

// Return the position of an element. Return -1 if the element is not found in the array.
int findElement(int* array, int array_size, int integer, int i)
{
    if (array[i] == integer)
    {
        return i;
    }
    if (i > array_size)
    {
        return -1;
    }

    findElement(array, array_size, integer, i+1);
}

// Return the number of occurences of an element in an array.
int countElement(int* array, int array_size, int integer, int i, int count)
{
    int yes = 0;

    if (i == array_size)
    {
        return count;
    }
    if (array[i] == integer)
    {
        yes = 1;
    }

    count = count + yes + countElement(array, array_size, integer, i+1, count);
}

int main()
{
    // Initialize arrays
    int array01[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int array02[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int array03[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int array04[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int array05[20] = {3, 3, 3, 3, 6, 6, 6, 6, 9, 9, 9, 9, 12, 12, 12, 12, 15, 15, 15, 15};
    int array06[20] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    int array07[20] = {0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int array08[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int array09[20] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    int array10[20] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    // Testing isAscending()
        // Test array01
        std::cout << isAscending(array01, 20, 0) << std::endl;
        // Test array03
        std::cout << isAscending(array03, 20, 0) << std::endl;
        // Test array04
        std::cout << isAscending(array04, 20, 0) << std::endl;
        // Test array10
        std::cout << isAscending(array10, 20, 0) << std::endl;
        // Test array06
        std::cout << isAscending(array06, 20, 0) << std::endl;

    // Testing Compare()
        // Testing array01 and array02
        std::cout << Compare(array01, array02, 20, 0) << std::endl;
        // Testing array03 and array04
        std::cout << Compare(array03, array04, 20, 0) << std::endl;
        // Testing array04 and array08
        std::cout << Compare(array04, array08, 20, 0) << std::endl;
        // Testing array09 and array10
        std::cout << Compare(array09, array10, 20, 0) << std::endl;
        // Testing array07 and array07
        std::cout << Compare(array07, array07, 20, 0) << std::endl;

    // Testing getTotal()
        // Testing array01
        std::cout << getTotal(array01, 20, 0, 0) << std::endl;
        // Testing array03
        std::cout << getTotal(array03, 20, 0, 0) << std::endl;
        // Testing array04
        std::cout << getTotal(array04, 20, 0, 0) << std::endl;
        // Testing array05
        std::cout << getTotal(array05, 20, 0, 0) << std::endl;
        // Testing array06
        std::cout << getTotal(array06, 20, 0, 0) << std::endl;

    // Testing findElement()
        // Testing array01 and element 5
        std::cout << findElement(array01, 20, 5, 0) << std::endl;
        // Testing array09 and element 10
        std::cout << findElement(array09, 20, 10, 0) << std::endl;
        // Testing array01 and element 10
        std::cout << findElement(array01, 20, 10, 0) << std::endl;
        // Testing array02 and element 20
        std::cout << findElement(array09, 20, 20, 0) << std::endl;
        // Testing array05 and element 6
        std::cout << findElement(array05, 20, 6, 0) << std::endl;

    return 0;
}
