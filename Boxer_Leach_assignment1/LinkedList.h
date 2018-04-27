/*
 * LinkedList.h
 * Class for the linked list
 *
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ItemType.h"

class LinkedList 
{
    struct NodeType
    {
        ItemType info;
        NodeType *next;
    };

public:

    /*
     * Post Condition: List is created
     */
    LinkedList();

    /*
     * Pre Condition: List is created
     * Post Condition: all nodes are freed
     */
    ~LinkedList();

    /*
     * Pre Condition: List is initialized
     * Post Condition: return length instance variable
     */
    int lengthIs() const;

    /*
     * Pre Condition: Item and found parameters exist
     * Post Condition: return length instance variable
     */
    ItemType retrieveItem(ItemType &item, bool &found);

    /*
     * Pre Condition: List exists
     * Post Condition found is set to true if the item is found in the list
     * and item is set to the info instance variable of the node that is
     * equivalent to item
     */
    void insertItem(ItemType &item);

    /*
     * Pre Condition: List exists and item initialized
     * Post Condition: the node that contains item is removed from the list
     */
    void deleteItem(ItemType &item);

    /*
     * Pre Condition: List exists
     * Post Condition: current pointer is set to nullptr
     */
    void resetList();

    /*
     * Pre Condition: List Exists
     * Post Condition: item equals the info member of the next node pointed
     * to by the current pointer.  Current now points to the next node
     */
    void getNextItem(ItemType &item);

    /*
     * Pre Condition: List exists
     * Post Condition: List contains no items. Length is equal to 0.
     * All  node pointer memory freed
     */
    void makeEmpty();

    /*
     * Pre Condition: List exists
     * Post Condition: items are printed to standard-out based on the
     * implementation in ItemType
     */
    void print();

private:

    int length;
    NodeType *head;
    NodeType *current;

    /*
     * Pre Condition: List exists and item initialized
     * Post Condition: return the address of the node that contains the item.
     * Otherwise return nullptr.
     */
    NodeType *findNode(ItemType & item);

    /*
     * Pre Condition: List exists and next node does not equal null
     * Post Condition: return the address of the next node that the
     * current node points to
     */
    void getNextNode();
};

#endif
