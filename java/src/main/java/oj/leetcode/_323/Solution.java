package oj.leetcode._323;

// Round 2: 第一题转动图片90图问题，第二题给定顶点之间connections, 求相连组件的数量。
// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

class UF{
    public List<Integer> bo = new ArrayList<>();
    public List<Integer> sz = new ArrayList<>();
    public UF(int n){
        for(int i=0;i<n;i++){
            bo.add(i);
            sz.add(1);
        }
    }
    public Integer find(Integer x){
        if (bo.get(x)!=x)
            bo.set(x, find(bo.get(x)));
        return bo.get(x);
    }
    public void merge(Integer x, Integer y){
        Integer bx = find(x), by = find(y);
        if (bx == by)
            return;
        if(sz.get(bx) < sz.get(by)){
            bo.set(bx, by);
            sz.set(by, sz.get(bx) + sz.get(by));
            sz.set(bx, 0);
        } else {
            bo.set(by, bx);
            sz.set(bx, sz.get(by) + sz.get(bx));
            sz.set(by, 0);
        }
    }
}

public class Solution {
    public int countComponents(int n, int[][] edges) {
        UF u = new UF(n);
        for (int i=0;i<edges.length;i++){
            u.merge(edges[i][0], edges[i][1]);
        }
        int r = 0;
        for (Integer i: u.sz){
            if (i>0)
                r++;
        }
        return r;
    }

    public static void main(String[] args){
        int[][] edges = {
                {0, 1}, {1, 2}, {3, 4}
        };
        Solution sln = new Solution();
        int r = sln.countComponents(5, edges);
        assertEquals(r, 2);
    }

}
