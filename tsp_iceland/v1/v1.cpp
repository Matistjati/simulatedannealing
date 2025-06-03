#include <bits/allocator.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <immintrin.h>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

#if _LOCAL
    ifstream in("c:/users/matis/in.txt");
    cin.rdbuf(in.rdbuf());
#endif

    int n;
    cin >> n;

    vector<pair<double, double>> pts(n);
    rep(i, n) cin >> pts[i].first >> pts[i].second;

    auto dist = [](pair<double, double> a, pair<double, double> b)
        {
            double dx = a.first - b.first;
            double dy = a.second - b.second;
            return sqrt(dx * dx + dy * dy);
        };

    vector<float> distmat(n * n);
    rep(i, n) rep(j, n) distmat[i * n + j] = dist(pts[i], pts[j]);

    auto eval = [&](vi& p)
        {
            float ret = 0;
            rep(i, n - 1)
            {
                ret += distmat[p[i] * n + p[i + 1]];
            }

            return ret + distmat[p[0] * n + p.back()];
        };

    auto evaldiff = [&](vi& p, int i, int j)
        {
            if (i == 0 && j == n - 1) return float(0);
            int li = i == 0 ? n - 1 : i - 1;
            int hj = j==n-1?0:j+1;
            return -distmat[p[li] * n + p[i]]
                - distmat[p[j] * n + p[hj]]
                + distmat[p[li] * n + p[j]]
                + distmat[p[i] * n + p[hj]];
        };

    auto start = chrono::high_resolution_clock::now();
    double tl = 2;
    double tstart;
    double tend;
    cin >> tstart >> tend;
    vi p(n);
    rep(i, n) p[i] = i;
    float score = eval(p);
    float bestans = score;

    mt19937 rng(11);
    uniform_int_distribution<int> distn(1, n - 1);
    uniform_real_distribution<double> dist01(0, 1);
    int ctr = 0;
    double T = tstart;
    while (true)
    {
        /*if (ctr++ % 100000 == 0)
        {
            cerr << bestans << " " << score << " " << T << "\n";
        }*/
        if (ctr%100==0)
        {
            double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() / (1000 * tl);
            if (t > 0.95) break;
            T = tstart * pow(tend / tstart, t);
        }


        int i = distn(rng);
        int j = distn(rng);
        if (i > j) swap(i, j);
        float nscore = score + evaldiff(p, i, j);
        bestans = min(bestans, nscore);
        if (nscore < score || exp((score - nscore) / T) > dist01(rng))
        {
            reverse(begin(p) + i, begin(p) + j + 1);
            score = nscore;
        }

    }
    //cerr << "ctr=" << ctr << " " << log10(ctr) << "\n";
    cout << bestans;
    // repe(u, p)
    // {
    //     cout << u << " ";
    // }

    return 0;
}
