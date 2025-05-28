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

const int maxn = 250;
signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    assert(n <= maxn);

    vector<bitset<maxn>> adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    mt19937_64 rng(10);
    uniform_real_distribution<double> dist01(0, 1);
    uniform_int_distribution<int> node_dist(0, n - 1);


    bitset<maxn> cur;
    int best_score = 0;
    int cur_score = 0;

    const double Tlo = 1e-3;
    const double Thi = 100;

    auto start = chrono::high_resolution_clock::now();
    while (1)
    {
        double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() / 1000.;
        if (t > 0.99) break;
        double T = Tlo * pow(Thi / Tlo, t);

        int u = node_dist(rng);
        int increase = 0;
        if (!cur[u])
        {
            increase = 1 - (~adj[u] & cur).count();
        }
        else increase = -1;

        if (increase >= 0 || dist01(rng) < exp(increase / T))
        {
            if (!cur[u]) cur = (cur & adj[u]);
            cur[u] = !cur[u];
            cur_score += increase;
            best_score = max(best_score, cur_score);
        }
    }

    cout << best_score;


    return 0;
}
