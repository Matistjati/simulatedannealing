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

    int k, n;
    cin >> k >> n;

    vvi adj(n);
    rep(i, n)
    {
        int d;
        cin >> d;
        adj[i].resize(d);
        rep(j, d) cin >> adj[i][j];
        rep(j, d) adj[i][j]--;
    }


    if (n >= k * 5)
    {
        cout << "possible";
        return 0;
    }

    random_device rd;
    mt19937_64 rng(rd());
    uniform_real_distribution<double> dist01(0, 1);
    uniform_int_distribution<int> node_dist(0, n-1);

    int best_score = 0;

    vi cur(n);
    int cur_score = best_score;

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
            increase++;
            repe(e, adj[u]) increase -= cur[e];
        }
        else increase = -1;

        if (increase >= 0 || dist01(rng) < exp(increase / T))
        {
            if (!cur[u]) repe(e, adj[u]) cur[e] = false;
            
            cur[u] = !cur[u];
            cur_score += increase;
            best_score = max(best_score, cur_score);
        }
        
    }

    if (best_score >= k)
    {
        cout << "possible";
    }
    else cout << "impossible";


    return 0;
}
