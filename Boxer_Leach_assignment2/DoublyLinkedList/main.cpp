//
// Created by Sandy Leach on 9/19/17.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main(const int argc, const char * argv[])
{
    DoublyLinkedList list;
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
         << "length (l), print (p), quit (q) "
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
            case 'l':
                cout << "length: " << list.lengthIs() << endl;
                break;
            case 'p':
                list.print();
                cout << '\n';
		break;
            case 'q':
                cout << "Quitting program..." << endl;
		exit(0);
		break;
            default:
                cout << "Command not recognized. Try Again." << endl;
        }

    }
}
