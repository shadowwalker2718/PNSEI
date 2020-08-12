//
// Created by henry.wu on 8/9/20.
//

#ifndef PNSEI_TRAVERSE_BT_PARENT_H
#define PNSEI_TRAVERSE_BT_PARENT_H

#include "utils/todo_binarytree.h"

namespace databricks::traverse{

void post_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* last = nullptr;
  while(root){
    if (last == root->parent) {
      if (root->left){
        last = root, root = root->left;
      } else {
        last = nullptr;
      }
    }
    if (last == root->left) {
      if (root->right)
        last = root, root = root->right;
      else
        last = nullptr;
    }
    if (last == root->right) {
      cout << root->val << ",";
      last = root, root = root->parent;
    }
  }
  cout << endl;
}

void pre_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* last = nullptr;
  while(root){
    if (last == root->parent) {
      cout << root->val << ",";
      if (root->left){
        last = root, root = root->left;
      } else {
        last = nullptr;
      }
    }
    if (last == root->left) {
      if (root->right)
        last = root, root = root->right;
      else
        last = nullptr;
    }
    if (last == root->right) {
      last = root, root = root->parent;
    }
  }
  cout << endl;
}

void in_order_traversal(){
  BTPNode* root = createTree5();
  BTPNode* last = nullptr;
  while(root){
    if (last == root->parent) {
      if (root->left){
        last = root, root = root->left;
      } else {
        last = nullptr;
      }
    }
    if (last == root->left) {
      cout << root->val << ",";
      if (root->right)
        last = root, root = root->right;
      else
        last = nullptr;
    }
    if (last == root->right) {
      last = root, root = root->parent;
    }
  }
  cout << endl;
}


}

#endif // PNSEI_TRAVERSE_BT_PARENT_H
