#pragma once
#include "henry.h"

namespace _214 {
    struct Solution {
        string shortestPalindrome(string s){
            if (s.size() <= 1) return s;
            int r = 0;
            int hash1 = 0, hash2 = 0, BASE=13, MOD=1000000007, POW=1;
            for (int i = 0; i < s.size(); ++i) {
                hash1 = hash1*BASE+s[i];
                hash2 = hash2 + s[i] * POW;
                if (hash1 == hash2) {
                    int j = 0, k = i, spurious=0;
                    while (j < k) if (s[j++] != s[k--]) { spurious = 1; break; }
                    if(spurious==0) r = i;
                }
                POW *= BASE;
            }
            string tmp = s.substr(r+1);
            reverse(tmp.begin(), tmp.end());
            return tmp + s;
        }
    };

    struct Solution2 {
        string shortestPalindrome(string s) {
            if (s.size() <= 1) return s;
            int r = 0, hash1 = 0, hash2 = 0, BASE = 29, POW = 1, MOD = 1e9 + 7;
            for (int i = 0; i < s.size(); ++i) {
                hash1 = (hash1*BASE + s[i]) % MOD;
                hash2 = (hash2 + s[i] * POW) % MOD;
                if (hash1 == hash2) r = i;
                POW = POW * BASE %MOD;
            }
            string tmp = s.substr(r + 1);
            reverse(tmp.begin(), tmp.end());
            return tmp + s;
        }
    };


    void test() {
        Solution sln;
        assert(sln.shortestPalindrome("aba") == "aba");
        assert(sln.shortestPalindrome("abc") == "cbabc");

        Solution2 sln2;
        assert(sln2.shortestPalindrome("aacecaaa") == "aaacecaaa");
    }
}