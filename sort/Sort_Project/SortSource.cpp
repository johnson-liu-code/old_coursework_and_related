//Sam Jacobs, Johnson Liu, Zach Kingsland
//Comp 53 Sort Project
//10/18/2019



#include <iostream>
#include <fstream>
#include <string>
//#include <cstdio> //allows use of C functions like fscanf
//#include <regex>   //allows use of regex expressions

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

		//getline(inputfile, buffer);		\\get the line from inputfile, put it into the buffer

		/*if ((regex_search(buffer, matches, rgx)))       //use regex to search if theres a match, abandoned due to the rejection at line 44
		{



			arr[count].rank = stoi(matches.str(0));
			arr[count].title = matches.str(1);
			cout << matches.str(2) << "\n";
			arr[count].worldwide = stod(matches.str(2));
			arr[count].domestic = stod(matches.str(3));
			arr[count].overseas = stod(matches.str(4));
			arr[count].year = stoi(matches.str(5));


			count++;
		}*/


		inputfile.close();


	}




	for (int j = 0; j < 100; j++)
	{
		cout << moviearr[j].gettitle() << "			\nRank: " << moviearr[j].getrank() << "			Worldwide Gross (In Millions): $" << moviearr[j].getworldwide();
		cout << "			\nDomestic Gross (In Millions): $" << moviearr[j].getdomestic() << "			Overseas Gross (In Millions): $" << moviearr[j].getoverseas();
		cout << "			\nYear Released: $" << moviearr[j].getyear() << "\n \n";

	}



	






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


	system("pause");
	return 0;

}