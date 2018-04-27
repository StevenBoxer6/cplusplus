#include <iostream>
#include <cstdlib>
#include "SortingMethods.h"
#include <fstream>
#include <vector>

using namespace std;

SortingMethods::SortingMethods()
{
    this->numSwaps = 0;
}

int SortingMethods::GetNumSwaps()
{
    return this->numSwaps;
}

void SortingMethods::SetNumSwaps(int num){
    this->numSwaps = num;
}

void SortingMethods::Swap(int & one, int & two)
{
    int temp = one;
    one = two;
    two = temp;
}

void SortingMethods::InsertionSort(vector<int> & values, int length)
{
    int i, cur, j;
    for (i = 1; i < length; i++)
    {
        cur = values[i];
        j = i - 1;

        while (j >= 0 && values[j] > cur)
        {
            values[j + 1] = values[j];
            j = j - 1;
            this->numSwaps++; 
        }
        values[j + 1] = cur;
	this->numSwaps++; //steven
    }
}

void SortingMethods::MergeItem(vector<int> & values, int left, int mid, int right)
{
    int x, y, z;
    int length1 = mid - left + 1;
    int length2 = right - mid;

    vector<int> leftArr(length1);
    vector<int> rightArr(length2);

    for (x = 0; x < length1; x++)
        leftArr[x] = values[left + x];
    for (y = 0; y < length2; y++)
        rightArr[y] = values[mid + 1 + y];

    x = 0;
    y = 0;
    z = left;

    while (x < length1 && y < length2)
      {
        if (leftArr[x] <= rightArr[y])
        {
            values[z] = leftArr[x];
            x++;
            this->numSwaps++;
        }
        else
        {
            values[z] = rightArr[y];
            y++;
            this->numSwaps++;
        }
        z++;
    }

    while (x < length1)
    {
        values[z] = leftArr[x];
        x++;
        z++;
    }

    while (y < length2)
    {
        values[z] = rightArr[y];
        y++;
        z++;
    }
}

void SortingMethods::MergeSort(vector<int> & values, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        MergeSort(values, left, mid);
        MergeSort(values, mid + 1, right);
        MergeItem(values, left, mid, right);
	//this->numSwaps++; //Steven
    }
}

int SortingMethods::Split(vector<int> & values, int first, int last)
{
    int pivot = values[last];
    int i = (first - 1);

    for (int j = first; j <= last-1; j++)
    {
        if (values[j] <= pivot)
        {
	        i++;
	        Swap(values[i], values[j]);
        }
        this->numSwaps++;
    }
    Swap(values[i + 1], values[last]);
    return (i + 1);
}

void SortingMethods::QuickSort(vector<int> & values, int first, int last)
{
    if(first < last)
    {
        int splitPoint = Split(values, first, last);
	    QuickSort(values, first, splitPoint - 1);
        QuickSort(values, splitPoint + 1, last);
    }
}
