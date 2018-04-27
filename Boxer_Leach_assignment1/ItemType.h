/*
 * ItemType.h
 * Class File for ItemType
 *
 */

#ifndef ITEMTYPE_H
#define ITEMTYPE_H_H

class ItemType
{
 public:
    enum RelationType
    {
        GREATER,
        LESS,
        EQUAL
    };

  /* 
   * public ItemType()
   * 
   * Post-Condition: ItemType object is created
   * (This is the constructor)
   *
   */
  ItemType();
  
  /*
   * public RelationType compareTo(ItemType &item)
   *
   * Pre-Condition: item parameter is initialized
   * 
   * Post-Condition: returns an enumeration that indicates whether the
   * calling object is GREATER, LESS, or EQUAL to item
   * 
   */
  RelationType compareTo(ItemType &item);

  /* 
   * public void print()
   * 
   * Pre-Condition: ItemType object has been initialized
   * 
   * Post-Condition: value instance variable is printed to standard-out
   * 
   */
  void print();
  
  /* 
   * void initialize(int number)
   * 
   * Pre-Condition: number parameter is initialized
   * 
   * Post-Condition: the value instance variable is set to number
   * 
   */
  void initialize(int number);
  
  /* 
   * int getValue() const;
   * 
   * Pre-Condition: ItemType object has been initialized
   * 
   * Post-Condition: return the value instance variable
   * 
   */
  int getValue() const;
  
 private:
  int value;
};

#endif