struct Tree {
    ll n, LOG, timer;
    vector<ll> tin, tout, depth, flat, par;
    vector<vector<ll>> adj, up;
 
    Tree(ll n) {
        this->n = n;
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        par.resize(n);
        flat.resize(2 * n);
        timer = 0;
        adj.resize(n);
        LOG = ceil(log2(n));
        up.assign(n, vector<ll>(LOG + 1));
    }
 
    void add_edge(ll a, ll b) {
        assert(0 <= a and a < n);
        assert(0 <= b and b < n);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
 
    void build(ll root) {
        depth[root] = 0;
        dfs(root, -1);
    }
 
    void dfs(ll v, ll p) {
        par[v] = p;
        flat[timer] = v;
        tin[v] = timer++;
        if (p != -1) depth[v] = depth[p] + 1;
        up[v][0] = (p == -1 ? v : p);
        for (int i = 1; i <= LOG; ++i) up[v][i] = up[up[v][i - 1]][i - 1];
        for (auto& u : adj[v])
            if (u != p) dfs(u, v);
        flat[timer] = v;
        tout[v] = timer++;
    }
 
    bool is_ancestor(ll u, ll v) { 
        return tin[u] <= tin[v] && tout[u] >= tout[v]; 
    }
 
    ll lca(ll u, ll v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = LOG; i >= 0; i--)
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        return up[u][0];
    }
 
    ll dist(ll u, ll v) { 
        return depth[u] + depth[v] - 2 * depth[lca(u, v)]; 
    }
 
    ll kth_node(ll u, ll v, ll k) {
        ll l = lca(u, v), d = depth[v] + depth[u] - 2 * depth[l];
        // assert(0 <= k and k <= d);
        ll dul = depth[u] - depth[l];
        if (k <= dul) {
            ll ans = u;
            for (int i = 0; i <= LOG; i++)
                if (k & (1 << i)) ans = up[ans][i];
            return ans;
        }
        ll dvl = depth[v] - depth[l], dd = dvl - (k - dul), ans = v;
        for (ll i = 0; i <= LOG; i++)
            if (dd & (1 << i)) ans = up[ans][i];
        return ans;
    }
 
    ll kth_ancestor(ll u, ll k, ll root = 0) { 
        return kth_node(u, root, k); 
    }
};
