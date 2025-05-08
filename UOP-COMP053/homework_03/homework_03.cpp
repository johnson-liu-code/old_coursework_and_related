#include<iostream>

using namespace std;


void drawShape(int n)
{
    if(n%2 == 0)
    {
        int down = n/2;
        for(int d = down; d > 0; d--)
        {
            int num_empty = n-d;
            for(int i = 0; i < num_empty; i++)
            {
                cout << " ";
            }
            int num_dots = 2*d;
            for(int n = 0; n < num_dots; n++)
            {
                cout << "*";
            }
            cout << endl;
        }
        for(int d = 1; d < down; d++)
        {
            int num_empty = n-d;
            for(int i = 0; i < num_empty; i++)
            {
                cout << " ";
            }
            int num_dots = 2*d;
            for(int n = 0; n < num_dots; n++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }
    else
    {
        int down = n/2;
        for(int d = 0; d < down; d++)
        {
            int num_empty = n-d;
            for(int i = 1; i < num_empty; i++)
            {
                cout << " ";
            }
            int num_dots = 2*d - 1;
            for(int n = 0; n < num_dots; n++)
            {
                cout << "*";
            }
            cout << endl;
        }
        for(int d = down; d > 0; d--)
        {
            int num_empty = n-d;
            for(int i = 1; i < num_empty; i++)
            {
                cout << " ";
            }
            int num_dots = 2*d - 1;
            for(int n = 0; n < num_dots; n++)
            {
                cout << "*";
            }
            cout << endl;
        }
    }


    return;
}




int main()
{
    drawShape(13);
    drawShape(10);
    drawShape(20);
    drawShape(7);

    return 0;
}
