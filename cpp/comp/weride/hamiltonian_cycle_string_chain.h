//
// Created by Henry Wu on 11/24/18.
//

#ifndef PNSEI_HAMILTONIAN_CYCLE_STRING_CHAIN_H
#define PNSEI_HAMILTONIAN_CYCLE_STRING_CHAIN_H
// http://www.ams.org/publicoutreach/feature-column/fcarc-dna-abc2
// https://proofwiki.org/wiki/Directed_Hamilton_Cycle_Problem_is_NP-complete
// https://blog.csdn.net/lmq_begood/article/details/52275570
// https://blog.csdn.net/rhx_qiuzhi/article/details/52402853
/*
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=314760&highlight=jingchi
2017(10-12月) 码农类General 硕士 全职@jingchi - 校园招聘会 - 技术电面 Onsite  | Pass | fresh grad应届毕业生
电面:给一列字符串,判断是否能接龙.接龙相邻的两个字符串要求满足 前一个的最后一个字符等于后一个的第一个字符.follow up:construct接龙顺序
onsite:
1. 一维直线上有若干村庄,能够建若干个仓库,每个村庄的cost为距离其最近的仓库到它距离的平方,求最小cost总和
2. 给一个矩阵,0表示无障碍物,1表示有障碍物,从上往下走,问有多少条路径可以到达最下的边,
例:
00000
00100
00000
有左右两条路径
3. 给一堆数字字符串,求拼接得到的最大的字符串
for example: "12", "123" -> "12312" > "12123".
*/

#include "henry.h"

namespace _weride_hamiltonian{

// 电面:给一列字符串,判断是否能接龙.接龙相邻的两个字符串要求满足 前一个的最后一个字符等于后一个的第一个字符.
/*
 * Urumic 发表于 2018-2-2 07:02
请问楼主,电面那道题,construct接龙就是调换数组元素的位置让他组成接龙对吗?
对,返回正确的一种就行了.input: ["abc", "bca", "cab"], output: ["abc","cab","bca"] or ["bca", "abc", "cab"] or ...
 * */
// kind of like hamiltonian cycle, but this is not cycle problem
struct Solution{
  map<int,set<int>> pre;
  map<int,set<int>> suc;
  
  bool is_strings_chainable(const vector<string>& vs){
    int L=vs.size();
    REP(i,0,L){
      REP(j,0,L){
        if (i==j || vs[i].empty() || vs[j].empty())
          continue;
        if(vs[i].back()==vs[j].front()){
          pre[j].insert(i), suc[i].insert(j);
        }
        if(vs[j].back()==vs[i].front()){
          suc[j].insert(i), pre[i].insert(j);
        }
      }
    }
    // pre-check
    vector<bool> bs(L);
    for(auto pr: pre)
      bs[pr.first] = true;
    if (count(bs.begin(),bs.end(),true)<L-1)
      return false;
    fill(bs.begin(), bs.end(), false);
    for(auto pr: suc)
      bs[pr.first] = true;
    if (count(bs.begin(),bs.end(),true)<L-1)
      return false;
    // DFS with each node like topological sort CLRS 613, but may have cycle
    for(int i=0;i<vs.size();i++){
      VI p;
      vector<bool> vd(L);
      if (dfs(p, vd, i, L)){
        return true;
      }
    }
    return false;
  }
  
  bool dfs(VI& p, VB& vd, int i, int L){
    p.push_back(i);
    if(p.size()==L)
      return true;
    vd[i]=true;
    for(auto j: suc[i]){
      if(vd[j]) continue;
      if (dfs(p,vd,j,L))
        return true;
    }
    return false;
  }

};

void test(){
  Solution sln;
  VS vs= {"gj","jl","dg","ad","gg"};
  assert(sln.is_strings_chainable(vs));
}
}

#endif //PNSEI_HAMILTONIAN_CYCLE_STRING_CHAIN_H
