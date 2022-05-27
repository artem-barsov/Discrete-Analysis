#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char const *argv[]) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char> > a(n, std::vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    int ans = 0;
    std::vector<int> d(m, -1), d1(m), d2(m);
    std::stack<int> st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') d[j] = i;
        }
        while (!st.empty()) st.pop();
        for (int j = 0; j < m; j++) {
            while (!st.empty() && d[st.top()] <= d[j]) st.pop();
            d1[j] = (!st.empty() ? st.top() : -1);
            st.push(j);
        }
        while (!st.empty()) st.pop();
        for (int j = m-1; j >= 0; j--) {
            while (!st.empty() && d[st.top()] <= d[j]) st.pop();
            d2[j] = (!st.empty() ? st.top() : m);
            st.push(j);
        }
        for (int j = 0; j < m; j++)
            ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1));
    }
    std::cout << ans << '\n';
}
