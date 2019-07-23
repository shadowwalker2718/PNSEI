//
// Created by henry on 12/15/18.
//

#ifndef PNSEI_uber_CARPOOL_H
#define PNSEI_uber_CARPOOL_H

// image/uber_riders.png
#include "henry.h"

namespace _uber_carpool {

  namespace simple {

    // Be noted: Car cannot U-turn!!! Must go forward!!!!
    VS city = {"DB--R",
               "-BBRR",
               "-BRB-",
               "-R-RR"};

    struct Solution {
      // BFS
      vector<PII> d={{0,1},{0,-1},{1,0},{-1,0}};
      struct node{
        PII loc;
        int n; // max rider number from start to this node
        bool operator<(const node& o) const // const is a must!!!
        {return loc<o.loc;}
      };
      vector<vector<PII>> pickup(VS city, int rider_number, PII start){
        int R=city.size(), C=city[0].size();
        auto valid=[&](int x,int y){
          return 0<=x and x<R and 0<=y and y<C;
        };
        map<node, set<node>> suc;

        node n={start, 0};
        set<PII> vd;
        queue<node> q;
        q.push(n), vd.insert(n.loc);
        bool found=false;
        while(!q.empty()){
          int z=q.size();
          if(found) break;
          set<PII> tmp_vd;
          while(z--) { // one layer
            auto t = q.front();
            q.pop();
            for (auto pr: d) {
              int nx = t.loc.first + pr.first, ny = t.loc.second + pr.second;
              if (valid(nx, ny) and !vd.count({nx, ny})) {
                tmp_vd.insert({nx, ny});
                if (city[nx][ny] == 'B') continue;
                if (city[nx][ny] == 'R') {
                  node tmp = {{nx, ny}, t.n + 1};
                  suc[t].insert(tmp);
                  q.push(tmp);
                  if (t.n + 1 == rider_number) {
                    found = true;
                  }
                } else if (city[nx][ny] == '-') {
                  node tmp = {{nx, ny}, t.n};
                  suc[t].insert(tmp);
                  q.push(tmp);
                }
              }
            }
          }
          for(auto p: tmp_vd)
            vd.insert(p);
        }

        vector<vector<PII>> r;
        vector<PII> p;
        dfs(city, r, p, suc, n, rider_number);
        return r;
      }

      void dfs(VS city, vector<vector<PII>>& r, vector<PII> p, map<node, set<node>>& suc, node start, const int N){
        if(start.n==N){
          r.push_back(p);
          return;
        }
        for(auto e: suc[start]){
          vector<PII> pp=p;
          if(city[e.loc.first][e.loc.second]=='R'){
            pp.push_back(e.loc);
          }
          dfs(city,r,pp,suc,e,N);
        }
      }
    };

    void test(){
      city = {"D---R",
              "-BBRR",
              "-BRB-",
              "-R-RR"};
      Solution sln;
      vector<vector<PII>> r=sln.pickup(city,2,{0,0});
      assert(r.size() == 2);
      assert(r[0] == vector<PII>({{0,4},{1,4}}));
      assert(r[1] == vector<PII>({{1,3},{1,4}}));
      r=sln.pickup(city,3,{0,0});
      cout << "number of possible paths:" << r.size() << endl;
      for(auto e: r){
        cout << string(80,'*') << endl;
        for(auto loc: e){
          cout << "rider(" << loc.first << "," << loc.second << ")" << endl;
        }
      }

      city = {"D---R",
              "-BBRR",
              "-BRBB",
              "R--RR"};
      r=sln.pickup(city,4,{0,0});
      assert(r.size() == 0);
    }

  }

}

#endif //PNSEI_uber_CARPOOL_H
