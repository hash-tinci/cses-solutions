/*
* author - qt
*/

// * Headers
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// * @brief Ordered set
// * @return kth smallest keys
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// * @brief Ordered MultiSet
// * @return kth smallest keys
template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define pb push_back
#define cy cout << "YES\n"
#define cn cout << "NO\n"
#define c1 cout << "-1\n"
#define line cout << endl
#define all(x) x.begin() , x.end()
using vi = vector<int>;
using vs = vector<string>;
using pi = pair<int,int>;

#define six_eyes ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define int64 long long
#define FAST_EXECUTION 

#ifdef FAST_EXECUTION
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:247474112")
#endif

const int64 mod = 1e9 + 7;
const int N = 1e5 + 5;
const int inf = 1e8;

vector<int64> fac(N), inv(N), sieve;

// * @brief Computes GCD 
int64 gcd(int64 a, int64 b) {
    return b == 0 ? a : gcd(b, a % b);
}


// * @brief Computes `a^b`
int64 binpow(int64 a, int64 b) {
    int64 res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// * @brief Computes Division with MOD
int64 modulardivision(int64 p, int64 q) {
    return (p % mod * binpow(q, mod - 2)) % mod;
}

// * @brief Computes Combinatrix problems 
void pre(int64 n) {
    fac[0] = 1;
    for (int64 i = 1; i <= n; ++i)
        fac[i] = (fac[i - 1] * i) % mod;
    inv[n] = binpow(fac[n], mod - 2);
    for (int64 i = n - 1; i >= 0; --i)
        inv[i] = (inv[i + 1] * (i + 1)) % mod;
}

int64 nCr(int64 n, int64 r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return (((fac[n] * inv[r]) % mod) * inv[n - r]) % mod;
}

// * @brief Z function for Strings
vector<int64> z_function(string s) {
    int64 n = s.size();
    vector<int64> z(n);
    int64 l = 0, r = 0;
    for (int64 i = 1; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// * @brief Sieve of Primes 
void SieveOfEratosthenes(int64 n) {
    vector<bool> prime(n + 1, true);
    for (int64 p = 2; p * p <= n; ++p) {
        if (prime[p]) {
            for (int64 i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    for (int64 p = 2; p <= n; ++p)
        if (prime[p]) sieve.pb(p);
}

// * @brief Seg Tree
struct SegmentTree {
    int64 n;
    vector<int64> tree;

    void init(int64 size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    void build(vector<int64>& a, int v, int tl, int tr) {
        if (tl == tr)
            tree[v] = a[tl];
        else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    int64 sum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return sum(v * 2, tl, tm, l, min(r, tm))
             + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int pos, int64 new_val) {
        if (tl == tr)
            tree[v] = new_val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }
};

// * @brief Disjoint Set Union
struct DSU {
    vector<int> parent, rank;

    void init(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }
};

// * @brief Main Working Logic here...
signed main() {
    six_eyes
    int n , x; cin >> n >> x;
    vi a(n); for(int l = 0;l < n;l++) cin >> a[l];

    vi dp(x+1 , inf); dp[0] = 0;
    for(int l(1); l <= x; l++){
        for(int i = 0; i < n; i++){
            if(l - a[i] >= 0){
                dp[l] = min(dp[l] , dp[l-a[i]] + 1);
            }
        }
    }
    if(dp[x] != inf) cout << dp[x];
    else c1;
    line;
}

//   /\_/\  
//  ( o.o )  CAT SEES YOUR BUGS
//   > ^ <
