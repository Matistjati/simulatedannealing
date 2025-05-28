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
    uniform_real_distribution<double> dist01(0, 1);
    random_device rd;
    mt19937 rng(rd());
    double T_hi = 10;
    double T_lo = 0.1;
    int prev_score = eval(P);
    while (true)
    {
        double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() / 1000.;
        if (t > 0.99) break;


        int i = dist(rng);
        int j = dist(rng);
        if (i > j) swap(i, j);

        reverse(begin(P) + i, begin(P) + j + 1);
        int new_score = eval(P);
        double T = T_lo * pow(T_hi / T_lo, t);
        if (new_score < prev_score || dist01(rng) < exp(-(new_score - prev_score) / T))
        {
            // keep change
            ans = min(ans, new_score);
            prev_score = new_score;
        }
        else
        {
            // undo change
            reverse(begin(P) + i, begin(P) + j + 1);
        }
    }

    cout << ans;

    return 0;
}
