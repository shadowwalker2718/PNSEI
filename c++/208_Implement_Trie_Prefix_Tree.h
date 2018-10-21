#pragma once
#include "henry.h"

namespace _208{
	struct TrieNode {
		struct TrieNode* next[26];
		bool isend;
	};

	/** Initialize your data structure here. */
	struct TrieNode* trieCreate() {
		// return (struct TrieNode*)malloc( sizeof(struct TrieNode));
		return (struct TrieNode*)calloc(1,sizeof(struct TrieNode));
	}

	/** Inserts a word into the trie. */
	void insert(struct TrieNode* root, char* word) {
		while (*word) {
			if (!root->next[*word - 'a']) root->next[*word - 'a'] = trieCreate();
			root = root->next[*word - 'a'];
			word++;
		}
		root->isend = true;
	}

	/** Returns if the word is in the trie. */
	bool search(struct TrieNode* root, char* word) {
		while (*word) {
			if (!root->next[*word - 'a']) return false;
			root = root->next[*word - 'a'];
			word++;
		}
		return root->isend;
	}

	/** Returns if there is any word in the trie
	that starts with the given prefix. */
	bool startsWith(struct TrieNode* root, char* prefix) {
		while (*prefix) {
			if (!root->next[*prefix - 'a']) return false;
			root = root->next[*prefix - 'a'];
			prefix++;
		}
		return true;
	}

	/** Deallocates memory previously allocated for the TrieNode. */
	void trieFree(struct TrieNode* root) {
		for (int i = 0; i<26; ++i)
			if (root->next[i]) {
				trieFree(root->next[i]);
			}
		free(root);
	}

	// Your Trie object will be instantiated and called as such:
	// struct TrieNode* node = trieCreate();
	// insert(node, "somestring");
	// search(node, "key");
	// trieFree(node);

	void test() {
		struct TrieNode* node = trieCreate();
		insert(node, "a");
		search(node, "a");
		startsWith(node, "a");
		trieFree(node);
	}
}
