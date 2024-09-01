class fhstring {
private:
    vector<vector<ll>> dp;
    vector<vector<ll>> inv;
    ll n;
    vector<ll> bases;
    vector<ll> mods;
 
public:
    fhstring(const string& s, const vector<ll>& bases, const vector<ll>& mods)
        : bases(bases), mods(mods) {
        n = s.size();
        ll num_bases = bases.size();
        dp.resize(num_bases, vector<ll>(n));
        inv.resize(num_bases, vector<ll>(n));
 
        vector<vector<ll>> p_pow(num_bases, vector<ll>(n, 1));
 
        for (ll k = 0; k < num_bases; ++k) {
            inv[k][0] = 1;
            dp[k][0] = (s[0] - '0' + 1);
        }
 
        for (ll j = 1; j < n; ++j) {
            char c = s[j];
            for (ll k = 0; k < num_bases; ++k) {
                p_pow[k][j] = (p_pow[k][j - 1] * bases[k]) % mods[k];
                inv[k][j] = binPow(p_pow[k][j], mods[k] - 2, mods[k]);
                dp[k][j] = (dp[k][j - 1] + (c - '0' + 1) * p_pow[k][j]) % mods[k];
            }
        }
    }
 
    static ll binPow(ll a, ll b, ll mod) {
        ll res = 1;
        while (b > 0) {
            if (b & 1)
                res = (res * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return res;
    }
 
    vector<ll> substrhash(ll L, ll R) {
        if (R < L) return vector<ll>(bases.size(), 0);
        int num_bases = bases.size();
        vector<ll> res(num_bases);
        for (ll k = 0; k < num_bases; ++k) {
            res[k] = dp[k][R];
            if (L > 0) {
                res[k] = (res[k] - dp[k][L - 1] + mods[k]) % mods[k];
                res[k] = (res[k] * inv[k][L]) % mods[k];
            }
        }
        return res;
    }
};
 
ll power(ll a, ll b, ll m = mod) {
    if (a == 0) return 0LL;
    if (b == 0) return 1LL;
    ll result;
    if (b % 2) {
        result = a * 1LL * power(a, b - 1, m);
    } else {
        ll half = power(a, b / 2, m);
        result = half * 1LL * half;
    }
    return result % m;
}
 
vector<ll> b;
vector<ll> m;
 
void setRandomBases(ll n) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 rng(seed);
    uniform_int_distribution<ll> base_distribution(31, 100000);
 
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        b[i] = base_distribution(rng);
    }
}
// put these two lines inside main function
// setRandomBases(2);
// m={mod,mod+2};
