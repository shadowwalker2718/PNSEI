#include <gtest/gtest.h>
#include "987.h"
#include "987_simplified.h"

TEST(_987, basic){
  using namespace _987;
  Solution sln;
  TreeNode* root = createTree2();
  vector<vector<int>> result=sln.verticalTraversal(root);
  for (int i = 0; i < result.size(); ++i) {
    for (int j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << ",";
    }
    cout << endl;
  }
}

TEST(_987, simplified){
  using namespace _987_2;
  Solution sln;
  TreeNode* root = createTree2();
  vector<vector<int>> result=sln.verticalTraversal(root);
  for (int i = 0; i < result.size(); ++i) {
    for (int j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << ",";
    }
    cout << endl;
  }
}