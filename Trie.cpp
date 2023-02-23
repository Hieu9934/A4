#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Trie.h"
using namespace std;

// Default constructor
Trie::Trie(){}

// Destructor
Trie::~Trie(){
    for (int i = 0; i < 26; i++){
        delete prtArray[i];
    }   
}

// Copy constructor
Trie::Trie(const Trie& other){
    isValidWord = other.isValidWord;
    for (int i = 0; i < 26; i++){
        prtArray[i] = nullptr;
        if (other.prtArray[i])
            prtArray[i] = new Trie(*(other.prtArray[i]));
    }
}

// Assignment operator
Trie& Trie::operator=(Trie other){
    std::swap(isValidWord, other.isValidWord);
    for (int i = 0; i < 26; i++){
        std::swap(prtArray[i], other.prtArray[i]);
    }
    return *this;
}

// This method adds a word if it is not contained in the Trie yet.
void Trie::addAWord(string word){
    // If this is the end of a word, this node leads to a valid word.
    if (word.compare("") == 0){
        isValidWord = true;
        return;
    } else {
        int index = int(word.front()) - int('a');
        // If this word is not added yet, create necessary nodes for letters.
        if (prtArray[index] == nullptr){
            prtArray[index] = new Trie();
        }
        // If this is not the end of a word, keep iterating through all letters of word
        if (word.length() == 1){
            (prtArray[index])->addAWord("");
        } else {
            (prtArray[index])->addAWord(word.substr(1));
        }
    }
}

// This method checks if input word is a valid word in Trie.
bool Trie::isAWord(string word){
    if (word.length() == 0){
        // If no more letter, check if it is a valid word
        return isValidWord;
    }
    int index = int(word.front()) - int('a');
    // A non-letter character will be outside of range of prtArray
    if (index < 0 || index >= 26){
        return false;
    } else if (prtArray[index] == nullptr){
        // If cannot keep iteraing the letters, it is not a word
        return false;
    } else {
        // Otherwise, keep iterating the word
        if (word.length() == 1){
            return (prtArray[index])->isAWord("");
        } else { 
            return (prtArray[index])->isAWord(word.substr(1));
        }
    }
}

// This method get all words starring with the input prefix.
vector<string> Trie::allWordsBeginningWithPrefix(string prefix){
    vector<string> listOfWords = {};
    vector<string> &listReference = listOfWords;
    string word = ""; 
    getWordsWithPrefix(listReference, prefix, word);
    return listOfWords;
}

// This helper driver method traverses through Trie to get all necessary words.
void Trie::getWordsWithPrefix(vector<string> &listOfWords, string prefix, string currentWord){
    // When not done traversing the prefix.
    if (prefix.compare("") != 0){
        int index = int(prefix.front()) - int('a');
        if (index < 0 || index >= 26){
            // If prefix contains invalid symbol, stop.
            return;
        } else if (prtArray[index] == nullptr){
            // If prefix cannot be traversed anymore, no word has this prefix, so stop.
            return;
        } else {
            currentWord += prefix.front();
            if (prefix.length() > 1){
                (prtArray[index])->getWordsWithPrefix(listOfWords, prefix.substr(1), currentWord);
            } else {
                (prtArray[index])->getWordsWithPrefix(listOfWords, "", currentWord);
            }
        }
    } else {
        if (isValidWord){
            // Put any valid word to listOfWords.
            listOfWords.push_back(currentWord);
        }
        // When done checking prefix, loop through prtArray and add any existed letter to get the next word.
        for (int i = 0; i < 26; i++){
            if (prtArray[i] != nullptr){
                char letter = char(i + int('a'));
                string temp = currentWord + letter;
                (prtArray[i])->getWordsWithPrefix(listOfWords, "", temp);
            }
        }
    }
}
