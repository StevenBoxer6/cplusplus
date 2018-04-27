//
// Created by Sandy Leach and Steven Boxer on 10/12/17.
//

#include "DoublyLinkedList.h"
#include "cstdlib"
#include "iostream"

using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
    this->length = 0;
    this->head = nullptr;
    this->current = nullptr;
}

DoublyLinkedList::~DoublyLinkedList()
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

int DoublyLinkedList::lengthIs() const
{
    return this->length;
}

void DoublyLinkedList::retrieveItem(ItemType &item, bool &found)
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
}

void DoublyLinkedList::insertItem(ItemType &item)
{
  /*
    cout << "Entered Insert Item with " << item.getValue() << endl;
    // Check if already in the list

    if (this->findNode(item) != nullptr)
      cout << "Item is already in list!" << endl;
    else
    {
        NodeType * location;
	// Create Node to Insert
        NodeType * node = new NodeType();
        node->info = item;

	if(this->length != 0)
	  location = head;

        // Empty List
        if (this->length == 0)
        {
            this->head = node;
            this->length++;
            cout << "REACHED HERE 0.  Length is "
                 << this->length
                 << endl;
        } 
	else //not empty
	  {
            cout << "REACHED HERE 1" << endl;
            // Item goes at beginning
            if (item.compareTo(head->info) == ItemType::LESS)
            {
                node->next = head;
                head->prev = node;
                head = node;
                this->length++;
            }
            // Item goes after beginning
            else
            {
                // Set location to after node to insert  
	      while (item.compareTo(location->info) == ItemType::GREATER)
		{
		  location = location ->next;
		}

                // Insert when location is at the end
                if (location->next == nullptr)
                {
		  cout <<"10 should reach this!";
                    location->next = node;
                    node->prev = location;
                    this->length++;
                }
                // Insert when location is not in end
                else
                {
                    location->prev->next = node;
                    node->prev = location->prev;
                    node->next = location;
                    location->prev = node;
                    this-> length++;
                }
            }
	  }
	delete node;
    }
  */

  if (findNode(item) != nullptr)
    cout << "Item is alreay in list!" << endl;
  else
    {
      NodeType* location;

      // Create Node to Insert
      NodeType* node = new NodeType();
      node->info = item;

      if(this->length != 0)
	location = head;

      if (length == 0)
        {
	  head = node;
	  length++;
        }
      else
        {
	  // Item is less than head
	  if (item.compareTo(head->info) == ItemType::LESS)
            {
	      node->next = head;
	      head->prev = node;
	      head = node;
	      length++;
            }
	  else
            {
	      bool last = false;
	      while (item.compareTo(location->info) == ItemType::GREATER)
                {
		  // At the last node
		  if (location->next == nullptr)
                    {
		      node->prev = location;
		      location->next = node;
		      length++;
		      last = true;
		      return;
                    }
		  else
		    location = location->next;
                }

	      // Insert before location
	      if(last == false)
		{
		  node->prev = location->prev;
		  location->prev->next = node;
		  node->next = location;
		  location->prev = node;
		  length++;
		}
            }
        }
    }


 
}

void DoublyLinkedList::deleteItem(ItemType &item)
{
    NodeType* location = head;
    NodeType* prevLocation = nullptr;
    bool inList = true;

    if(this->findNode(item) == nullptr)
    {
        cout << "Item not in list." <<endl;
        inList = false;

    }

    if (item.compareTo(head->info) == ItemType::EQUAL && inList) // If the node to delete is head
    {
        prevLocation = location;
        if(length != 1)
        {
            location = location-> next;
            location->prev = nullptr;
            head = location;
        }
        delete prevLocation;
    }
    else if(inList)
    {
        while(item.compareTo(location->info) != ItemType::EQUAL)
        {
            prevLocation = location;
            location = location-> next;
        }

        //now location is item we want to delete

        if(location->next == nullptr) //last item in list
        {
            prevLocation->next = nullptr;
            location-> prev = nullptr;
            delete location;
        }
        else //item somewhere in middle of list
        {
            prevLocation->next = location->next;
            location->next->prev = prevLocation;
        }

    }

    if(inList)
        this->length--;

}

void DoublyLinkedList::resetList()
{
    current = nullptr;
}

void DoublyLinkedList::print()
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

void DoublyLinkedList::getNextNode()
{
    if(current == nullptr)
        current=head;
    else
        current = current->next;
}

NodeType* DoublyLinkedList::findNode(ItemType & item)
{
  if(this->length != 0)
    {
    NodeType* location = this->head;

    // All but last item
    while (location->next != nullptr)
    {
        if (item.compareTo(location->info) == ItemType::EQUAL)
            return location;
        location = location->next;
    }

    // Last Item
    if (item.compareTo(location->info) == ItemType::EQUAL)
        return location;

    return nullptr;
    }
  else
    return nullptr;
}
