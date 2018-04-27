//
// Created by Sandy Leach and Steven Boxer on 9/21/17.
//

#include "LinkedList.h"
#include "cstdlib"
#include "iostream"

using namespace std;

LinkedList::LinkedList()
{
    this->length = 0;
    this->head = nullptr;
    this->current = nullptr;
}

LinkedList::~LinkedList()
{
    NodeType *tempPtr;
    this->current = this->head;
    while (this->current != nullptr)
    {
        tempPtr = this->current;
        this->current = this->current->next;
        delete tempPtr;
    }
}

int LinkedList::lengthIs() const
{
    return this->length;
}

ItemType LinkedList::retrieveItem(ItemType &item, bool &found)
{
    found = false;
    NodeType *location;
    location = head;
    
    bool notFound = (location != nullptr);
    while(notFound && !found)
    {
        switch(item.compareTo(location->info))
        {
            case ItemType::GREATER:
                location = location->next;
                notFound = (location != nullptr);
                break;
                
            case ItemType::EQUAL:
                found = true;
                item = location->info;
                break;
            
            case ItemType::LESS:
                notFound = false;
                break;
                
        }
    }

    return item;
}


void LinkedList::insertItem(ItemType &item)
{
    NodeType * location;
    
    NodeType * node;
    node = new NodeType;
    node->info = item;
    node->next = nullptr;

    bool notFound = true; 

    location = head;    
    if(length == 0)
      {
	notFound = false;
	head = node;
	location = head;
      }
    if(item.compareTo(location->info) == ItemType::LESS && length != 0)
      {
	notFound = false;
	node->next = head;
        head = node;
      }
    else if(length != 0)
      {
      
      while(notFound)
	{   
	  if(location->next != nullptr)
	    {
	      switch(item.compareTo(location->next->info))
		{
		case ItemType::GREATER:
		  location  = location->next;
		  break;
		  
		case ItemType::EQUAL:
		  notFound = false;
		  cout << "Item already in list!" <<endl;
		  length --;
		  break;
		  
		case ItemType::LESS:
		  notFound = false;
		  node->next = location->next;
		  location->next = node;
		  break;
		}
	    }
	  else
	    {
	      notFound = false;
	      location->next = node;
	    }
	}
      }

    length ++;
}

void LinkedList::deleteItem(ItemType &item)
{
    NodeType * location = head;
    NodeType * prevLocation = nullptr;
    bool inList = true;

    if(this->findNode(item) == nullptr)
      {
	cout << "Item not in list." <<endl;
	inList = false;
	
      }

    if (item.compareTo(head->info) == ItemType::EQUAL && inList) // If the node to delete is head
    {
        prevLocation = location;
        head = head->next;
	this->length --;
    }
    else
    {
      while((item.compareTo(location->next->info) != ItemType::EQUAL) && inList)
        {
	  if(location->next != nullptr)
	    {
	      prevLocation = location;
	      location = location->next;
	    }
	  else
	    {
	      if(item.compareTo(location->info) == ItemType::EQUAL) //last item is item to delete
		{
		  prevLocation->next = nullptr;
		  delete location;
		  inList = false;
		  this->length --;
		}
	      else
		{ 
		  inList = false;
		  cout << "Item is not in list";
		}
	    }
	}
	if(inList)
	  {
	    prevLocation = location->next;
	    location->next = location->next->next;
	  }
	  
	
	if(inList)
	  {
	    delete prevLocation;
	    this->length--;
	  }
    }
}

void LinkedList::resetList()
{
    current = nullptr;
}

void LinkedList::getNextItem(ItemType &item)
{
  getNextNode();
  item = current->info;
}

void LinkedList::makeEmpty()
{
    NodeType * tempPtr;

    while (head != nullptr)
    {
        tempPtr = head;
        head = head->next;
        delete tempPtr;
    }

    this->length = 0;
}

void LinkedList::print()
{
  resetList();
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
}

void LinkedList::getNextNode()
{
  if(current == nullptr)
    current=head;
  else
    current = current->next;
}


LinkedList::NodeType* LinkedList::findNode(ItemType & item)
{
  NodeType * location = head;
  bool found = false;
  while(location != nullptr)
    {
      if(item.compareTo(location->info) == ItemType::EQUAL)
	{
	  found = true;
	  return location;
	}
      location = location->next;
    }
  if(!found)
    return nullptr;
}

