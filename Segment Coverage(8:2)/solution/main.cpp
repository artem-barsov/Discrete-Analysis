#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;
using ll = long long;

struct Segment {
    ll l, r;
    int id;
};

int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;
    std::vector<Segment> segs(n);
    for (int i = 0; i < n; i++) {
        std::cin >> segs[i].l >> segs[i].r;
        segs[i].id = i;
    }
    ll m;
    std::cin >> m;
    sort(segs.begin(), segs.end(), [&](const Segment& lhs, const Segment& rhs) {
        return std::tie(lhs.l, rhs.r, lhs.id) < std::tie(rhs.l, lhs.r, rhs.id);
    });
    std::vector<Segment> cover = {{-1, 0, -1}};
    Segment best = {-1, -1, -1};
    bool ok = false;
    for (auto& seg : segs) {                    // seg - (), last - [], best - {}
        if (seg.r <= cover.back().r) continue;  // ...)...]... => skip
        if (seg.l <= cover.back().r) {          // ...(...]... => consider best?
            if (best.r < seg.r) {               // ...}...)... => new best
                best = seg;
                if (m <= best.r) {              // ...M...}... => good end
                    cover.push_back(best);
                    ok = true;
                    break;
                }
            }
        }
        else {                                  // ...]...(... => need changes
            if (seg.l <= best.r) {              // ...(...}... => new last
                cover.push_back(best);
                best = seg;
                if (m <= best.r) {              // ...M...}... => good end
                    cover.push_back(best);
                    ok = true;
                    break;
                }
            }
            else {                              // ...}...(... => bad end
                ok = false;
                break;
            }
        }
    }
    if (ok) {
        sort(cover.begin(), cover.end(), [&](const Segment& lhs, const Segment& rhs) {
            return lhs.id < rhs.id;
        });
        std::cout << cover.size() - 1 << '\n';
        for (int i = 1; i < cover.size(); i++)
            std::cout << cover[i].l << ' ' << cover[i].r << '\n';
    }
    else std::cout << 0 << '\n';
}
