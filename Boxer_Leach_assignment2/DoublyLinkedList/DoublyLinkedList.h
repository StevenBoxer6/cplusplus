//
// Created by Sandy Leach on 10/12/17.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "ItemType.h"

struct NodeType
{
    ItemType info;
    NodeType* next;
    NodeType* prev;
};

class DoublyLinkedList
{
    
public:
    
    DoublyLinkedList(); //constructor
    ~DoublyLinkedList(); //dectructor
    
    int lengthIs() const;
    void retrieveItem(ItemType &item, bool &found);
    void insertItem(ItemType &item);
    void deleteItem(ItemType &item);
    void resetList();
    void print();
    
private:
    
    int length;
    NodeType* head;
    NodeType* current;
    NodeType* findNode(ItemType &item);
    void getNextNode();
    
};


#endif
