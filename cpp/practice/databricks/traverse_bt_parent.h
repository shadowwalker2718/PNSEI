//
// Created by henry.wu on 8/9/20.
//

#ifndef PNSEI_TRAVERSE_BT_PARENT_H
#define PNSEI_TRAVERSE_BT_PARENT_H

#include "utils/todo_binarytree.h"

namespace databricks::traverse{

void post_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* prev = nullptr;
  while(root){
    if (prev == root->parent) {
      if (root->left){
        prev = root, root = root->left;
      } else {
        prev = nullptr;
      }
    }
    if (prev == root->left) {
      if (root->right)
        prev = root, root = root->right;
      else
        prev = nullptr;
    }
    if (prev == root->right) {
      cout << root->val << ",";
      prev = root, root = root->parent;
    }
  }
  cout << endl;
}

void pre_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* prev = nullptr;
  while(root){
    if (prev == root->parent) {
      cout << root->val << ",";
      if (root->left){
        prev = root, root = root->left;
      } else {
        prev = nullptr;
      }
    }
    if (prev == root->left) {
      if (root->right)
        prev = root, root = root->right;
      else
        prev = nullptr;
    }
    if (prev == root->right) {
      prev = root, root = root->parent;
    }
  }
  cout << endl;
}

void in_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* prev = nullptr;
  while(root){
    if (prev == root->parent) {
      if (root->left){
        prev = root, root = root->left;
      } else {
        prev = nullptr;
      }
    }
    if (prev == root->left) {
      cout << root->val << ",";
      if (root->right)
        prev = root, root = root->right;
      else
        prev = nullptr;
    }
    if (prev == root->right) {
      prev = root, root = root->parent;
    }
  }
  cout << endl;
}


}

#endif // PNSEI_TRAVERSE_BT_PARENT_H
