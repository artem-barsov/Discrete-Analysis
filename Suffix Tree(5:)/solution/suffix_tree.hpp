#pragma once
#include <iostream>
#include <map>
#include <vector>

class suffix_tree_t {
private:
    const static int INF = 1e9;
    const static int TAB_SIZE = 4;

    struct node_t {
        std::map<char, int> go;
        int l, len;
        int link = 0;

        node_t(int _l, int _len) : l(_l), len(_len) {}
    };

    using item_t = std::pair<char, int>;

    bool can_go(int u, char c) {
        return data[u].go.count(c);
    }
    int go(int u, char c) {
        return data[u].go[c];
    }

    std::string s;
    std::vector<node_t> data;
    int size;
    int nodes;
    int u = 0;
    int rem = 0;

    void go_edge();
    int create_node(int l = 0, int len = INF);
    void build();
    void extend(char c);
    void print_edge(int v, std::ostream & out);
    void print(int id, std::ostream & out, int h);

public:
    suffix_tree_t(const std::string & _s);
    friend std::ostream & operator << (std::ostream & out, suffix_tree_t & st);
    std::string lex_min(int k);
};
