#pragma once
#include "henry.h"

namespace _425 {
#define ix(x) (x-'a')

    struct node {
        bool k = false;// k represent the end of a string
        node *n[26] = {};// Use index to represent the current char, n mean next
    };

    struct trie {
        trie() { r = new node(); }
        void insert(const string& s) {
            node* cur = r;
            for (char c : s) {
                if (cur->n[ix(c)] == 0) cur->n[ix(c)] = new node();
                cur = cur->n[ix(c)];
            }
            cur->k = true;
        }
        vector<string> get_words_start_with(const string& s) {
            vector<string> re;
            node* cur = r;
            for (char c : s) {
                if (cur == 0 || cur->n[ix(c)] == 0) return re;
                cur = cur->n[ix(c)];
            }
            _getwords(cur, re, s);
            return re;
        }
    private:

        void _getwords(node* no, vector<string>& re, const string& prefix) {
            if (no->k) re.push_back(prefix);
            for (int i = 0; i<26; i++)
                if (no->n[i]) _getwords(no->n[i], re, prefix + (char)('a' + i));
        }
        node* r; // root
    };

    class Solution {
    public:
        vector<vector<string>> wordSquares(vector<string>& words) {
            trie tr;
            for_each(words.begin(), words.end(), [&tr](const string& s) {tr.insert(s); });

            vector<vector<string>> r;
            vector<string> p;
            for (string& s : words) f(r, p, s, &tr, 1);
            return r;
        }

        string get_prefix(const vector<string>& vs, int i) {
            string r;
            for (const string& s : vs) r += s[i];
            return r;
        }

        void f(vector<vector<string>>& r, vector<string>& p, string& s, trie* ptr, int start) {
            p.push_back(s);
            if (start >= s.size())
                r.push_back(p);
            else {
                vector<string> t = ptr->get_words_start_with(get_prefix(p, start));
                for (string& ns : t) f(r, p, ns, ptr, start + 1);
            }
            p.pop_back();
        }
    };


    void test() {
        vector<string> vs = { "area", "lead", "wall", "lady", "ball" };
        Solution sln;
        vector<vector<string>> r = sln.wordSquares(vs);
        assert(r.size() == 2);
    }


    class Solution2 {
    public:
        vector<vector<string>> wordSquares(vector<string>& words) {
            n = words[0].size();
            square.resize(n);
            for (string& word : words)
                for (int i = 0; i<n; i++)
                    trie[word.substr(0, i)].push_back(word);
            dfs(0);
            return squares;
        }
        int n;
        unordered_map<string, vector<string>> trie;
        vector<string> square;
        vector<vector<string>> squares;
        void dfs(int i) {
            if (i == n) {
                squares.push_back(square);
                return;
            }
            string prefix;
            for (int k = 0; k<i; k++) prefix += square[k][i];
            for (string word : trie[prefix])
                square[i] = word, dfs(i + 1);
        }
    };

    void test2() {
        vector<string> vs = { "area", "lead", "wall", "lady", "ball" };
        Solution2 sln;
        vector<vector<string>> r = sln.wordSquares(vs);
        assert(r.size() == 2);
    }

    struct Solution3 { // 75ms, 90%
        struct TrieNode {
            vector<const char*> words; //avoid using string for optimization
            int nodes[26] = {};
        };
        vector<vector<string>> wordSquares(vector<string>& words) {
            //1. Build trie
            vector<TrieNode> trie(1); // 0 as root node
            for (const auto& s : words) {
                int i = 0;
                for (char ch : s) {
                    if (trie[i].nodes[ch - 'a'] == 0) {
                        trie[i].nodes[ch - 'a'] = trie.size();
                        trie.push_back(TrieNode());
                    }
                    i = trie[i].nodes[ch - 'a'];
                    trie[i].words.push_back(s.c_str());
                }
            }

            //2. DFS
            vector<vector<string>> r;
            vector<string> p;
            for (string& s : words) dfs(r, p, trie, s.c_str(), 1);
            return r;
        }
        void dfs(vector<vector<string>>& r, vector<string>& p, vector<TrieNode>& trie, const char* s, int k) {
            p.push_back(s);
            if (k == strlen(s)) {
                r.push_back(p);
            } else {
                int i = 0;
                for (string& ns : p)
                    if ((i = trie[i].nodes[ns[k] - 'a']) == 0) break;
                if (i>0) for (const char* ns : trie[i].words) dfs(r, p, trie, ns, k + 1);
            }
            p.pop_back();
        }
    };

    void test3() {
        vector<string> vs = { "area", "lead", "wall", "lady", "ball" };
        Solution3 sln;
        vector<vector<string>> r = sln.wordSquares(vs);
        assert(r.size() == 2);
    }
}
