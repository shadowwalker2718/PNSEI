//
// Created by root on 11/6/18.
//

#ifndef PNSEI_BUILD_TREE_BY_INDENTATION_H
#define PNSEI_BUILD_TREE_BY_INDENTATION_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=453208&highlight=cruise
 * 2018(10-12月) 码农类General 本科 全职@Cruise - 内推 - 技术电面  | Fail | fresh grad应届毕业生
地里推的,感谢&#128591;. 一亩-三分-地,独家发布
九月底做的oa,和大家一样
十月底店面的.
一个印度小哥做data infra的面的.
聊简历
题是建一个树根据indentation
example:
输入
a
    b
   c
     d
        e
      f
输出
           a
       b      c
                   d
                f       e
rule有两条
每行的那个新node先跟上一行比
如果indent比上一行的node多就变成上一个的child
如果少就往上走直到找到indent多的地.
例子里面c就是indent比b少所以往上走,但是他比a的indent多所以变成a的孩子
一开始花时间理解这个规则了一会,然后做出来了
第二天挂了,说不fit
可能是自我介绍讲project那说的不好
========================================================================================

https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=452690&highlight=cruise
2018(10-12月) 码农类General 博士 全职@Cruise - 内推 - 技术电面  | Fail | fresh grad应届毕业生
Cruise 2轮电面  先安排了一次 再安排的第二次
第一轮
LRU Cache
follow up问了一下如果分布式如何处理
第二轮
把一个print出来的tree还原成树的形状 不可以有parent指针
比如
A
   B
   C
          D
       E
   F
A是root  然后儿子有B C F
C的儿子有D和E
字母前面的空格个数不确定,规则是**每个点是他之前空格数量第一个比他少的child**
面完一周之后HR说木有headcount了
*/
#include <utils/todo_binarytree.h>
#include "henry.h"
#include "utils/todo_binarytree.h"

namespace cruise_recover_tree {

nnode* build_tree(vector<string> vs){
  map<int, vector<nnode*>> m;
  for(string s: vs){
    if (s.rfind(' ')==s.npos){
      m[0].push_back(new nnode);
      m[0].back()->key =s.back();
    }else{
      int t=s.rfind(' ');
      auto it=m.lower_bound(t);
      if(it!=m.begin()) --it;

      auto n=new nnode;
      n->key=s.back();
      it->second.back()->children.push_back(n);
      m[t].push_back(n);
    }
  }
  return m[0].front();
}

nnode* build_tree2(vector<string> vs){
  vector<pair<int,nnode*>> m; // {length, node*}
  int i=0;
  for(string s: vs){
    if (s.rfind(' ')==s.npos){
      m.emplace_back(0, new nnode);
      m.back().second->key =s.back();
    }else{
      int t=s.rfind(' '); // t is len
      nnode* par;
      for(int j=m.size()-1;j>=0;j--){
        if(m[j].first<t){
          par=m[j].second;
          break;
        }
      }
      auto n=new nnode;
      n->key=s.back();
      par->children.push_back(n);
      m.emplace_back(t,n);
    }
    i++;
  }
  return m[0].second;
}

void test(){
  vector<string> vs = {"A",
                       "   B",
                       "   C",
                       "          D",
                       "       E",
                       "   F"};
  nnode* n=build_tree(vs);
  vs={
      "a",
      "    b",
      "   c",
      "     d",
      "        e",
      "      f"
  };
  n=build_tree2(vs);
}


}

#endif //PNSEI_BUILD_TREE_BY_INDENTATION_H
