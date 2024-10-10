template <typename Cap, typename Cost>
struct zkw_mcmf {
    struct node {
        int ne;
        Cap cp;
        Cost dt;
        int inv;
    };
    zkw_mcmf(int _sz, int _st, int _en)
    {
        sz = _sz, st = _st, en = _en;
        grp.resize(sz);
        idx = new int[sz + 1];
        vis = new bool[sz + 1];
        dst.resize(sz);
    }
    void add_edge(int x, int y, Cap cp, Cost dt)
    {
        grp[x].push_back({y, cp, dt, int(grp[y].size())});
        grp[y].push_back({x, 0, -dt, int(grp[x].size()) - 1});
    }
    void spfa()
    {
        fill(dst.begin(), dst.end(), numeric_limits<Cost>::max());
        vector<bool> inn(sz);
        queue<int> que;
        que.push(st);
        inn[st] = 1;
        dst[st] = 0;
        while (que.size() > 0) {
            auto lo = que.front();
            que.pop();
            inn[lo] = 0;
            for (auto &ne : grp[lo])
                if (ne.cp > 0 && dst[ne.ne] > dst[lo] + ne.dt) {
                    dst[ne.ne] = dst[lo] + ne.dt;
                    if (inn[ne.ne] == 0) {
                        que.push(ne.ne);
                        inn[ne.ne] = 1;
                    }
                }
        }
    }
    pair<Cap, Cost> calculate()
    {
        Cap va;
        pair<Cap, Cost> ret = {0, 0};
        for (;;) {
            memset(idx, 0, sizeof(int) * sz);
            for (;;) {
                memset(vis, 0, sizeof(bool) * sz);
                va = dfs(st, numeric_limits<Cap>::max());
                if (va == 0)
                    break;
                ret.first += va;
                ret.second += va * dst[en];
            }
            if (update() == 0)
                break;
        }
        return ret;
    }

   private:
    int sz, st, en;
    int *idx;
    bool *vis;
    vector<Cost> dst;
    vector<vector<node>> grp;
    Cap dfs(int lo, Cap flw)
    {
        Cap va;
        vis[lo] = 1;
        if (lo == en)
            return flw;
        for (; idx[lo] < grp[lo].size(); idx[lo]++) {
            auto &ne = grp[lo][idx[lo]];
            if (vis[ne.ne] == 0 && ne.cp > 0 && dst[ne.ne] == dst[lo] + ne.dt) {
                va = dfs(ne.ne, min(flw, ne.cp));
                if (va > 0) {
                    ne.cp -= va;
                    grp[ne.ne][ne.inv].cp += va;
                    return va;
                }
            }
        }
        return 0;
    }
    bool update()
    {
        Cost va;
        va = numeric_limits<Cost>::max();
        for (int i = 0; i < sz; i++)
            if (vis[i] == 1)
                for (auto &ne : grp[i])
                    if (ne.cp > 0 && vis[ne.ne] == 0)
                        va = min(va, dst[i] + ne.dt - dst[ne.ne]);
        if (va == numeric_limits<Cost>::max())
            return 0;
        for (int i = 0; i < sz; i++)
            if (vis[i] == 0)
                dst[i] += va;
        return 1;
    }
};
