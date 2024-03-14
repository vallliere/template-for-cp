template <typename T>
struct dinic {
    struct node {
        int ne;
        T flw, cap;
        int rev;
    };
    dinic(int st, int en, int sz)
    {
        st_lo = st, en_lo = en;
        now_idx.resize(sz + 1);
        level.resize(sz + 1);
        grp.assign(sz + 1, {});
        max_num = numeric_limits<T>::max();
    }
    void push(int st, int en, T cp)
    {
        if (cp < 0)
            cp = max_num;
        grp[st].push_back({en, 0, cp, int(grp[en].size())});
        grp[en].push_back({st, 0, 0, int(grp[st].size()) - 1});
    }
    T dfs(int lo, T fl)
    {
        T ret;
        if (lo == en_lo)
            return fl;
        while (now_idx[lo] < grp[lo].size()) {
            auto& it = grp[lo][now_idx[lo]];
            if (level[it.ne] == level[lo] + 1 && it.cap > it.flw) {
                ret = dfs(it.ne, min(fl, it.cap - it.flw));
                if (ret > 0) {
                    it.flw += ret;
                    grp[it.ne][it.rev].flw -= ret;
                    return ret;
                }
            }
            now_idx[lo]++;
        }
        return 0;
    }
    T action()
    {
        int lo;
        T n, ret;
        fill(all(now_idx), 0);
        fill(all(level), -1);
        queue<int> que;
        que.push(st_lo);
        level[st_lo] = 1;
        while (que.empty() == 0) {
            lo = que.front();
            que.pop();
            for (auto& ne : grp[lo])
                if (level[ne.ne] == -1 && ne.cap > ne.flw) {
                    que.push(ne.ne);
                    level[ne.ne] = level[lo] + 1;
                }
        }
        if (level[en_lo] == -1)
            return -1;
        ret = 0;
        for (;;) {
            n = dfs(st_lo, max_num);
            if (n == 0)
                break;
            ret += n;
        }
        return ret;
    }

   private:
    int st_lo, en_lo;
    T max_num;
    vector<int> now_idx, level;
    vector<vector<node>> grp;
};
