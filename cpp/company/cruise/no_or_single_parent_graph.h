//
// Created by Henry Wu on 11/6/18.
//

#ifndef PNSEI_NO_OR_SINGLE_PARENT_GRAPH_H
#define PNSEI_NO_OR_SINGLE_PARENT_GRAPH_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=455652&highlight=cruise
 *
 * 2018(10-12月) 码农类General 硕士 全职@Cruise - 内推 - 技术电面  | Other | fresh grad应届毕业生
今早面的,Cruise Infra new grad,9月中做完OA,然后HR放了一个月鸽子.到了10月底直接说背景和skills不fit,要发拒信...最后argue了下给了个电面

拜仁小哥先聊了10分钟简历,接着让手写了下union find的算法.算法题是给了个图,类似于树的结构,一个节点可以有多个parent.
 函数输入是[(parent1,child1),(parent2, child2).....]这样的一个Integer pair list,然后让找只有一个parent或者没
 有parent的节点,比如1,3,7是根节点,没parent.2,4,6是只有一个parent的节点,就返回[1,3,7],[2,4,6]

可能是之前聊的有点多,最后10分钟也没follow up,可能headcount已经没了,就走个形式吧
 *
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=452722&highlight=cruise
 * 一个有向图,给很多pairs比如[[1,2],[4,5],[3,6],[4,2],[5,3],[7,2]],1是2的parent这样,求
 * 1.无parent的node,
 * 2.有一个parent的node.
 * followup:判断两个node有没有公共祖先.
 * */

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=459567
coding是tree 需要输出没有parent的所有nodes 只有一个parent的...
例子
1   2   4
\ /   / \
  3   5   8
   \ / \   \
    6   7   10

zero parent: [1,2,4]
only one parent: [5,8,7,10].

follow up: 如果input为空 如何输出两个空结果 Ex: int[0][0]->[][]
二问没做完 时间不够了
在一问基础上 如果给tree里两个数 返回是否有共同parent 就是是不是在同一分支下 比如
parentChildPairs, 3, 8 => false
parentChildPairs, 5, 8 => true
parentChildPairs, 6, 8 => true
*/

// http://sde.quant365.com/graph.html#topological-sort
#include "henry.h"
namespace _multiparent_tree{

struct mpnode{ // multiparent node
  int v;
  vector<mpnode*> ps;
};

// 一个有向图,给很多pairs比如[[1,2],[4,5],[3,6],[4,2],[5,3],[7,2]],1是2的parent这样
VVI get_zero_indegree_nodes(vector<PII> edges){
  map<int,set<int>> pre;
  set<int> ns;
  for(auto pr: edges){
    pre[pr.second].insert(pr.first);
    ns.insert(pr.first), ns.insert(pr.second);
  }
  VVI r(2,VI());
  VI zero, one;
  for(int i: ns){
    if(pre.count(i)==0)
      zero.push_back(i);
    else if(pre.count(i)==1)
      one.push_back(i);
  }
  r[0]=zero, r[1]=one;
  return r;
}

// lowest common ancestor - MSBFS
VI LCA(vector<PII> edges, int x, int y){
  map<int,set<int>> pre;
  for(auto pr: edges){
    pre[pr.second].insert(pr.first);
  }
  set<int> p1={x}, p2={y};
  VI r;
  while(!p1.empty() && !p2.empty()){
    int t1=*p1.begin(), t2=*p2.begin();
    //TODO
  }
  return r;
};
/*
 1   2   4
  \ /   / \
    3   5   8
     \ / \   \
      6   7   10
*/
void test(){
  vector<PII> v={{1,3},{2,3},{4,5},{4,8},{3,6},{5,7},{8,10}};
  auto r=get_zero_indegree_nodes(v);
  assert(r[0].size()==3);
  r=get_zero_indegree_nodes({{}});
  assert(r[0].size()==0 && r[1].size()==0);
}

}



#endif //PNSEI_NO_OR_SINGLE_PARENT_GRAPH_H
