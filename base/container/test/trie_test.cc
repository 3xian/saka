#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "common/macro.h"
#include "container/trie.h"

TEST(TrieTest, Insert) {
    base::Trie<char, int> tree;

    std::string s1 = "apple";
    std::vector<char> v1(s1.begin(), s1.end());

    std::string s2 = "apple tree";
    std::vector<char> v2(s2.begin(), s2.end());

    ASSERT_TRUE(tree.insert(v1, 1));
    ASSERT_TRUE(tree.insert(v2, 1));
    ASSERT_FALSE(tree.insert(v1, 1));
    ASSERT_FALSE(tree.insert(v2, 2));

    tree.clear();
    ASSERT_TRUE(tree.insert(v2, 1));
    ASSERT_TRUE(tree.insert(v1, 1));
}

TEST(TrieTest, Modify) {
    base::Trie<char, int> tree;

    std::string s1 = "apple";
    std::vector<char> v1(s1.begin(), s1.end());

    std::string s2 = "apple tree";
    std::vector<char> v2(s2.begin(), s2.end());

    int value;

    ASSERT_TRUE(tree.insert(v1, 1));
    ASSERT_TRUE(tree.insert(v2, 2));
    ASSERT_TRUE(tree.get_values(v1, &value));
    ASSERT_EQ(value, 1);
    ASSERT_TRUE(tree.get_values(v2, &value));
    ASSERT_EQ(value, 2);

    ASSERT_TRUE(tree.modify(v1, 1111));
    ASSERT_TRUE(tree.modify(v2, 2222));
    ASSERT_TRUE(tree.get_values(v1, &value));
    ASSERT_EQ(value, 1111);
    ASSERT_TRUE(tree.get_values(v2, &value));
    ASSERT_EQ(value, 2222);
}

TEST(TrieTest, Erase) {
    base::Trie<char, int> tree;

    std::string s1 = "apple";
    std::vector<char> v1(s1.begin(), s1.end());

    std::string s2 = "apple tree";
    std::vector<char> v2(s2.begin(), s2.end());

    int value;
    ASSERT_TRUE(tree.insert(v1, 1));
    ASSERT_TRUE(tree.insert(v2, 2));
    ASSERT_TRUE(tree.get_value(v1, &value));
    ASSERT_EQ(value, 1);
    ASSERT_TRUE(tree.erase(v1));
    ASSERT_FALSE(tree.erase(v1));
    ASSERT_FALSE(tree.get_value(v1, &value));
    ASSERT_TRUE(tree.erase(v2));
    ASSERT_FALSE(tree.erase(v2));
}

TEST(TrieTest, SearchSubstr) {
    base::Trie<char, std::string> tree;

    std::string s1 = "apple";
    std::vector<char> v1(s1.begin(), s1.end());

    std::string s2 = "monkey";
    std::vector<char> v2(s2.begin(), s2.end());

    std::string s3 = "pineapple";
    std::vector<char> v3(s3.begin(), s3.end());

    std::string s4 = "  ";
    std::vector<char> v4(s4.begin(), s4.end());

    std::string s5 = "pine";
    std::vector<char> v5(s5.begin(), s5.end());

    ASSERT_TRUE(tree.insert(v1, "[little fruit]"));
    ASSERT_TRUE(tree.insert(v2, "[animal]"));
    ASSERT_TRUE(tree.insert(v3, "[big fruit]"));
    ASSERT_TRUE(tree.insert(v4, "[nothing]"));
    ASSERT_TRUE(tree.insert(v5, "[plant]"));

    std::string context = "Does monkey like pineapples?";
    std::vector<char> vc(context.begin(), context.end());

    std::vector<std::pair<size_t, std::string>> subs = tree.search_substr(vc);
    ASSERT_EQ(subs.size(), 4u);

    std::cout << context << std::endl;
    FOR_EACH (it, subs) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}

TEST(TrieTest, DumpAndLoad) {
    base::Trie<int, int> tree;
    std::vector<int> key;
    for (int j = 0; j < 10; ++j) {
        key.push_back(1234567);
    }
    ASSERT_TRUE(tree.insert(key, 7654321));
    ASSERT_EQ(tree.nodes_count(), 11u);
    ASSERT_TRUE(tree.dump("test.trie"));
    ASSERT_TRUE(tree.load("test.trie"));
    int value;
    ASSERT_EQ(tree.nodes_count(), 11u);
    ASSERT_TRUE(tree.get_value(key, &value));
    ASSERT_EQ(value, 7654321);
}

TEST(TrieTest, Dump) {
    base::Trie<int, int> tree;

    for (int i = 0; i < 100000; ++i) {
        std::vector<int> key;
        for (int j = 0; j < 10; ++j) {
            key.push_back(i);
        }
        ASSERT_TRUE(tree.insert(key, i));
    }
    ASSERT_TRUE(tree.dump("test.trie"));
}

TEST(TrieTest, Load) {
    /*
    base::Trie<int, int> tree;
    ASSERT_TRUE(tree.load("test.trie"));
    for (int i = 0; i < 100000; ++i) {
        std::vector<int> key;
        for (int j = 0; j < 10; ++j) {
            key.push_back(i);
        }
        int value;
        ASSERT_TRUE(tree.get_value(key, &value));
        ASSERT_EQ(value, i);
    }
    for (int i = 0; i < 100000; ++i) {
        std::vector<int> key;
        int len = std::rand() % 20;
        if (len == 10) {
            continue;
        }
        for (int j = 0; j < len; ++j) {
            key.push_back(i);
        }
        int value;
        ASSERT_FALSE(tree.get_value(key, &value));
    }
    */
}
