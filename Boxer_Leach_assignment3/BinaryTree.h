//
// Created by Steven Boxer on 11/5/17.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "ItemType.h"

struct TreeNode
{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
};

class BinaryTree
{

    public:
        BinaryTree();
        ~BinaryTree();
        TreeNode * getRoot();
        void insert(ItemType &key);
        void deleteItem(ItemType &key);
        void retrieve(TreeNode* key,ItemType &item, bool &found) const;
        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        int getLength() const;
        int CountNodes(TreeNode* tree) const ;
        void callPreOrder(TreeNode* key) const ;
        void callPostOrder(TreeNode* key) const ;
        void callInOrder(TreeNode* key) const ;
        void DeleteNode(TreeNode*& tree);
        void Delete(TreeNode*& tree, ItemType item);
        void getPreviousNode(TreeNode* tree, ItemType& data);
        void insertItem(TreeNode*& tree, ItemType item);
        void destroy(TreeNode* tree);

    private:
        int length;
        TreeNode* root;
};


#endif