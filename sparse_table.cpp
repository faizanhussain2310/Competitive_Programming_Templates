class sparsetable {
public:
    ll combine(ll l,ll r){
        return l&r;
    }
    sparsetable(const vector<ll>& arr) {
        n = arr.size();
        k = log2(n) + 1;
        st = vector<vector<ll>>(n, vector<ll>(k));
        build(arr);
    }
    ll query(ll L, ll R) {
        ll j = log2(R - L + 1);
        return combine(st[L][j], st[R - (1 << j) + 1][j]);
    }
private:
    ll n, k;
    vector<vector<ll>> st;
    void build(const vector<ll>& arr) {
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                st[i][j] = combine(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
};
