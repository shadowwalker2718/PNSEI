import collections

"""
  https://leetcode.com/problems/prefix-and-suffix-search/

  Intuition and Algorithm

  Consider the word 'apple'. For each suffix of the word, we could insert that suffix, 
  followed by '#', followed by the word, all into the trie.

  For example, we will insert '#apple', 'e#apple', 'le#apple', 'ple#apple',
 'pple#apple', 'apple#apple' into the trie. Then for a query like prefix = "ap",
  suffix = "le", we can find it by querying our trie for le#ap.
"""


Trie = lambda: collections.defaultdict(Trie)
WEIGHT = False


class WordFilter(object):
    def __init__(self, words):
        self.trie = Trie()
        for weight, word in enumerate(words):
            word += '#'
            for i in xrange(len(word)):
                cur = self.trie
                cur[WEIGHT] = weight
                for j in xrange(i, 2 * len(word) - 1):
                    cur = cur[word[j % len(word)]]
                    cur[WEIGHT] = weight

    def f(self, prefix, suffix):
        cur = self.trie
        for letter in suffix + '#' + prefix:
            if letter not in cur:
                return -1
            cur = cur[letter]
        return cur[WEIGHT]


wf = WordFilter(['apple', "banana", 'able'])
assert (wf.f(prefix="ap", suffix="le") == 0)
assert (wf.f(prefix="b", suffix="na") == 1)
assert (wf.f(prefix="a", suffix="e") == 2)
