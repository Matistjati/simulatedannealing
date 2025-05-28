#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    string piece;
    cin >> piece;
    int tl;
    cin >> tl;
    map<char, int> remap;
    repe(c, piece) if (!remap.count(c)) remap[c] = sz(remap);
    int n = sz(remap);
    vvi A(n, vi(n));

    rep(i, sz(piece) - 1)
    {
        A[remap[piece[i]]][remap[piece[i + 1]]]++;
    }

    int ans = inf;

    vi P(n);
    rep(i, n) P[i] = i;

    auto eval = [&](vi& perm)
        {
            int cost = 0;

            rep(i, n)
            {
                rep(j, n)
                {
                    cost += abs(distance(find(all(P), i), find(all(P), j))) * A[i][j];
                }
            }

            return cost;
        };

    auto start = chrono::high_resolution_clock::now();
    uniform_int_distribution<int> dist(0, n - 1);
    random_device rd;
    mt19937 rng(rd());
    shuffle(all(P), rng);
    while (true)
    {
        double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() / double(tl);
        if (t > 0.95) break;

        int i = dist(rng);
        int j = dist(rng);
        if (i > j) swap(i, j);

        int scorebefore = eval(P);
        ans = min(ans, scorebefore);
        reverse(begin(P)+i, begin(P)+j+1);
        if (eval(P) > scorebefore) // if new score is worse, undo
        {
            reverse(begin(P)+i, begin(P)+j+1);
        }
    }

    cout << ans;

    return 0;
}
