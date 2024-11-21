// https://github.com/justiceHui/icpc-teamnote/blob/master/code/Graph/DominatorTree.cpp
vector<int> dominator_tree(const vector<vector<int>> &bse_grp, int st)
{  // 0-based
    int n;
    n = bse_grp.size();
    vector<vector<int>> rev_bse_grp(n), buf(n);
    vector<int> ra(n), val(n), idom(n, -1), sdom(n, -1), tem, par(n), uni(n);
    iota(all(ra), 0);
    iota(all(val), 0);
    for (int i = 0; i < n; i++)
        for (auto ne : bse_grp[i])
            rev_bse_grp[ne].push_back(i);
    function<int(int)> find = [&](int lo) {
        if (lo == ra[lo])
            return lo;
        int ret = find(ra[lo]);
        if (sdom[val[lo]] > sdom[val[ra[lo]]])
            val[lo] = val[ra[lo]];
        return ra[lo] = ret;
    };
    function<void(int)> dfs = [&](int lo) {
        sdom[lo] = tem.size();
        tem.push_back(lo);
        for (auto ne : bse_grp[lo])
            if (sdom[ne] == -1)
                par[ne] = lo, dfs(ne);
    };
    dfs(st);
    reverse(all(tem));
    for (auto &ne : tem) {
        if (sdom[ne] == -1)
            continue;
        for (auto nd : rev_bse_grp[ne]) {
            if (sdom[nd] == -1)
                continue;
            int x = val[find(nd), nd];
            if (sdom[ne] > sdom[x])
                sdom[ne] = sdom[x];
        }
        buf[tem[tem.size() - sdom[ne] - 1]].push_back(ne);
        for (auto nd : buf[par[ne]])
            uni[nd] = val[find(nd), nd];
        buf[par[ne]].clear();
        ra[ne] = par[ne];
    }
    reverse(all(tem));
    idom[st] = st;
    for (auto ne : tem)  // WARNING : if different, takes idom
        if (ne != st)
            idom[ne] = sdom[ne] == sdom[uni[ne]] ? sdom[ne] : idom[uni[ne]];
    for (auto ne : tem)
        if (ne != st)
            idom[ne] = tem[idom[ne]];
    return idom;  // unreachable -> ret[i] = -1
}
