struct hopcroft_karp {
    hopcroft_karp(int _sz, int _isz)
    {
        sz = _sz, isz = _isz;
        grp.resize(sz);
        que.resize(sz);
        index_u.resize(sz, -1), index_v.resize(isz, -1);
        dsj_set.resize(sz);
        prev_u.resize(sz);
    }
    void add_edge(int u, int v)
    {
        grp[u].push_back(v);
    }
    int match_index_u(int lo)
    {
        return index_u[lo];
    }
    int match_index_v(int lo)
    {
        return index_v[lo];
    }
    int matching()
    {
        int u, loc, flow, cur_flow, q_begin, q_end;
        flow = 0;
        vector<pii> linked_list(sz + 2);
        linked_list[0].first = sz, linked_list[sz - 1].second = sz + 1;
        linked_list[sz].second = 0, linked_list[sz + 1].first = sz - 1;
        for (int i = 0; i < sz - 1; i++)
            linked_list[i].second = i + 1;
        for (int i = 1; i < sz; i++)
            linked_list[i].first = i - 1;
        vector<int> last_rep(sz);
        for (int rep = 1;; rep++) {
            cur_flow = 0;
            q_begin = 0, q_end = 0;
            loc = linked_list[sz].second;
            while (loc < sz + 1) {
                if (index_u[loc] == -1) {
                    que[q_end++] = dsj_set[loc] = prev_u[loc] = loc;
                    last_rep[loc] = rep;
                }
                loc = linked_list[loc].second;
            }
            while (q_begin < q_end) {
                u = que[q_begin++];
                if (index_u[dsj_set[u]] != -1)
                    continue;
                for (auto v : grp[u]) {
                    if (index_v[v] == -1) {
                        while (v != -1) {
                            index_v[v] = u;
                            swap(index_u[u], v);
                            u = prev_u[u];
                            /*
                            Before : {u} <-> {index_u[u]}
                            After : {u} <-> {v}
                            Update since index_u[u] matching is missing : {v} to {u} and {u} to previous vertex {prev_u[u]}
                            */
                        }
                        linked_list[linked_list[u].first].second = linked_list[u].second;
                        linked_list[linked_list[u].second].first = linked_list[u].first;
                        cur_flow++;
                        break;
                    }
                    if (last_rep[index_v[v]] < rep) {
                        que[q_end++] = index_v[v];
                        prev_u[index_v[v]] = u, dsj_set[index_v[v]] = dsj_set[u];
                        last_rep[index_v[v]] = rep;
                    }
                }
            }
            if (cur_flow == 0)
                break;
            flow += cur_flow;
        }
        return flow;
    }

   private:
    int sz, isz;
    vector<int> que, index_u, index_v, dsj_set, prev_u;
    vector<vector<int>> grp;
};
