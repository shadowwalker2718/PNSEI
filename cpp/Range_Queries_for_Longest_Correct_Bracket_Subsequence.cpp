#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define ll long long int
#define pb push_back
#define mp make_pair
#define ull unsigned long long int

struct node {
  int p; //
  int o; // open
  int c; // close
};
node tree[10000];
int n;
node merge(node l, node r) {
  node res;
  int mn = min(l.o, r.c);
  res.p = l.p + r.p + mn;
  res.o = l.o + r.o - mn;
  res.c = l.c + r.c - mn;
  return res;
}
void build(string s) {
  for (int i = 0; i < n; i++) {
    tree[i + n].p = 0;
    tree[i + n].o = (s[i] == '(' ? 1 : 0);
    tree[i + n].c = (s[i] == ')' ? 1 : 0);
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
  }
}
int query(int l, int r) {
  node ans;
  ans.p = 0, ans.o = 0, ans.c = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      ans = merge(ans, tree[l++]);
    if (r & 1)
      ans = merge(ans, tree[--r]);
  }
  return 2 * ans.p;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  string s;
  cin >> s;
  n = s.length();
  build(s);
  while (t--) {
    int l, r;
    cin >> l >> r;
    cout << query(l, r + 1) << endl;
  }
  return 0;
}
