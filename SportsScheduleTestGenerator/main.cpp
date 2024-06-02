//#include <udacha$$$>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define i128 __int128
#define ld long double
#define ull uint64_t
#define pll pair<ll, ll>
#define pii pair<int, int>
#define pli pair<ll, int>
#define pil pair<int, ll>
#define plli pair<pll, int>
#define pld pair<ld, ld>
#define fst first
#define snd second
#define pdi pair<ld, int>
#define pdd pair<double, double>
#define piii pair<int, pii>
#define plll pair<ll, pll>
#define forn(i, n) for (ll i = 1; i <= n; i++)
#define dforn(i, a, b) for (ll i = a; i <= b; i++)
#define rforn(i, n) for (int i = n; i >= 1; i--)
#define rdforn(i, a, b) for (int i = b; i >= a; i--)
#define sforn(i, a, b, s) for (ll i = a; i <= b; i += s)
#define aforn(v, a) for (auto& v : a)
#define sz(a) (int)a.size()

const int mod = 1e9 + 7;
const ld pi = acos(-1);
const int N = 1e5 + 100;
const int iinf = 1e9;
const ll inf = 1e18;
const ld dinf = 1e12;
const double eps = 1e-10;

void solve() {
    string s;
    cin >> s;
    ofstream fout(s);
    int n, m;
    cin >> n >> m;
    fout << n << " " << m << '\n';
    int tn = n & 1 ? n : n - 1;

    random_device rd;
    mt19937 gen(rd());
    int clim = -1, blim = -1;
    cin >> clim >> blim;

    for(int i = 0; i < tn; i++) {
        for(int j = 0; j < m; j++) fout << gen() % clim + 1 << " ";
        fout << '\n';
    }
    for(int i = 0; i < tn; i++) {
        for(int j = 0; j < m; j++) fout << gen() % blim + 1 << " ";
        fout << '\n';
    }
}

void solve2() {
    string s;
    cin >> s;
    ofstream fout(s);
    int n, m;
    cin >> n >> m;
    fout << n << " " << m << '\n';
    int tn = n & 1 ? n : n - 1;
    ll alpha = 1, beta = 1;
    fout << alpha << " " << beta << '\n';
    random_device rd;
    mt19937 gen(rd());
    int clim = -1, blim = -1;
    cin >> clim >> blim;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) fout << gen() % clim + 1 << " ";
        fout << '\n';
    }
    for(int i = 0; i < tn; i++) {
        for(int j = 0; j < m; j++) fout << gen() % blim + 1 << " ";
        fout << '\n';
    }
    for(int i = 0; i < m; i++) {
        fout << 0 << " ";
    }
    fout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0); int t = 1;
    //cin >> t;
    while (t--) solve2();
    return 0;
}
