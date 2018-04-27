#ifndef SORTINGMETHODS_SORTINGMETHODS_H
#define SORTINGMETHODS_SORTINGMETHODS_H

#include <vector>

using namespace std;

class SortingMethods
{
public:
    SortingMethods();
    void Swap(int & one, int & two);
    void InsertionSort(vector<int> & values, int length);
    void MergeItem(vector<int> & values, int left, int mid, int right);
    void MergeSort(vector<int> & values, int left, int right);
    void QuickSort(vector<int> & values, int first, int last);
    int Split(vector<int> & values, int first, int last);
    int GetNumSwaps();
    void SetNumSwaps(int num);

private:
    int numSwaps;
};


#endif //SORTINGMETHODS_SORTINGMETHODS_H
