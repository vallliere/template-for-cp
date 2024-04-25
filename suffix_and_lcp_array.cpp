struct suffix_lcp {
    suffix_lcp(string _str)
    {
        str = _str;
        n = str.length();
        count.resize(n + 1);
        temp.resize(n);
        _get_suffix_array();
        _get_lcp_array();
    }
    vector<int> get_suffix_array() { return suffix_arr; }
    vector<int> get_lcp_array() { return lcp_arr; }

   private:
    int n;
    string str;
    vector<int> suffix_arr, suffix_rank, lcp_arr, count, temp;
    int cal_rank(int loc, int len, int cmp_loc = -1)
    {
        if (cmp_loc != -1)  // compare loc's rank and cmp_loc's rank
            return suffix_rank[min(n, loc + len)] == suffix_rank[min(n, cmp_loc + len)];
        return suffix_rank[min(n, loc + len)];
    }
    void counting_sort(int len)
    {
        int count_sum, count_temp;
        for (int i = 0; i <= n; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[cal_rank(i, len)]++;
        for (int i = 1; i <= n; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            temp[--count[cal_rank(suffix_arr[i], len)]] = suffix_arr[i];
        for (int i = 0; i < n; i++)
            suffix_arr[i] = temp[i];
    }
    void _get_suffix_array()
    {
        suffix_arr.resize(n);
        suffix_rank.resize(n + 1);
        set<char> char_check(all(str));
        map<char, int> char_rank;
        auto it = char_check.begin();
        for (int i = 1; it != char_check.end(); it++, i++)
            char_rank[*it] = i;
        for (int i = 0; i < n; i++)
            suffix_arr[i] = i, suffix_rank[i] = char_rank[str[i]];
        for (int len = 1; len < n; len *= 2) {
            counting_sort(len), counting_sort(0);
            temp[suffix_arr[0]] = 1;
            for (int i = 1; i < n; i++)
                if (cal_rank(suffix_arr[i], 0, suffix_arr[i - 1]) == 1 && cal_rank(suffix_arr[i], len, suffix_arr[i - 1]))
                    temp[suffix_arr[i]] = temp[suffix_arr[i - 1]];
                else
                    temp[suffix_arr[i]] = temp[suffix_arr[i - 1]] + 1;
            for (int i = 0; i < n; i++)
                suffix_rank[i] = temp[i];
            if (suffix_rank[suffix_arr[n - 1]] == n)
                break;
        }
    }
    void _get_lcp_array()
    {
        int len;
        lcp_arr.resize(n);
        vector<int> inv_index(n);
        for (int i = 0; i < n; i++)
            inv_index[suffix_arr[i]] = i;
        len = 0;
        for (int i = 0; i < n; i++)
            if (inv_index[i] > 0) {
                while (min(i, suffix_arr[inv_index[i] - 1]) + len < n && str[i + len] == str[suffix_arr[inv_index[i] - 1] + len])
                    len++;
                lcp_arr[inv_index[i]] = len;
                len = max(0, len - 1);
            }
    }
};
