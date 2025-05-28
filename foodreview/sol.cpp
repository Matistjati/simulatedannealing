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

struct UF
{
    vi par;
    vi size;
    int ncomps;
    UF(int n) : par(n), size(n, 1), ncomps(n)
    {
        rep(i, n)par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        ncomps--;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

signed main()
{
    fast();

    int n, r, f;
    cin >> n >> r;

    int fixedcost = 0;

    vector<p2> forced;
    rep(i,r)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        forced.emplace_back(a, b);
        fixedcost += c;
    }

    cin >> f;

    vi costs;
    vector<p2> optional;
    rep(i, f)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        optional.emplace_back(a, b);
        costs.emplace_back(c);
    }

    auto is_feasible = [&](vi& used)
        {
            UF uf(n);
            vi deg(n);

            repe(e, forced)
            {
                deg[e.first]++;
                deg[e.second]++;
                uf.merge(e.first, e.second);
            }

            rep(i, sz(used))
            {
                if (!used[i]) continue;
                uf.merge(optional[i].first, optional[i].second);
                deg[optional[i].first]++;
                deg[optional[i].second]++;
            }

            int numodd = 0;
            rep(i, n) numodd += deg[i] % 2;

            return (numodd==0)&&uf.ncomps==1;
        };

    auto eval = [&](vi& used)
        {
            int cost = 0;

            rep(i, sz(used))
            {
                if (!used[i]) continue;
                cost += costs[i];
            }

            return cost;
        };

    vi used(f);

    auto start = chrono::high_resolution_clock::now();
    uniform_real_distribution<double> dist01(0, 1);
    random_device rd;
    mt19937 rng(rd());
    double T_hi = 100;
    double T_lo = 0.0001;
    int prev_score = eval(used);
    int ans = inf;
    while (true)
    {
        double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() / 1000.;
        if (t > 0.99) break;

        vi sw(f);
        rep(i, sz(sw)) sw[i] = dist01(rng) > 0.8;
        rep(i, sz(sw)) if (sw[i]) used[i] = !used[i];

        int new_score = eval(used)+ is_feasible(used) / t;
        double T = T_lo * pow(T_hi / T_lo, t);
        if ((new_score < prev_score || dist01(rng) < exp(-(new_score - prev_score) / T)))
        {
            // keep change
            if (is_feasible(used)) ans = min(ans, eval(used));
            prev_score = new_score;
        }
        else
        {
            // undo change
            rep(i, sz(sw)) if (sw[i]) used[i] = !used[i];
        }
    }

    cout << ans+fixedcost;

    return 0;
}
