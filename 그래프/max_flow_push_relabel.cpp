template <typename flow_t>
struct push_relabel {
    struct edge {
        int v, rev;
        flow_t flw;
        edge(int _v, flow_t _f, int _rev) : v(_v), flw(_f), rev(_rev) {}
    };
    push_relabel(int _N)
    {
        N = _N;
        S = T = -1;
        grp.resize(N);
        stk.resize(N * 2);
    }
    void add_edge(int u, int v, flow_t flow)
    {
        assert(flow >= 0);
        assert(u >= 0 && u < N && v >= 0 && v < N);
        assert(u != v);
        grp[u].push_back({v, flow, int(grp[v].size())});
        grp[v].push_back({u, 0, int(grp[u].size()) - 1});
    }
    void set_ST(int _S, int _T)
    {
        S = _S, T = _T;
    }
    void add_flow(edge &lo, flow_t va)
    {
        if (ex[lo.v] == 0 && va > 0)
            stk[hei[lo.v]].push_back(lo.v);
        lo.flw -= va;
        grp[lo.v][lo.rev].flw += va;
        ex[grp[lo.v][lo.rev].v] -= va;
        ex[lo.v] += va;
    }

    // max flow
    flow_t max_flow()
    {
        int u, hi;
        assert(S != -1 && T != -1);
        ex.assign(N, 0);
        idx.assign(N, 0);
        hei.assign(N, 0);
        hei[S] = N;
        ex[T] = 1;
        vector<int> cnt(N * 2);
        cnt[0] = N - 1;
        for (auto &ne : grp[S])
            add_flow(ne, ne.flw);
        if (stk[0].size() > 0) {
            hi = 0;
            while (hi >= 0) {
                u = stk[hi].back();
                stk[hi].pop_back();
                while (ex[u] > 0) {  // discharge u
                    if (idx[u] == grp[u].size()) {
                        hei[u] = 3 * N;
                        for (int i = 0; i < grp[u].size(); i++) {  // relabel
                            auto &lo = grp[u][i];
                            if (lo.flw > 0 && hei[u] > hei[lo.v] + 1)
                                hei[u] = hei[lo.v] + 1, idx[u] = i;
                        }
                        cnt[hei[u]]++, cnt[hi]--;
                        if (cnt[hi] == 0 && hi < N)  // gap heuristic
                            for (int i = 0; i < N; ++i)
                                if (hei[i] > hi && hei[i] < N) {
                                    cnt[hei[i]]--;
                                    hei[i] = N + 1;
                                }
                        hi = hei[u];
                    }
                    else if (grp[u][idx[u]].flw > 0 && hei[u] == hei[grp[u][idx[u]].v] + 1)  // push
                        add_flow(grp[u][idx[u]], min(ex[u], grp[u][idx[u]].flw));
                    else
                        idx[u]++;
                }
                while (hi >= 0 && stk[hi].size() == 0)
                    hi--;
            }
        }
        return -ex[S];
    }

   private:
    int N, S, T;
    vector<vector<edge>> grp;

    vector<int> idx, hei;
    vector<vector<int>> stk;
    vector<flow_t> ex;
};
