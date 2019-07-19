//
// Created by root on 1/29/19.
//

#ifndef PNSEI_TT_H
#define PNSEI_TT_H

#include "henry.h"

struct  node{
  int id;
  string match;
  set<node*> next;
};

//vector<set<string>> levels_matches;

map<int, int> id2price;

// j in Root->next
node* helper(string s, set<node*> next){
  for(node* n: next){ //
    if (s == n->match)
      return n;
  }
  return 0;
}

int sum=0;
void get_price(node* Root, set<string> jobs){ // 2bed, 3ba, pets
  if (!Root) return;
  for(string j: jobs){
    node *n=0;
    if (n=helper(j, Root->next)){
      if(n->next.empty()){
        sum += id2price[n->id];
        return;
      }
      get_price(n, jobs);
    }
  }
}

void test(){
  node Root={0};
  node n1={1,"2bed"};
  node n2={2,"2bath"};
  node n3={3,"3bath"};
  node n4={4,"3bed"};
  node n5={5,"2bed"};
  node n6={6,"3bed"};
  node n7={7,"pets"};
  Root.next={&n1,&n4,&n7};
  n1.next={&n2,&n3};
  n4.next={&n5,&n6};
  id2price[2]=120;
  id2price[7]=20;




}




#endif //PNSEI_TT_H
