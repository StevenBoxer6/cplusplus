//
// Created by Sandy Leach on 10/12/17.
//

#include "CircularLinkedList.h"
#include "ItemType.h"
#include "cstdlib"
#include "iostream"

using namespace std;

CircularLinkedList::CircularLinkedList()
{
    this->length = 0;
    this->head = nullptr;
    this->current = nullptr;
}

CircularLinkedList::~CircularLinkedList()
{
    NodeType* tempPtr;
    this->current = this->head;
    while (this->current != nullptr)
    {
        tempPtr = this->current;
        this->current = this->current->next;
        delete tempPtr;
    }
}

int CircularLinkedList::lengthIs() const
{
    return this->length;
}

void CircularLinkedList::getNextNode()
{
    if(current == nullptr)
        current=head->next;
    else
        current = current->next;
}

void CircularLinkedList::print()
{
  NodeType* node = head->next;
  do{
    node->info.print();
    node = node->next;
  }while(node != head->next);

  /*
    getNextNode();
    if (head == nullptr)
        cout << "EMPTY LIST" << endl;
    else
    {
        while (current != nullptr)
        {
            current->info.print();
            getNextNode();
        }
        cout << endl;
    }
  */
}

void CircularLinkedList::insertItem(ItemType &item)
{
    NodeType* location;
    NodeType* node = new NodeType();
    node->info = item;
    node->next = nullptr;
    
    bool notFound = true;
    
    if(this->length != 0)
      location = head;
    
    if(this->length == 0) //insert first element
    {
        notFound = false;
        head = node;
        node->next = head;
	this->length ++;
        
    }
    else if(this->findNode(item) == nullptr)
    {
      if(item.compareTo(head->info) == ItemType::GREATER) //goes in back, new head
        {
            node->next = head->next;
            head->next = node;
            head = node;
        }
        else if(item.compareTo(head->next->info) == ItemType::LESS) //if first element
        {
            node->next = head->next;
            head->next = node;
        }
        else
        {
            while(notFound)
            {
            switch (item.compareTo(location->next->info))
                {
                    // New Node needs to be inserted after the current node
                    case ItemType::LESS:
                        node->next = location->next;
                        location->next = node;
                        notFound = false;
                        break;
                    // New Node needs to be inserted after the next node
                    case ItemType::EQUAL:
                        cout << "Error, Item is in list" << endl;
                        break;
                    case ItemType::GREATER:
                        location = location->next;
                        break;
                }
            }
        }
	this->length++;   
    }
    else //in list already
    {
        cout << "Item already in list!" << endl;
    }
}

void CircularLinkedList::deleteItem(ItemType& item)
{
    NodeType* location = head->next;
    NodeType* prevLocation = head;
    bool inList = true;
    
    if(this->findNode(item) == nullptr)
    {
        cout <<"Item is not in list." << endl;
        inList = false;
    }
    
    //if head, the back, is to be deleted
    if(item.compareTo(head->info) == ItemType::EQUAL && inList)
    {
        while(location->next != prevLocation)
        {
            location = location->next;
        }
        location->next = prevLocation ->next;
        head = location;
        delete prevLocation;
    }
    else if(item.compareTo(location->info) == ItemType::EQUAL && inList) //if first item is one to be deleted
    {
        prevLocation->next = location->next;
        delete location;
    }
    else if(inList)
    {
        while(item.compareTo(prevLocation->next->info) != ItemType::EQUAL)
        {
            prevLocation = location;
            location = location->next;
        }
        prevLocation->next = location->next;
        delete location;
    }
    
    if(inList)
        this->length --;
    
}

NodeType* CircularLinkedList::findNode(ItemType & item)
{
    NodeType* location = head;

    do {
        if (location->info.compareTo(item) == ItemType::EQUAL)
            return location;
        else
            location = location->next;
    } while (location != head);

    return nullptr;
}




