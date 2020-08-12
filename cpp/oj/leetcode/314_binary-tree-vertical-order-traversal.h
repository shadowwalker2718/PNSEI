#ifndef PNSEI_314_BINARY_TREE_VERTICAL_ORDER_TRAVERSAL_H
#define PNSEI_314_BINARY_TREE_VERTICAL_ORDER_TRAVERSAL_H

#include "utils/todo_binarytree.h"

namespace _314 {
  struct Solution {
    vector<vector<int>> verticalOrder(TreeNode* root) {
      if(!root) return vector<vector<int>>();
      int ml=0, mr=0;
      dfs1(root,0,0,ml,mr);
      int L=ml+mr+1;
      vector<vector<int>> rt(L, vector<int>());
      dfs2(rt, root, ml);
      return rt;
    }
    void dfs1(TreeNode* n, int l, int r, int& ml, int& mr){
      if(!n) return;
      dfs1(n->left,l+1,r,ml,mr);
      dfs1(n->right,l,r+1,ml,mr);
      ml = max(ml, l-r);
      mr = max(mr, r-l);
    }
    void dfs2(vector<vector<int>>& r, TreeNode* n, int idx){
      if(!n) return;
      r[idx].push_back(n->val);
      dfs2(r,n->left,idx-1);
      dfs2(r,n->right,idx+1);
    }
  };

  struct Solution2 {
    vector<vector<int>> verticalOrder(TreeNode* root) {
      if(!root) return vector<vector<int>>();
      int ml=0, mr=0;
      dfs(root,0,0,ml,mr);
      int L=ml+mr+1;
      vector<vector<int>> rt(L, vector<int>());
      bfs(rt, root, ml);
      return rt;
    }
    void dfs(TreeNode* n, int l, int r, int& ml, int& mr){
      if(!n) return;
      dfs(n->left,l+1,r,ml,mr);
      dfs(n->right,l,r+1,ml,mr);
      ml = max(ml, l-r), mr = max(mr, r-l);
    }
    void bfs(vector<vector<int>>& r, TreeNode* n, int idx){
      queue<pair<TreeNode*, int>> q;
      q.push({n,idx});
      while(!q.empty()){
        int sz=q.size();
        while(sz--){
          auto t=q.front(); q.pop();
          r[t.second].push_back(t.first->val);
          if(t.first->left) q.push({t.first->left, t.second-1});
          if(t.first->right) q.push({t.first->right, t.second+1});
        }
      }
    }
  };

  void test(){
    TreeNode* tn = createTree1();
    Solution sln;
    auto r = sln.verticalOrder(tn);
    for_each(r.begin(), r.end(), [](auto& vi){
      for_each(vi.begin(), vi.end(), [](int i){
        cout << i << ",";
      });
      cout << "@" << endl;
    });
  }

void test2(){
  TreeNode* tn = createTree1();
  Solution2 sln;
  auto r = sln.verticalOrder(tn);
  for_each(r.begin(), r.end(), [](auto& vi){
    for_each(vi.begin(), vi.end(), [](int i){
      cout << i << ",";
    });
    cout << "@" << endl;
  });
}

}

#endif // PNSEI_314_BINARY_TREE_VERTICAL_ORDER_TRAVERSAL_H
