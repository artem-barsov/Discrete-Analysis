#include "suffix_tree.hpp"

void suffix_tree_t::go_edge() {
    do {
        char c = s[size - rem];
        if (!can_go(u, c)) {
            return;
        }
        int v = go(u, c);
        if (rem > data[v].len) {
            rem -= data[v].len;
            u = v;
        } else {
            return;
        }
    } while (1);
}

int suffix_tree_t::create_node(int l, int len) {
    data.push_back(node_t(l, len));
    return ++nodes;
}

void suffix_tree_t::build() {
    size = 0;
    nodes = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        extend(s[i]);
    }
}

void suffix_tree_t::extend(char c) {
    ++size;
    ++rem;
    int last = 0;
    while (rem) {
        go_edge();
        char a = s[size - rem];
        if (!can_go(u, a)) {
            /* Case 1: creating a leaf */
            data[u].go[a] = create_node(size - rem);
            data[last].link = u;
            last = u;
        } else {
            int v = go(u, a);
            int good_len = rem - 1;
            char t = s[data[v].l + good_len];
            if (t != c) {
                /* Case 2: splitting an edge */
                int split = create_node(data[v].l, good_len);
                int new_v = create_node(size - 1, INF);
                data[v].len -= good_len;
                data[v].l += good_len;
                data[u].go[a] = split;
                data[split].go[t] = v;
                data[split].go[c] = new_v;
                data[last].link = split;
                last = split;
            } else {
                /* Case 3: end of phase */
                data[last].link = u;
                return;
            }
        }
        if (u == 0) {
            --rem;
        } else {
            u = data[u].link;
        }
    }
}

void suffix_tree_t::print_edge(int v, std::ostream & out) {
    int edge_len = std::min(size - data[v].l, data[v].len);
    for (int i = 0; i < edge_len; ++i) {
        out << s[data[v].l + i];
    }
}

void suffix_tree_t::print(int id, std::ostream & out, int h) {
    for (item_t elem : data[id].go) {
        for (int i = 0; i < TAB_SIZE * (h - 1); ++i) {
            out << ' ';
        }
        int v = elem.second;
        out << "|-> {id = " << v << ", ";
        print_edge(v, out);
        out << ", link = " << data[v].link << "}\n";
        print(v, out, h + 1);
    }
}

suffix_tree_t::suffix_tree_t(const std::string & _s) : s(_s) {
    create_node(0, INF);
    build();
}

std::ostream & operator << (std::ostream & out, suffix_tree_t & st) {
    out << "root\n";
    st.print(0, out, 1);
    return out;
}

std::string suffix_tree_t::lex_min(int k) {
    int v = data[0].go.begin()->second;
    int pos = 0;
    std::string res;
    while (k) {
        if (pos == data[v].len) {
            v = data[v].go.begin()->second;
            pos = 0;
        } else {
            res.push_back(s[data[v].l + pos]);
            ++pos;
            --k;
        }
    }
    return res;
}
