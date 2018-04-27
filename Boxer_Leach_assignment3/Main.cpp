//
// Created by Sandy Leach on 11/6/17.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "BinaryTree.h"

using namespace std;

bool DEBUG = false;

int main(const int argc, const char * argv[])
{
    BinaryTree tree;
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

            if (DEBUG)
                cout << "ITEM: " << item.getValue() << endl;

            tree.insert(item);
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
         << "retrieve (r), length (l), in-order (n), pre-order (p), post-order (o), quit (q) "
         << endl;

    ItemType tempItem;
    int temp;

    while(userInput != 'q')
    {
        cout << "Enter a command: ";
        cin >> userInput;
        temp = 0;

        switch(userInput)
        {
            case 'i': {
                cout << "Item to insert: ";
                cin >> temp;
                item.initialize(temp);
                tree.insert(item);
                cout << "In-Order: ";
                tree.inOrder();
                cout << endl;
                break;
            }

            case 'd': {
                cout << "Number to delete: ";
                cin >> temp;
                item.initialize(temp);
                tree.deleteItem(item); //make sure checks if in list in method
                cout << "\n";
                cout << "In-Order: ";
                tree.inOrder();
                cout << endl;
                break;
            }

            case 'l': {
                cout << "List Length: " << tree.getLength() << endl;
                break;
            }

            case 'r': {
                bool retrieved = false;
                int local = 0;
                cout << "Item to be retrieved: ";
                cin >> local;

                ItemType insertItem;
                insertItem.initialize(local);

                tree.retrieve(tree.getRoot(), insertItem, retrieved);

                if (retrieved)
                    cout << "Item found in tree" << endl;
                else
                    cout << "Item not found in tree" << endl;
                break;
            }

            case 'n': {
                cout << "In-Order: ";
                tree.inOrder();
                cout << endl;
                break;
            }

            case 'p': {
                cout << "Pre-Order: ";
                tree.preOrder();
                cout << endl;
                break;
            }

            case 'o': {
                cout << "Post-Order: ";
                tree.postOrder();
                cout << endl;
                break;
            }

            case 'q': {
                cout << "Quitting program..." << endl;
                exit(0);
                break;
            }

            default:
                cout << "Command not recognized. Try Again." << endl;
        }

    }
}
