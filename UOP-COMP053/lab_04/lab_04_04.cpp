#include<fstream>
#include<string>

using namespace std;


class College
{
public:
    College()
    {
        this->college_ID = 0;
        this->college_name = "";
    }
    College(int college_ID, string college_name)
    {
        this->college_ID = college_ID;
        this->college_name = college_name;
    }
private:
    int college_ID;
    string college_name;
};

College

class UnsortedList
{
public:
	UnsortedList()
    {
        length = 0;
        listData = NULL;
    };
	void MakeEmpty()
    {

    };
	bool IsFull() const;
	int GetLength() const;
	College GetItem(int ID, bool&);
	void PutItem(int ID, int Age, string Name);
	void DeleteItem(int ID);
	void ResetList();
	College GetNextItem();

private:
	int length;
	int currentPos;
};


int main()
{




    return 0;
}
