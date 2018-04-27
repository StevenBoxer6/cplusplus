//
// Created by Sandy Leach on 10/12/17.
//

#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "ItemType.h"


struct NodeType
{
    ItemType info;
    NodeType* next;
};

class CircularLinkedList
{
    
public:
    CircularLinkedList();
    
    ~CircularLinkedList();
    
    void FindItem(NodeType* listData, ItemType item, NodeType* &location, NodeType*& predLoc, bool& found);
    
    void insertItem(ItemType &item);
    
    void deleteItem(ItemType &item);
    
    int lengthIs() const;
    
    void print();
    
    void getNextNode();
    
    NodeType* findNode(ItemType& item);
    
private:
    int length;
    NodeType* head;
    NodeType* current;
    
};


#endif
