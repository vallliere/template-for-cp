template <typename Cap, typename Cost>
struct potential_mcmf {
    struct node {
        int ne;
        Cap cp;
        Cost dt;
        int inv;
    };
    potential_mcmf(int _sz, int _st, int _en)
    {
        sz = _sz, st = _st, en = _en;
        grp.resize(sz);
        ptl.resize(sz);
    }
    void add_edge(int x, int y, Cap cp, Cost dt)
    {
        grp[x].push_back({y, cp, dt, int(grp[y].size())});
        grp[y].push_back({x, 0, -dt, int(grp[x].size()) - 1});
    }
    void spfa()
    {
        fill(ptl.begin(), ptl.end(), numeric_limits<Cost>::max());
        vector<bool> inn(sz);
        queue<int> que;
        que.push(st);
        inn[st] = 1;
        ptl[st] = 0;
        while (que.size() > 0) {
            auto lo = que.front();
            que.pop();
            inn[lo] = 0;
            for (auto &ne : grp[lo])
                if (ne.cp > 0 && ptl[ne.ne] > ptl[lo] + ne.dt) {
                    ptl[ne.ne] = ptl[lo] + ne.dt;
                    if (inn[ne.ne] == 0) {
                        que.push(ne.ne);
                        inn[ne.ne] = 1;
                    }
                }
        }
    }
    pair<Cap, Cost> calculate()
    {
        pair<Cap, Cost> ret = {0, 0};
        vector<node *> edg(sz);
        vector<bool> vis(sz);
        vector<Cap> flw(sz);
        vector<Cost> dst(sz, numeric_limits<Cost>::max());
        for (;;) {
            priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<>> pq;
            pq.push({0, st});
            dst[st] = 0;
            flw[st] = numeric_limits<Cap>::max();
            while (pq.size() > 0) {
                auto [dt, lo] = pq.top();
                pq.pop();
                if (vis[lo] == 1)
                    continue;
                vis[lo] = 1;
                for (auto &ne : grp[lo]) {
                    if (vis[ne.ne] == 0 && ne.cp > 0 && dst[ne.ne] > dt + ne.dt + ptl[lo] - ptl[ne.ne]) {
                        dst[ne.ne] = dt + ne.dt + ptl[lo] - ptl[ne.ne];
                        pq.push({dst[ne.ne], ne.ne});
                        flw[ne.ne] = min(flw[lo], ne.cp);
                        edg[ne.ne] = &ne;
                    }
                }
            }
            if (vis[en] == 0)
                break;
            for (int i = 0; i < sz; i++)
                if (vis[i] == 1) {
                    // dst[i] -= ptl[st] - ptl[i];
                    // ptl[i] = dst[i];
                    ptl[i] += dst[i];
                    vis[i] = 0;
                    dst[i] = numeric_limits<Cost>::max();
                }
            Cap va = flw[en];
            ret.first += va;
            ret.second += ptl[en] * va;
            int lo = en;
            while (lo != st) {
                auto ne = edg[lo];
                ne->cp -= va;
                grp[ne->ne][ne->inv].cp += va;
                lo = grp[ne->ne][ne->inv].ne;
            }
        }
        return ret;
    }

   private:
    int sz, st, en;
    vector<Cost> ptl;
    vector<vector<node>> grp;
};
