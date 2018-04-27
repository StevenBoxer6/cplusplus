//
// Created by Steven Boxer on 11/5/17.
//

#include "BinaryTree.h"
#include "ItemType.h"
#include "cstdlib"
#include "iostream"

using namespace std;

BinaryTree::BinaryTree()
{
    this->length = 0;
    this->root = nullptr;
}

TreeNode * BinaryTree::getRoot()
{
    return this->root;
}

BinaryTree::~BinaryTree()
{
    if(this->root != nullptr)
        destroy(this->root);
}

void BinaryTree::destroy(TreeNode* tree)
{
    if(tree == nullptr)
        return;
    callPostOrder(tree->left);
    callPostOrder(tree->right);
    delete tree;
}

void BinaryTree::insert(ItemType &key)
{
    bool found = true;
    retrieve(this->root, key, found);

    if(found)
    {
        cout << "Item is already in list.";
        return;
    }

    if(this->root == nullptr)
    {
        TreeNode* tree = new TreeNode();
        tree->right = nullptr;
        tree->left = nullptr;
        tree->info = key;
        this->root = tree;
    }
    else
        insertItem(this->root, key);
}

void BinaryTree::insertItem(TreeNode*& tree, ItemType item)
{
    if(tree == nullptr)
    {
        tree = new TreeNode();
        tree->right = nullptr;
        tree->left = nullptr;
        tree->info = item;
    }
    else if(item.compareTo(tree->info) == ItemType::LESS)
        insertItem(tree->left, item);
    else
        insertItem(tree->right, item);
}

void BinaryTree::deleteItem(ItemType &key)
{
    Delete(this->root, key);
}

void BinaryTree::Delete(TreeNode*& tree, ItemType item)
{
    bool found = true;
    retrieve(this->root,item,found);

    if(!found)
    {
        cout << "Item not in tree.";
        return;
    }

    if (item.compareTo(tree->info) == ItemType::LESS)
        Delete(tree->left, item);
    else if (item.compareTo(tree->info) == ItemType::GREATER)
        Delete(tree->right, item);
    else
        DeleteNode(tree);
}

void BinaryTree::DeleteNode(TreeNode*& tree)
{
    ItemType info;
    TreeNode* tempPtr;
    tempPtr = tree;

    if (tree->left == nullptr)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == nullptr)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        getPreviousNode(tree->left, info);
        tree->info = info;
        Delete(tree->left, info);
    }

}

void BinaryTree::getPreviousNode(TreeNode *tree, ItemType &data)
{
    while(tree->right != nullptr)
        tree = tree->right;
    data = tree->info;
}

void BinaryTree::retrieve(TreeNode* key,ItemType &item, bool &found) const
{
    if(key == nullptr)
        found = false;
    else if(item.compareTo(key->info) == ItemType::GREATER)
        retrieve(key ->right, item, found);
    else if(item.compareTo(key->info) == ItemType::LESS)
        retrieve(key ->left, item,found);
    else
    {
        item = key->info;
        found = true;
    }
}

void BinaryTree::preOrder() const // TODO Print out (Left, Root, Right)
{
    callPreOrder(this->root);
}

void BinaryTree::callPreOrder(TreeNode *key) const
{
    if(key == nullptr)
        return;
    key->info.print();
    callPreOrder(key->left);
    callPreOrder(key->right);

}

void BinaryTree::inOrder() const // TODO Print out (Root, Left, Right)
{
    callInOrder(this->root);
}

void BinaryTree::callInOrder(TreeNode *key) const
{
    if(key == nullptr)
        return;
    callInOrder(key->left);
    key->info.print();
    callInOrder(key->right);
}

void BinaryTree::postOrder() const
{
    callPostOrder(this->root);
}

void BinaryTree::callPostOrder(TreeNode *key) const
{
    if(key == nullptr)
        return;
    callPostOrder(key->left);
    callPostOrder(key->right);
    key->info.print();
}

int BinaryTree::getLength() const
{
    return CountNodes(this->root);
}

int BinaryTree::CountNodes(TreeNode *tree) const
{
    if(tree == nullptr)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}
