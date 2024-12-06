// need biconnected_component
struct block_cut_tree : public biconnected_component {
    block_cut_tree(int _N) : biconnected_component(_N), N(_N), BN(-1) {}
    void add_edge(int u, int v) { biconnected_component::add_edge(u, v); }
    void init()
    {
        biconnected_component::init();
        BN = biconnected_component::bcc.size();
        blk.resize(BN);
        cut.resize(N);
        vector<bool> chk_cut(N);
        for (int i = 0; i < BN; i++) {
            for (auto id : biconnected_component::bcc[i]) {
                auto [u, v] = biconnected_component::edg[id];
                if (biconnected_component::is_cut_v[u])
                    chk_cut[u] = 1;
                if (biconnected_component::is_cut_v[v])
                    chk_cut[v] = 1;
            }
            for (auto id : biconnected_component::bcc[i]) {
                auto [u, v] = biconnected_component::edg[id];
                if (chk_cut[u])
                    chk_cut[u] = 0, cut[u].push_back(i), blk[i].push_back(u);
                if (chk_cut[v])
                    chk_cut[v] = 0, cut[v].push_back(i), blk[i].push_back(v);
            }
        }
    }

    int BN, N;
    vector<vector<int>> blk, cut;
};
