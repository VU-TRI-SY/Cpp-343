// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>
#include <algorithm>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst)
{
  root = copyTree(bst.root);
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v)
{
  // sort input vector: ascending order
  // call rebalance_helper
  vector<value_type> vt;
  for (int i = 0; i < v.size(); i++)
  {
    vt.push_back(v[i]);
  }

  sort(vt.begin(), vt.end(), [](const value_type &v1, const value_type &v2)
       { return v1.first < v2.first; });
  root = rebalance_helper(vt, 0, vt.size() - 1);
}

// destructor
BSTMap::~BSTMap()
{
  clear();
}

// delete all nodes in tree
void BSTMap::clear()
{
  destroyTree(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const
{
  return root == nullptr;
}

// Number of nodes in BST
int BSTMap::size() const
{
  return countAllNodes(root);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const
{
  if (root == nullptr)
    return false;

  Node *cur = root;
  while (cur != nullptr)
  {
    int compare_res = key.compare(cur->data.first);
    if (compare_res == 0)
      return true;

    if (compare_res < 0) // seacrh to left side
      cur = cur->left;
    else
      cur = cur->right;
  }

  return false;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k)
{
  // assert(false && "operator[] has not been implemented");
  // return root->data.second;
  if (root == nullptr)
  {
    root = new Node({k, 0});
    return root->data.second;
  }

  Node *cur = root;
  while (cur != nullptr)
  {
    int compare_res = k.compare(cur->data.first);
    if (compare_res == 0)
      return cur->data.second;

    if (compare_res < 0)
    {
      if (cur->left == nullptr)
      {
        cur->left = new Node({k, 0});
        return cur->left->data.second;
      }
      else
      {
        cur = cur->left;
      }
    }
    else
    {
      if (cur->right == nullptr)
      {
        cur->right = new Node({k, 0});
        return cur->right->data.second;
      }
      else
      {
        cur = cur->right;
      }
    }
  }
  return root->data.second;
}
// Seat
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const
{
  vector<value_type> v;
  addAll_helper(root, v, k);
  return v;
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const
{
  return getHeight(root);
}

int BSTMap::getHeight(const Node *n)
{
  if (n == nullptr)
  {
    return 0;
  }
  return 1 + max(getHeight(n->left), getHeight(n->right));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const key_type &k) const
{
  return contains(k);
}

// created a helper function in header file
// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const
{
  // created a helper function in header file
  inorder_helper(root, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const
{
  // helper function
  preorder_helper(root, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const
{
  // helper function
  postorder_helper(root, visit);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance()
{
  // save all nods to a vector inorder
  vector<value_type> vt;
  saveInorder(root, vt);
  // recreating the BST
  //  BSTMap(vt);
  clear(); // clear tree
  root = rebalance_helper(vt, 0, vt.size() - 1);
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const
{
  return compareTwoTrees(root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const
{
  return !compareTwoTrees(root, other.root);
}

bool BSTMap::erase(const key_type &k)
{
  if (contains(k) == true)
  {
    deleteNode_helper(root, k);
    return true;
  }
  else
    return false;
}
