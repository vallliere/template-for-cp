// you need a base flow class
// ex : dinic<flow_t>
template <typename flow_t>
struct circulation : base_flow_class {
    using flow = base_flow_class;

    circulation(int _sz) : flow(_sz + 2)
    {
        sz = _sz;
        dem_flow = 0;
        dem.resize(sz);
    }
    void add_edge(int u, int v, flow_t low, flow_t flw)
    {
        dem[u] += low, dem[v] -= low;
        flow::add_edge(u, v, flw - low);
    }
    void set_ST(int _s, int _t)
    {
        S = _s, T = _t;
        flow::add_edge(T, S, numeric_limits<flow_t>::max());
    }
    flow_t run()
    {
        flow::set_ST(sz, sz + 1);
        dem_flow = 0;
        for (int i = 0; i < sz; i++) {
            dem_flow += max(flow_t(0), dem[i]);
            if (dem[i] < 0)
                flow::add_edge(sz, i, -dem[i]);
            else if (dem[i] > 0)
                flow::add_edge(i, sz + 1, dem[i]);
        }
        return cur_flow = flow::complete_run();
    }
    bool check_circulation()
    {
        assert(cur_flow != -1);
        return dem_flow == cur_flow;
    }

   private:
    int sz, S, T;
    flow_t cur_flow, dem_flow;
    vector<flow_t> dem;
};
