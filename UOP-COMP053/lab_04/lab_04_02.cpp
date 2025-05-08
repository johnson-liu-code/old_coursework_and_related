#include<iostream>
#include<string>

using namespace std;


class UnsortedType
{
public:
    UnsortedType()
    {
        length = 0;
        listData = NULL;
    }
    ~UnsortedType()
    {
        int* tempPtr;
        while(listData != NULL)
        {
            tempPtr = listData;
            listData = listData->next;
            delete tempPtr;
        }
    }

private:
    int length;
    int *listData;
    int *next;
};


int main()
{


    return 0;
}
