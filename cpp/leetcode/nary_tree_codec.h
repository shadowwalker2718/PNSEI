//
// Created by root on 11/19/18.
//

#ifndef PNSEI_NARY_TREE_CODEC_H
#define PNSEI_NARY_TREE_CODEC_H

#include "henry.h"
namespace _428 { //Serialize and Deserialize N-ary Tree

class Node {
public:
  int val = NULL;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Codec {
public:

  // Encodes a tree to a single string.
  string serialize(Node *root) {
    if (root == nullptr) {
      return "[]";
    }
    string result = "[" + to_string(root->val);
    for (Node *child : root->children) {
      result += serialize(child);
    }
    result += "]";

    return result;
  }

  // Decodes your encoded data to tree.
  Node *deserialize(string data) {
    if (data == "[]") {
      return nullptr;
    }

    int i = 1, num = 0, n = data.size();
    while (i < n - 1 && isdigit(data[i])) {
      num = num * 10 + (data[i++] - '0');
    }
    Node *node = new Node(num, {});
    stack<Node *> St;
    while (i < n - 1) {
      if (data[i] == '[') {
        St.push(node);
        ++i;
        num = 0;
        while (i < n - 1 && isdigit(data[i])) {
          num = num * 10 + (data[i++] - '0');
        }
        node = new Node(num, {});
      } else if (data[i] == ']') {
        ++i;
        St.top()->children.push_back(node);
        node = St.top();
        St.pop();
      }
    }

    return node;
  }
};

}
#endif //PNSEI_NARY_TREE_CODEC_H
