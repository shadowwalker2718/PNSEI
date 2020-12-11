#ifndef PNSEI__721_H
#define PNSEI__721_H

#include "pnsei.h"

//Given a list accounts, each element accounts[i] is a list of strings, where th
//e first element accounts[i][0] is a name, and the rest of the elements are email
//s representing emails of the account.
//
// Now, we would like to merge these accounts. Two accounts definitely belong to
// the same person if there is some email that is common to both accounts. Note th
//at even if two accounts have the same name, they may belong to different people
//as people could have the same name. A person can have any number of accounts ini
//tially, but all of their accounts definitely have the same name.
//
// After merging the accounts, return the accounts in the following format: the
//first element of each account is the name, and the rest of the elements are emai
//ls in sorted order. The accounts themselves can be returned in any order.
//
// Example 1:
//
//Input:
//accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnn
//ybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Ma
//ry", "mary@mail.com"]]
//Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.
//com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
//Explanation:
//The first and third John's are the same person as they have the common email "
//johnsmith@mail.com".
//The second John and Mary are different people as none of their email addresses
// are used by other accounts.
//We could return these lists in any order, for example the answer [['Mary', 'ma
//ry@mail.com'], ['John', 'johnnybravo@mail.com'],
//['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] wo
//uld still be accepted.
//
//
//
// Note:
// The length of accounts will be in the range [1, 1000].
// The length of accounts[i] will be in the range [1, 10].
// The length of accounts[i][j] will be in the range [1, 30].
// Related Topics Depth-first Search Union Find
// 👍 1533 👎 305

// https://stackoverflow.com/questions/23055236/union-find-retrieve-all-members-of-a-set-efficiently
namespace _721{

struct uf{
  vector<int> bo;
  vector<int> sz;
  uf(int i){
    bo.resize(i);
    iota(bo.begin(),bo.end(), 0);
    sz.resize(i);
    fill(sz.begin(), sz.end(), 1);
  }
  int find_boss(int x){
    if (bo[x]!=x)
      bo[x]= find_boss(bo[x]);
    return bo[x];
  }
  void merge(int x, int y){
    int bx= find_boss(x), by= find_boss(y);
    if (bx==by) return;
    if (sz[bx]<sz[by]){ ////
      bo[bx] = by;
      sz[by] += sz[bx], sz[bx] = 0;
    } else {
      bo[by] = bx;
      sz[bx] += sz[by], sz[by] = 0;
    }
  }
};
class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    vector<vector<string>> r;
    uf u(accounts.size());
    map<string, int> m;
    for (int i = 0; i < accounts.size(); ++i) {
      for (int j = 1; j < accounts[i].size(); ++j) {
        string& s=accounts[i][j];
        if (m.count(s)){
          u.merge(i, m[s]);
        } else {
          m[s]=i;
        }
      }
    }
    map<int, set<string>> i2emails;
    for (int i=0;i<u.bo.size();i++){ ////
      for (int j = 1; j < accounts[i].size(); ++j) {
        string e=accounts[i][j];
        i2emails[u.find_boss(i)].insert(e); ////
      }
    }
    for (auto& pr: i2emails) {
      vector<string> vs = {accounts[pr.first][0]};
      for(auto& s: pr.second){
        vs.push_back(s);
      }
      r.push_back(vs);
    }
    return r;
  }
};
}


#endif // PNSEI__721_H
