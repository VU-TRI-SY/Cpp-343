// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap
{

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap() = default;

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node
  {
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;

    Node(value_type d)
    { // create single node
      data = d;
      left = nullptr;
      right = nullptr;
    }
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);

  // helper function to compare 2 Strings by prefix
  int compareNode(Node *n1, Node *n2)
  {
    string s1 = n1->data.first;
    string s2 = n2->data.first;
    int compare_val = s1.compare(s2);

    if (compare_val < 0)
      return -1;
    if (compare_val == 0)
      return 0;
    else
      return 1;
  }

  Node *copyTree(Node *tree2)
  {
    if (tree2 == nullptr)
    {
      return nullptr;
    }
    Node *newNode = new Node(tree2->data);
    newNode->left = copyTree(tree2->left);
    newNode->right = copyTree(tree2->right);
    return newNode;
  }

  void destroyTree(Node *node)
  {
    if (node != nullptr)
    {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  int countAllNodes(Node *root) const
  {
    if (root == nullptr)
      return 0;

    return 1 + countAllNodes(root->left) + countAllNodes(root->right);
  }

  void inorder_helper(Node *node, void visit(const value_type &item)) const
  {
    
    
    if (node != nullptr)
    {
      inorder_helper(node->left, visit);
      // visit(node->data);
      cout << "(" << node->data.first << ", " << node->data.second << ") ";
      inorder_helper(node->right, visit);
    }
  }

  void preorder_helper(Node *node, void visit(const value_type &item)) const
  {
    
    if (node != nullptr)
    {
      visit(node->data);
      preorder_helper(node->left, visit);
      preorder_helper(node->right, visit);
    }
  }

  void postorder_helper(Node *node, void visit(const value_type &item)) const
  {
    if (node != nullptr)
    {
      postorder_helper(node->left, visit);
      postorder_helper(node->right, visit);
      visit(node->data);
    }
  }

  void saveInorder(Node* root, vector<value_type>& vt){
    if(root == nullptr)
      return;

    saveInorder(root->left, vt);
    vt.push_back(root->data);
    saveInorder(root->right, vt);
  }

  bool compareTwoTrees(Node* root1, Node* root2) const{
    if(root1 == nullptr && root2 == nullptr){
      return true;
    }

    if(root1 == nullptr || root2 == nullptr){
      return false;
    }

    // if(root1 != nullptr && root2 == nullptr){
    //   return false;
    // }

    //2 trees are not empty
    if(root1->data.first != root2->data.first || root1->data.second != root2->data.second){
      return false;
    }

    // return compareTwoTrees(root1->left, root2->left) && compareTwoTrees(root1->right, root2->right);
    if(compareTwoTrees(root1->left, root2->left) == true){
      return compareTwoTrees(root1->right, root2->right);
    }else{
      return false;
    }
  }

  bool isPrefix(const key_type& k1, const key_type& k2) const{//check k2 is substring (prefix) of k1 or not
    size_t i = 0;
    size_t j = 0;
    size_t len1 = k1.size();
    size_t len2 = k2.size();

    while(i < len1 && j < len2){
      if(k1[i] != k2[j])
        return false;
      
      i++;
      j++;
    }

    //"Helloaaaa"
    //"Hello"
    if(i == len1 && j == len2)
      return true;

    if(j == len2 && i < len1)
      return true;

    //i = len1 and j < len2
    return false;
  } 

  void addAll_helper(Node* root, vector<value_type>& vt, const key_type &k) const{
    if(root == nullptr) return;

    //k = "Seat"
    //root->data = <"Seaton, South Australia, Australia", 9704>
    if(isPrefix(root->data.first, k)){ //check k is prefix of root->data.first
      vt.push_back(root->data);
      addAll_helper(root->left, vt, k);
      addAll_helper(root->right, vt, k);
    }else{
      int compare_val = k.compare(root->data.first);
      if(compare_val < 0){ // k < key of root
        addAll_helper(root->left, vt, k);
      }else{
        addAll_helper(root->right, vt, k);
      }
    }
  }

  Node* rebalance_helper(vector<value_type>& vt, int left, int right){
    if (left > right) {
      return nullptr;
    }
    int mid = (left + right) / 2;
    Node* node = new Node(vt[mid]);
    node->left = rebalance_helper(vt, left, mid - 1);
    node->right = rebalance_helper(vt, mid + 1, right);
    return node;
  }


  // Node* rebalance_helper(Node*& root, vector<value_type>& vt, int left, int right){
  //   if(left > right) return nullptr;
  //   int mid = (left + right)/2;
  //   root = new Node(vt[mid]);
  //   root->left = rebalance_helper(root->left, vt, left, mid-1);
  //   root->right = rebalance_helper(root->right, vt, mid+1, right);
  //   return root;
  // }


  Node* findMin_helper(Node* node){
    while(node->left != nullptr){
      node = node->left;
    }
    return node;
  }

  Node* deleteNode_helper(Node* root,const key_type &k) {
    if (root == NULL) return NULL;
    int compare_val = k.compare(root->data.first);
    if (compare_val < 0) {
        root->left = deleteNode_helper(root->left, k);
    } else if (compare_val > 0) {
        root->right = deleteNode_helper(root->right, k);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* minNode = findMin_helper(root->right);
            root->data = minNode->data;
            root->right = deleteNode_helper(root->right, minNode->data.first);
        }
    }
    return root;
}
};

#endif // BSTMAP_H
