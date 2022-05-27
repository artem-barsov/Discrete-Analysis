#include <iostream>
#include <vector>
#include <set>

using namespace std;
using Graph = std::vector<std::vector<int> >;

void dfs(Graph& gra, std::vector<char>& used, std::set<int>& con_comp, int u) {
    used[u] = true;
    con_comp.insert(u);
    for (int v : gra[u]) {
        if (used[v]) continue;
        dfs(gra, used, con_comp, v);
    }
}

int main(int argc, char const *argv[]) {
    int n, m;
    std::cin >> n >> m;
    Graph gra(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        gra[u].push_back(v);
        gra[v].push_back(u);
    }
    std::vector<char> used(n, false);
    std::vector<std::set<int> > con_comps;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            con_comps.emplace_back();
            dfs(gra, used, con_comps.back(), i);
        }
    }
    for (auto& con_comp : con_comps) {
        for (int u : con_comp) std::cout << u + 1 << ' ';
        std::cout << '\n';
    }
}
