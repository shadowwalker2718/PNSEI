//
// Created by root on 10/31/18.
//

#ifndef PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
#define PNSEI_10_REGULAR_EXPRESSION_MATCHING_H

#include "henry.h"

namespace _10{

    // https://leetcode.com/problems/regular-expression-matching/description/
    // substr(N) - N could be the size of the string, but cannot more than that
    class Solution {
    public:
        bool isMatch(string s, string p) {
            if (p.empty()) return s.empty();
            if (p.size()==1) return s.size()==1 and (p[0]==s[0] or p[0]=='.');

            if ('*' == p[1])
                // x* matches empty string or at least one character: x* -> xx*
                // *s is to ensure s is non-empty
                if(isMatch(s, p.substr(2))){ // [x*] matches 0 char
                    return true;
                }else if(!s.empty() &&(s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)){ //[x*] matches 1 char
                    return true;
                }else{
                    return false;
                }
            else
                return !s.empty() &&
                       (s[0] == p[0] || '.' == p[0]) &&
                       isMatch(s.substr(1), p.substr(1));
        }
    };

    void test(){
        string s = "mississippi";
        string p = "mis*is*p*.";
        Solution sln;
        cout << sln.isMatch(s,p)==false << endl;
    }
}

#endif //PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
