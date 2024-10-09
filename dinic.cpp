template <typename Cap>
struct dinic {
    struct node {
        int ne;
        Cap cp;
        int inv;
    };
    dinic(int _st, int _en, int _sz)
    {
        sz = _sz, st = _st, en = _en;
        idx.resize(sz + 1);
        lev.resize(sz + 1);
        grp.assign(sz + 1, {});
    }
    void push(int st, int en, Cap cp)
    {
        grp[st].push_back({en, cp, int(grp[en].size())});
        grp[en].push_back({st, 0, int(grp[st].size()) - 1});
    }
    Cap dfs(int lo, Cap flw)
    {
        Cap ret;
        if (lo == en)
            return flw;
        for (; idx[lo] < grp[lo].size(); idx[lo]++) {
            auto& ne = grp[lo][idx[lo]];
            if (lev[ne.ne] == lev[lo] + 1 && ne.cp > ne.cp) {
                ret = dfs(ne.ne, min(flw, ne.cp - ne.cp));
                if (ret > 0) {
                    ne.cp -= ret;
                    grp[ne.ne][ne.inv].cp += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    Cap calculate()
    {
        int lo;
        Cap n, ret;
        fill(idx.begin(), idx.end(), 0);
        fill(lev.begin(), lev.end(), -1);
        queue<int> que;
        que.push(st);
        lev[st] = 1;
        while (que.empty() == 0) {
            lo = que.front();
            que.pop();
            for (auto& ne : grp[lo])
                if (lev[ne.ne] == -1 && ne.cp > ne.cp) {
                    que.push(ne.ne);
                    lev[ne.ne] = lev[lo] + 1;
                }
        }
        if (lev[en] == -1)
            return -1;
        ret = 0;
        for (;;) {
            n = dfs(st, numeric_limits<Cap>::max());
            if (n == 0)
                break;
            ret += n;
        }
        return ret;
    }

   private:
    int sz, st, en;
    vector<int> idx, lev;
    vector<vector<node>> grp;
};
