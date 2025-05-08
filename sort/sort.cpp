//Sam Jacobs, Johnson Liu, Zach Kingsland
//Comp 53 Sort Project
//10/18/2019



#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> //allows use of C functions like fscanf
#include <regex>   //allows use of regex expressions
#include <chrono>

using namespace std;

class movie {
public:
	void setrank(int rank)
	{
		this->rank = rank;
	}

	int getrank()
	{
		return rank;
	}

	void settitle(string title)
	{
		this->title = title;
	}

	string gettitle()
	{
		return this->title;
	}

	void setworldwide(double worldwide)
	{
		this->worldwide = worldwide;
	}

	double getworldwide()
	{
		return this->worldwide;
	}

	void setdomestic(double domestic)
	{
		this->domestic = domestic;
	}

	double getdomestic()
	{
		return this->domestic;
	}

	void setoverseas(double overseas)
	{
		this->overseas = overseas;
	}

	double getoverseas()
	{
		return this->overseas;
	}

	void setyear(int year)
	{
		this->year = year;
	}

	int getyear()
	{
		return year;
	}


private:

	int rank;
	string title;
	double worldwide;
	double domestic;
	double overseas;
	int year;


};

// ###########################################################################################
// Code for Merge Sort
movie* merge(movie arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // Create temporary arrays
    movie L[n1], R[n2];

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
        if (L[i].getdomestic() >= R[j].getdomestic())
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

movie* mergeSort(movie arr[], int l, int r)
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
movie* swap(movie arr[], int i, int j)
{
    movie t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;

    return arr;
}
int partition (movie arr[], int low, int high)
{
    int pivot = arr[high].getdomestic(); // Pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If the current element is smaller than the pivot
        if (arr[j].getdomestic() > pivot)
        {
            i++; // Increment index of smaller element
            swap(arr, i,j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

void quickSort(movie arr[], int low, int high)
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
void printArray(movie A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        std::cout << A[i].getrank() << " " << A[i].gettitle() << " " << A[i].getworldwide() << " " << A[i].getdomestic() << " " << A[i].getoverseas() << " " << A[i].getyear() << std::endl;
    printf("\n");
}
// ###########################################################################################

// ###########################################################################################
// Code for Bubble Sort

void bubbleSort(movie arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
      swapped = false;
      for (j = 0; j < n-i-1; j++)
      {
         if (arr[j].getdomestic() > arr[j+1].getdomestic())
         {
            swap(arr[j], arr[j+1]);
            swapped = true;
         }
      }
      if (swapped == false)
         break;
    }
}



int main()
{
	ifstream inputfile;
	inputfile.open("Movies.txt");

	//FILE *inputfile;

	movie moviearr[100];


	/*regex rgx("([0-9]+)\\s+\"(.*)\"\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+)"); //regex expression to fin between quotes

	smatch matches;	//structure for holding matches

	string buffer; //buffer for holding getline while regex checks*/

	int count = 0;
	int rank, year;
	string title;
	double worldwide, domestic, overseas;

	while (inputfile.is_open())
	{


		while (inputfile >> rank >> title >> worldwide >> domestic >> overseas >> year)
		{

			moviearr[count].setrank(rank);
			moviearr[count].settitle(title);
			moviearr[count].setworldwide(worldwide);
			moviearr[count].setdomestic(domestic);
			moviearr[count].setoverseas(overseas);
			moviearr[count].setyear(year);

			count++;
		}

		/*getline(inputfile, buffer);		//get the line from inputfile, put it into the buffer

		if ((regex_search(buffer, matches, rgx)))       //use regex to search if theres a match, abandoned due to the rejection at line 44
		{



			moviearr[count].rank = stoi(matches.str(0));
			moviearr[count].title = matches.str(1);
			cout << matches.str(2) << "\n";
			moviearr[count].worldwide = stod(matches.str(2));
			moviearr[count].domestic = stod(matches.str(3));
			moviearr[count].overseas = stod(matches.str(4));
			moviearr[count].year = stoi(matches.str(5));


			count++;
		}*/


		inputfile.close();


	}

    movie movie_insertion[100] = moviearr;
    movie movie_selection[100] = moviearr;
    movie movie_merge[100] = moviearr;
    movie movie_quick[100] = moviearr;
    movie movie_bubble[100] = moviearr;

	// for (int j = 0; j < 100; j++)
	// {
	// 	cout << moviearr[j].gettitle() << "			\nRank: " << moviearr[j].getrank() << "			Worldwide Gross (In Millions): $" << moviearr[j].getworldwide();
	// 	cout << "			\nDomestic Gross (In Millions): $" << moviearr[j].getdomestic() << "			Overseas Gross (In Millions): $" << moviearr[j].getoverseas();
	// 	cout << "			\nYear Released: " << moviearr[j].getyear() << "\n \n";
    //
	// }

    std::cout << "####################################################################################" << std::endl;
    std::cout << "Now performing insertion sort ..." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();

	//start insertion sort
	int i, j;
	movie key;
	for (i = 1; i < 100; i++)
	{
		key = movie_insertion[i];
		j = i - 1;


		while (j >= 0 && movie_insertion[j].getdomestic() > key.getdomestic())
		{
			movie_insertion[j + 1] = movie_insertion[j];
			j = j - 1;
		}
		movie_insertion[j + 1] = key;
	}
		cout << "This is the list sorted by insertion sort, by domestic gross \n \n \n \n \n";

	for (int j = 0; j < 100; j++)
	{
		cout << movie_insertion[j].gettitle() << "			\nRank: " << movie_insertion[j].getrank() << "			Worldwide Gross (In Millions): $" << movie_insertion[j].getworldwide();
		cout << "			\nDomestic Gross (In Millions): $" << movie_insertion[j].getdomestic() << "			Overseas Gross (In Millions): $" << movie_insertion[j].getoverseas();
		cout << "			\nYear Released: " << movie_insertion[j].getyear() << "\n \n";

	}

	//end insertion sort

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_insertion = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


    std::cout << "####################################################################################" << std::endl;
    std::cout << "Now performing selection sort ..." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();

//start sort
	int least, leastPos;
	movie temp;
	for (int j = 0; j < 100; j++)
	{
		least = movie_selection[j].getdomestic();
		leastPos = j;
		for (int i = 0 + j; i < 100; i++) {
			if (movie_selection[i].getdomestic() < least) {
				least = movie_selection[i].getdomestic();
				leastPos = i;
			}
		}
		temp = movie_selection[leastPos];
		movie_selection[leastPos] = movie_selection[j];
		movie_selection[j] = temp;


	}
//endsort
    t2 = std::chrono::high_resolution_clock::now();


	for (int j = 0; j < 100; j++)
	{
		cout << movie_selection[j].gettitle() << "			\nRank: " << movie_selection[j].getrank() << "			Worldwide Gross (In Millions): $" << movie_selection[j].getworldwide();
		cout << "			\nDomestic Gross (In Millions): $" << movie_selection[j].getdomestic() << "			Overseas Gross (In Millions): $" << movie_selection[j].getoverseas();
		cout << "			\nYear Released: " << movie_selection[j].getyear() << "\n \n";

	}

    auto duration_selection = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


    std::cout << "####################################################################################" << std::endl;
    std::cout << "Merge sort in descending order using the second money column." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    mergeSort(movie_merge, 0, 99);
    t2 = std::chrono::high_resolution_clock::now();
    printArray(movie_merge, 100);
    auto duration_merge = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << std::endl << std::endl;

    std::cout << "####################################################################################" << std::endl;
    std::cout << "Quick sort in descending order using the second money column." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    quickSort(movie_merge, 0, 99);
    t2 = std::chrono::high_resolution_clock::now();
    printArray(movie_merge, 100);
    auto duration_quick = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "####################################################################################" << std::endl;
    std::cout << "Now performing selection sort ..." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    bubbleSort(movie_bubble, 100);
    t2 = std::chrono::high_resolution_clock::now();
    printArray(movie_bubble, 100);
    auto duration_bubble = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took insertion sort " << duration_insertion << " microseconds to complete." << std::endl;
    std::cout << "Insertion sort has a time complexity of O(n^2)." << std::endl;
    std::cout << "####################################################################################" << std::endl;


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took selection sort " << duration_selection << " microseconds to complete." << std::endl;
    std::cout << "Selection sort has a time complexity of O(n^2)." << std::endl;
    std::cout << "####################################################################################" << std::endl;


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took merge sort " << duration_merge << " microseconds to complete." << std::endl;
    std::cout << "Merge sort has a time complexity of O(nlogn)." << std::endl;
    std::cout << "####################################################################################" << std::endl;


    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took quick sort " << duration_quick << " microseconds to complete." << std::endl;
    std::cout << "Quick sort has a time complexity of O(nlogn)." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took bubble sort " << duration_quick << " microseconds to complete." << std::endl;
    std::cout << "Bubble sort has a time complexity of O(n^2)." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    std::cout << "The quickest sorting method for this particular data set is selection Sort." << std::endl << std::endl;




	/*inputfile = fopen("Movies.txt", "r+");    //open file, give read permission

	int count = 0;
	while (inputfile && count < 100)
	{

		fscanf_s(inputfile, "%d %s %f %f %f %d", &arr[count].rank, &arr[count].title, &arr[count].worldwide, &arr[count].domestic, &arr[count].overseas, &arr[count].year);
		count++;
	}


	for (int i = 0; i < 100; i++)
	{
		cout << arr[i].title << "\n";
	}*/


	// system("pause");
	return 0;

}
