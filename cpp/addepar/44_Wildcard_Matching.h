//
// Created by root on 10/31/18.
//

#ifndef PNSEI_44_WILDCARD_MATCHING_H
#define PNSEI_44_WILDCARD_MATCHING_H

#include "henry.h"

namespace _44{

    /*
     * 外卡匹配和正则匹配最大的区别就是在星号的使用规则上，对于正则匹配来说，星号不能单独存在，前面必须要有一个字符，
     * 而星号存在的意义就是表明前面这个字符的个数可以是任意个，包括0个，那么就是说即使前面这个字符并没有在s中出现过也无
     * 所谓，只要后面的能匹配上就可以了。而外卡匹配就不是这样的，外卡匹配中的星号跟前面的字符没有半毛钱关系，如果前面
     * 的字符没有匹配上，那么直接返回false了，根本不用管星号。而星号存在的作用是可以表示任意的字符串，当然只是当匹配
     * 字符串缺少一些字符的时候起作用，当匹配字符串包含目标字符串没有的字符时，将无法成功匹配。*/

    class Solution { // TLE
    public:
        bool isMatch(string s, string p) {
            p.erase(unique(p.begin(), p.end(),[](char x, char y){return x==y and x=='*';}), p.end());
            return rec(s, p);
        }
        bool rec(string s, string p) {
            if(p.empty()) return s.empty();
            if(s.empty()){ //"*****" can match ""
                return p.empty() or p=="*";
            }

            if(p[0]=='?'){
                return rec(s.substr(1), p.substr(1));
            }else if(p[0]=='*'){
                string np=p.substr(1);
                for(int i=0; i<=s.size(); i++){
                    if(rec(s.substr(i), np))
                        return true;
                }
                return false;
            }else if(isalpha(p[0])){
                return p[0]==s[0] and rec(s.substr(1), p.substr(1));
            }
        }
    };

    void test(){
        string s="mississippi";
        string p="m??*ss*?i*pi";
        Solution sln;
        cout << sln.isMatch(s,p) << endl;
    }
}

#endif //PNSEI_44_WILDCARD_MATCHING_H
