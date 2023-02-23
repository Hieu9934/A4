#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef TRIE_H
#define TRIE_H

class Trie{
    Trie* prtArray[26] = {};
    bool isValidWord = false;

public:
    Trie();
    ~Trie();
    Trie(const Trie& other);
    Trie& operator=(Trie other);
    void addAWord(string word);
    bool isAWord(string word);
    vector<string> allWordsBeginningWithPrefix(string prefix);
    void getWordsWithPrefix(vector<string> &listOfWords, string prefix, string currentWord);
};
#endif