//Sam Jacobs, Johnson Liu, Zach Kingsland
//Comp 53 Sort Project
//10/18/2019
//Selection Sort based on Domestic Gross



#include <iostream>
#include <fstream>
#include <string>
//#include <cstdio> //allows use of C functions like fscanf
//#include <regex>   //allows use of regex expressions
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




int main()
{
	ifstream inputfile;
	inputfile.open("Movies.txt");

	//FILE *inputfile;

	movie moviearr[100];


	//	regex rgx("([0-9]+)\\s+\"(.*)\"\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+\\.[0-9]+)\\s+([0-9]+)"); //regex expression to fin between quotes

	//	smatch matches;	//structure for holding matches

	//	string buffer; //buffer for holding getline while regex checks

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
		inputfile.close();
	}


    std::cout << "####################################################################################" << std::endl;
    std::cout << "Now performing selection sort ..." << std::endl;
    std::cout << "####################################################################################" << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();

//start sort
	int least, leastPos;
	movie temp;
	for (int j = 0; j < 100; j++)
	{
		least = moviearr[j].getdomestic();
		leastPos = j;
		for (int i = 0 + j; i < 100; i++) {
			if (moviearr[i].getdomestic() < least) {
				least = moviearr[i].getdomestic();
				leastPos = i;
			}
		}
		temp = moviearr[leastPos];
		moviearr[leastPos] = moviearr[j];
		moviearr[j] = temp;


	}
//endsort
    auto t2 = std::chrono::high_resolution_clock::now();


	for (int j = 0; j < 100; j++)
	{
		cout << moviearr[j].gettitle() << "			\nRank: " << moviearr[j].getrank() << "			Worldwide Gross (In Millions): $" << moviearr[j].getworldwide();
		cout << "			\nDomestic Gross (In Millions): $" << moviearr[j].getdomestic() << "			Overseas Gross (In Millions): $" << moviearr[j].getoverseas();
		cout << "			\nYear Released: " << moviearr[j].getyear() << "\n \n";

	}

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "####################################################################################" << std::endl;
    std::cout << "It took selection sort " << duration << " microseconds to complete." << std::endl;
    std::cout << "Selection sort has a time complexity of O(n^2)." << std::endl;
    std::cout << "####################################################################################" << std::endl;







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
