#include<iostream>
#include<fstream>
#include<string>
#include <chrono>


class Movie
{
public:
    Movie()
    {
        rank = 0;
        movieName = "";
        field1 = 0;
        field2 = 0;
        field3 = 0;
        year = 0;
    }
    Movie(int rank, std::string movieName, float field1, float field2, float field3, int year)
    {
        this->rank = rank;
        this->movieName = movieName;
        this->field1 = field1;
        this->field2 = field2;
        this->field3 = field3;
        this->year = year;
    }

    int rank;
    std::string movieName;
    float field1;
    float field2;
    float field3;
    int year;
};


// ###########################################################################################
// Code for Merge Sort
Movie* merge(Movie arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // Create temporary arrays
    Movie L[n1], R[n2];

    // Copy data into the temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    // Merge the temporary arrays back into arr
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        // Descending sort
        if (L[i].field2 >= R[j].field2)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L, if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R, if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    return arr;
}

Movie* mergeSort(Movie arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        // Sort first and second halves
        arr = mergeSort(arr, l, m);
        arr = mergeSort(arr, m+1, r);

        arr = merge(arr, l, m, r);
    }
    return arr;
}
// ###########################################################################################

// ###########################################################################################
// Code for Quick Sort

// Swap two items
Movie* swap(Movie arr[], int i, int j)
{
    Movie t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;

    return arr;
}
int partition (Movie arr[], int low, int high)
{
    int pivot = arr[high].field2; // Pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If the current element is smaller than the pivot
        if (arr[j].field2 > pivot)
        {
            i++; // Increment index of smaller element
            swap(arr, i,j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

void quickSort(Movie arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}
// ###########################################################################################

// ###########################################################################################
// Print the array
void printArray(Movie A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        std::cout << A[i].rank << " " << A[i].movieName << " " << A[i].field1 << " " << A[i].field2 << " " << A[i].field3 << " " << A[i].year << std::endl;
    printf("\n");
}
// ###########################################################################################

int main()
{
    std::ifstream inFile;
    std::string inFileName = "Movies.txt";
    inFile.open(inFileName);

    Movie movieArr1[100];
    Movie movieArr2[100];

    int rank;
    std::string movieName;
    float field1;
    float field2;
    float field3;
    int year;

    for(int i = 0; i < 100; i++)
    {
        inFile >> rank;
        inFile >> movieName;
        inFile >> field1;
        inFile >> field2;
        inFile >> field3;
        inFile >> year;

        movieArr1[i] = Movie(rank, movieName, field1, field2, field3, year);
        movieArr2[i] = Movie(rank, movieName, field1, field2, field3, year);
    }
    std::cout << "####################################################################################" << std::endl;
    std::cout << "Merge sort in descending order using the second money column." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    mergeSort(movieArr1, 0, 99);
    auto t2 = std::chrono::high_resolution_clock::now();
    printArray(movieArr1, 100);
    auto duration_merge = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << std::endl << std::endl;

    std::cout << "####################################################################################" << std::endl;
    std::cout << "Quick sort in descending order using the second money column." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    quickSort(movieArr2, 0, 99);
    t2 = std::chrono::high_resolution_clock::now();
    printArray(movieArr2, 100);
    auto duration_quick = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took merge sort " << duration_merge << " microseconds to complete." << std::endl;
    std::cout << "Merge sort has a time complexity of O(nlogn)." << std::endl;
    std::cout << "####################################################################################" << std::endl;


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took quick sort " << duration_quick << " microseconds to complete." << std::endl;
    std::cout << "Quick sort has a time complexity of O(nlogn)." << std::endl;
    std::cout << "####################################################################################" << std::endl;



    return 0;
}
