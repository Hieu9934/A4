#include <iostream>
#include <fstream>
#include <string.h>
#include "Trie.h"
#include "gtest/gtest.h"

using namespace std;

class TrieTest : public ::testing::Test{
    protected:
    Trie* myTrie = new Trie();

    TrieTest(){
        myTrie->addAWord("cat");
        myTrie->addAWord("catenate");
        myTrie->addAWord("catwalk");
        myTrie->addAWord("cool");
        myTrie->addAWord("cooldown");
        myTrie->addAWord("cooler");
        myTrie->addAWord("fish");
        myTrie->addAWord("fishing");
        myTrie->addAWord("fisherman");
        myTrie->addAWord("dog");
        myTrie->addAWord("catwalking");
        myTrie->addAWord("doggo");
    }

    ~TrieTest() override {
        delete myTrie;
    }

};

TEST_F(TrieTest, TestIsAWord) {
    EXPECT_TRUE(myTrie->isAWord("cat"));
    EXPECT_FALSE(myTrie->isAWord("catty"));
}

TEST_F(TrieTest, TestAddAWord) {
    EXPECT_FALSE(myTrie->isAWord("fishy"));
    myTrie->addAWord("fishy");
    EXPECT_TRUE(myTrie->isAWord("fishy"));
}

TEST_F(TrieTest, TestIsAWordInvalidInput) {
    EXPECT_FALSE(myTrie->isAWord("cAt"));
    EXPECT_FALSE(myTrie->isAWord("coo|er"));
}

TEST_F(TrieTest, TestCopyConstructor) {
    Trie* copy = new Trie(*(myTrie));
    EXPECT_TRUE(copy->isAWord("cooldown"));
    myTrie->addAWord("cooldowntime");
    EXPECT_TRUE(myTrie->isAWord("cooldowntime"));
    EXPECT_FALSE(copy->isAWord("cooldowntime"));
    delete copy;
}

TEST_F(TrieTest, TestAssignmentOperator) {
    Trie* copy = new Trie();
    EXPECT_FALSE(copy->isAWord("dog"));
    EXPECT_FALSE(copy->isAWord("fishing"));
    *copy = *myTrie;
    EXPECT_TRUE(copy->isAWord("dog"));
    EXPECT_TRUE(copy->isAWord("fishing"));
    delete copy;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}