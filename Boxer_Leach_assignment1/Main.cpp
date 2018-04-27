//
// Created by Sandy Leach on 9/19/17.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main(const int argc, const char * argv[])
{
    LinkedList list;
    ItemType item;
    int input;
    std::fstream fs;

    fs.open(argv[1], fstream::in);
    if (fs.is_open())
    {
        fs >> input;
        while (!fs.eof())
        {
            item.initialize(input);
            list.insertItem(item);
            fs >> input;
        }
    }
    else
    {
        cout << "File could not be opened."
             << " Try again"
             << endl;
        return 0;
    }

    char userInput = 'a';


    cout << "Commands - insert (i), delete (d), "
         << "make empty (e), length (l), print (p),  "
         << "next item (g), reset list (r), quit (q) "
         << endl;

    ItemType tempItem;
    int temp;
    while(userInput != 'q')
    {
        cout << "Enter a command: ";
        cin >> userInput;
	// cout << "\n";
        temp = 0;
        
        switch(userInput)
        {
            case 'i':
                cout << "Number to insert: ";
                cin >> temp;
                item.initialize(temp);
		list.insertItem(item);
                break;
            case 'd':
                cout << "Number to delete: ";
                cin >> temp;
                item.initialize(temp);
		list.deleteItem(item); //make sure checks if in list in method
                break;
            case 'e':
                cout << "Making empty." << endl;
                list.makeEmpty();
                break;
            case 'l':
                cout << "length: " << list.lengthIs() << endl;
                break;
            case 'p':
                list.print();
                break;
            case 'g':
                cout << "Next item: ";
		list.getNextItem(tempItem);
		tempItem.print();
		cout << "\n";
                break;
            case 'r':
                cout << "List reset." << endl;
                list.resetList();
                break;
            case 'q':
                cout << "Quitting program..." << endl;
                break;
            default:
                cout << "Command not recognized. Try Again." << endl;
        }

    }
}
