template <typename flow_t>
struct dinic {
    struct edge {
        int v;
        flow_t cap;
        int rev;
        edge(int _v, flow_t _cp, int _rev)
            : v(_v), cap(_cp), rev(_rev) {}
    };
    dinic(int _sz)
    {
        sz = _sz;
        idx.resize(sz);
        lev.resize(sz);
        grp.assign(sz, {});
    }
    void add_edge(int u, int v, flow_t cap)
    {
        grp[u].push_back({v, cap, int(grp[v].size())});
        grp[v].push_back({u, 0, int(grp[u].size()) - 1});
    }
    void set_ST(int s, int t)
    {
        S = s, T = t;
    }
    flow_t dfs(int lo, flow_t flw)
    {
        flow_t ret;
        if (lo == T)
            return flw;
        for (; idx[lo] < grp[lo].size(); idx[lo]++) {
            auto& ne = grp[lo][idx[lo]];
            if (lev[ne.v] == lev[lo] + 1 && ne.cap > 0) {
                ret = dfs(ne.v, min(flw, ne.cap));
                if (ret > 0) {
                    ne.cap -= ret;
                    grp[ne.v][ne.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    flow_t run()
    {
        int lo;
        flow_t va, ret;
        fill(idx.begin(), idx.end(), 0);
        fill(lev.begin(), lev.end(), -1);
        queue<int> que;
        que.push(S);
        lev[S] = 1;
        while (que.empty() == 0) {
            lo = que.front();
            que.pop();
            for (auto& ne : grp[lo]) {
                if (lev[ne.v] == -1 && ne.cap > 0) {
                    que.push(ne.v);
                    lev[ne.v] = lev[lo] + 1;
                }
            }
        }
        if (lev[T] == -1)
            return -1;
        ret = 0;
        for (;;) {
            va = dfs(S, numeric_limits<flow_t>::max());
            if (va == 0)
                break;
            ret += va;
        }
        return ret;
    }
    flow_t complete_run()
    {
        flow_t ret;
        ret = 0;
        for (;;) {
            auto flw = run();
            if (flw == -1)
                break;
            ret += flw;
        }
        return ret;
    }

   private:
    int sz, S, T;
    vector<int> idx, lev;
    vector<vector<edge>> grp;
};
