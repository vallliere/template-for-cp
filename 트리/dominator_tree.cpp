struct dominator_tree {
    vector<vector<int>> g, rg, bucket;
    vector<int> arr, par, rev, sdom, dom, dsu, label;
    int N, T;
    dominator_tree(int n) : g(n), rg(n), bucket(n), arr(n, -1), par(n, -1), rev(n, -1), sdom(n, -1), dom(n, -1), dsu(n, 0), label(n, 0), N(n), T(0) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    void dfs(int u)
    {
        arr[u] = T, rev[T] = u, label[T] = sdom[T] = dsu[T] = T;
        T++;
        for (int w : g[u]) {
            if (arr[w] == -1)
                dfs(w), par[arr[w]] = arr[u];
            rg[arr[w]].push_back(arr[u]);
        }
    }
    int find(int u, int x = 0)
    {
        if (u == dsu[u])
            return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0)
            return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    vector<int> run(int root)
    {
        dfs(root);
        iota(dom.begin(), dom.end(), 0);
        for (int i = T - 1; i >= 0; --i) {
            for (int ne : rg[i])
                sdom[i] = min(sdom[i], sdom[find(ne)]);
            if (i > 0)
                bucket[sdom[i]].push_back(i);
            for (int ne : bucket[i]) {
                int v = find(ne);
                if (sdom[v] == sdom[ne])
                    dom[ne] = sdom[ne];
                else
                    dom[ne] = v;
            }
            if (i > 1)
                dsu[i] = par[i];
        }
        for (int i = 1; i < T; i++)
            if (dom[i] != sdom[i])
                dom[i] = dom[dom[i]];
        vector<int> outside_dom(N, -1);
        for (int i = 1; i < T; i++)
            outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};
