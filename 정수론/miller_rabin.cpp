struct miller_rabin {
    miller_rabin(vector<long long> _pri = vector<long long>({2, 3, 61}))
    {
        pri = _pri;
    }
    bool check(long long va)
    {
        for (auto ne : pri)
            if (va == ne)
                return 1;
        if (va == 1 || va % 2 == 0)
            return 0;
        for (auto ne : pri)
            if (calculate(va, ne) == 0)
                return 0;
        return 1;
    }

   private:
    vector<long long> pri;
    bool calculate(long long va, long long pi)
    {
        long long n, m;
        n = va - 1;
        while (n % 2 == 0)
            n /= 2;
        m = power(pi, n, va);
        if (m == 1 || m == va - 1)
            return 1;
        while (n != va - 1) {
            m = m * m % va;
            n *= 2;
            if (m == 1)
                return 0;
            if (m == va - 1)
                return 1;
        }
        return 0;
    }
    long long power(long long va, long long pw, long long md)
    {
        long long ret;
        ret = 1;
        while (pw > 0) {
            if (pw % 2 == 1)
                ret = ret * va % md;
            va = va * va % md;
            pw /= 2;
        }
        return ret;
    }
};
