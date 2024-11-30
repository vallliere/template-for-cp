struct biconnected_component {
    biconnected_component(int _N) : N(_N)
    {
        grp.resize(N);
        bcc.resize(N);
        dfn.resize(N);
    }
    void add_edge(int u, int v)
    {
        grp[u].push_back({v, int(edg.size())});
        grp[v].push_back({u, int(edg.size())});
        edg.push_back({u, v});
    }
    void init()
    {
        for (int i = 0; i < N; i++)
            if (dfn[i] == 0)
                dfs(i, -1);
        vector<bool> chk(N);
        vector<int> cnt(N);
        is_cut_v.resize(N), is_bridge.resize(edg.size());
        for (int i = 0; i < bcc.size(); i++) {
            if (bcc[i].size() == 1) {
                bridge.push_back(bcc[i][0]);
                is_bridge[bcc[i][0]] = 1;
            }
            for (auto id : bcc[i]) {
                auto [u, v] = edg[id];
                chk[u] = chk[v] = 1;
            }
            for (auto id : bcc[i]) {
                auto [u, v] = edg[id];
                if (chk[u] == 1)
                    chk[u] = 0, cnt[u]++;
                if (chk[v] == 1)
                    chk[v] = 0, cnt[v]++;
            }
        }
        for (int i = 0; i < N; i++)
            if (cnt[i] > 1) {
                cut_v.push_back(i);
                is_cut_v[i] = 1;
            }
    }

    int N;
    vector<bool> is_cut_v, is_bridge;
    vector<int> dfn, stk, cut_v, bridge;
    vector<array<int, 2>> edg;
    vector<vector<int>> bcc;
    vector<vector<array<int, 2>>> grp;

   private:
    int dfs(int lo, int be)
    {
        static int dn = 1;
        int ret;
        dfn[lo] = dn++;
        ret = dfn[lo];
        for (auto [ne, id] : grp[lo])
            if (ne != be) {
                if (dfn[ne] != 0)
                    ret = min(ret, dfn[ne]);
                else {
                    stk.push_back(id);
                    auto va = dfs(ne, lo);
                    ret = min(ret, va);
                    if (va >= dfn[lo]) {
                        bcc.push_back({});
                        do {
                            bcc.back().push_back(stk.back());
                            stk.pop_back();
                        } while (bcc.back().back() != id);
                    }
                }
            }
        return ret;
    }
};
