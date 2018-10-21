#pragma once

#include "henry.h"

namespace _254 {
    struct Solution {
        int rec_count = 0, loop_count = 0, push_count=0;
        vector<vector<int>> getFactors(int n) {
            rec_count++;
            vector<vector<int>> res;
            int t = sqrt(n);
            for (int i = 2; i <= t; ++i) {
                loop_count++;
                if (n % i == 0) {
                    res.push_back({ i, n / i });
                    push_count += 2;
                    vector<vector<int>> v = getFactors(n / i);
                    for (auto a : v) {
                        loop_count++;
                        if (i <= a[0]) {
                            a.insert(a.begin(), i);
                            res.push_back(a);
                            push_count++;
                        }
                    }
                }
            }
            return res;
        }
    };

    struct Solution2 {
        vector<vector<int>> getFactors(int n) { // 12
            vector<vector<int>> r;
            vector<int> p;
            dfs(r, p, 2, n);
            return r;
        }
        void dfs(vector<vector<int>>& r, vector<int>& p, int divisor, int dividend) {
            if (dividend == 1) { // dividend / divisor
                if (p.size()>1) r.push_back(p); // [12] is not allowed
                return;
            }
            for (int i = divisor; i <= dividend; ++i) {
                if (dividend%i == 0) { // i是被除数,n/i是相除的结果
                    p.push_back(i);
                    dfs(r, p, i, dividend / i);// why 3rd parameter is i, because 因子从小到大的顺序排列
                    p.pop_back();
                }
            }
        }
    };

    struct Solution3 { // 3ms
        vector<vector<int>> getFactors(int n) {
            vector<vector<int>> res;
            dfs(res, {}, n, 2);
            return res;
        }
        void dfs(vector<vector<int>> &res, vector<int> p, int dividend, int divisor) {
            for (int i = divisor; i <= sqrt(dividend); ++i) {
                if (dividend % i == 0) {
                    vector<int> t = p;
                    t.push_back(i);
                    dfs(res, t, dividend / i, i);
                    t.push_back(dividend / i);
                    res.push_back(t);
                }
            }
        }
    };


    void test() {
        Solution2 sln2;
        auto re=sln2.getFactors(12);
        re.size();

        Solution3 sln3;
        re = sln3.getFactors(32);
        re.size();

        re = sln3.getFactors(16);
        re.size();

        Solution sln;
        vector<vector<int>> v = sln.getFactors(12);
        assert(v.size() == 3);
        cout << sln.rec_count << endl;

        vector<int> rec_count, loop_count, push_count;
        for (int i = 4; i < 1000; i++) {
            sln.rec_count = 0, sln.loop_count = 0, sln.push_count=0;
            sln.getFactors(i);
            rec_count.push_back(sln.rec_count);
            loop_count.push_back(sln.loop_count);
            push_count.push_back(sln.push_count);
        }
        cout << endl;

        cout << "recursion" << endl;
        for (int i : rec_count) {cout << i << ",";} cout << endl;
        cout << "loop times" << endl;
        for (int i : loop_count) { cout << i << ","; } cout << endl;
        cout << "push times" << endl;
        for (int i : push_count) { cout << i << ","; } cout << endl;
        
        cout << endl;
        sln.rec_count = 0;
        auto vv = sln.getFactors(999);
        for (auto v : vv) {
            for (auto i: v) {
                cout << i << ",";
            }
            cout << "\n";
        }
    }
}