#include "suffix_tree.hpp"

using namespace std;

using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    std::string t = s + s;
    t.push_back('z' + 1);
    suffix_tree_t st(t);
    cout << st.lex_min(s.size()) << endl;
}
