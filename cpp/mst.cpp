//
// Created by root on 10/30/18.
//

#include <henry.h>

namespace tree{

    int V=5, E=6;
    map<int,map<int,int>> m; // a->b 1
    
    vector<int> bo(V+1,-1);
    int findbo(int x){ return (bo[x]!=-1)?findbo(bo[x]):x;}
    void merge(int x, int y){
        if(findbo(x)==findbo(y)) return;
        x=findbo(x), y=findbo(y);
        bo[x]=y;
    }
    int start=1;
    void init(){
        m[1][2]=3;
        m[1][3]=4;
        m[4][2]=6;
        m[5][2]=2;
        m[2][3]=5;
        m[3][5]=7;
    }
    vector<pair<int,int>> kruskal(){
        init();
        map<int, map<int,int>> es; // weight => a -> b
        for(auto& pr: m)
            for(auto& xy: pr.second)
                es[xy.second][pr.first] = xy.first;
        vector<pair<int,int>> r;
        int sum=0;
        for(auto pr: es){
            auto mp=pr.second;
            for(auto ab : mp){
                if(findbo(ab.first)==findbo(ab.second)) continue;
                r.push_back(ab);
                merge(ab.first, ab.second);
                sum += pr.first;
            }
        }
        cout << sum << endl;
        return r;
    }
    vector<pair<int,int>> prim(){
        init();

    }

    int test(){
        cout << "hello\n";
        auto r=kruskal();
        for (int i = 0; i < r.size(); ++i){
            cout << char('A'+r[i].first-1) << "," << char('A'+r[i].second-1) << endl;
        }
        return 0;
    }

}
