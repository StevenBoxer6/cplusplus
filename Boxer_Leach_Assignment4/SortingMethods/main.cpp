#include <iostream>
#include <cstdlib>
#include "SortingMethods.h"
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char * argv[])
{
    bool DEBUG = true;

    if (argc != 2)
    {
        cout << "Please enter one filename -> ./main file_name.txt"
             << endl;
        return 0;
    }

    char method;

    cout << "Options: " << endl;
    cout << "  i - Insertion Sort" << endl;
    cout << "  m - Merge Sort" << endl;
    cout << "  q - Quick Sort" << endl;
    cout << "  Anything else - Quit" << endl;

    do{

      ifstream in(argv[1]);
      int value;

        vector<int> values, temp, tester;

        while (in >> value)
            values.push_back(value);

        in.close();

        SortingMethods sm;

        cout << "Enter the algorithm for sorting: ";
        cin >> method;

        string s = "";

        if(method == 'i')
        {
            sm.InsertionSort(values, (int) values.size());
            s = "Insertion Sort: ";
        }
        else if(method == 'm')
        {
            sm.MergeSort(values, 0, (int) values.size() - 1);
            s = "Merge Sort: ";
        }
        else if(method == 'q')
        {
            sm.QuickSort(values, 0, (int) values.size() - 1);
            s = "Quick Sort: ";
        }
        else
        {
            cout << "Quitting..." << endl;
            exit(0);
        }

        for (int i = 0; i < values.size(); i++)
            cout << values[i] << endl;

        cout << "Total # of comparisons: " << sm.GetNumSwaps() << endl;

        sm.SetNumSwaps(0);

    } while(method == 'i' || method == 'q' || method == 'm');
} //end of main
