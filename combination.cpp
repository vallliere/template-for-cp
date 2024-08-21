struct combination {
    combination(ll _n, ll _md)
    {
        md = _md;
        fac.resize(2 * _n + 1);
        ifac.resize(2 * _n + 1);
        fac[0] = ifac[0] = 1;
        for (int i = 1; i < fac.size(); i++)
            fac[i] = fac[i - 1] * i % md;
        ifac.back() = power(fac.back(), md - 2, md);
        for (int i = ifac.size() - 2; i > 0; i--)
            ifac[i] = ifac[i + 1] * (i + 1) % md;
    }
    ll power(ll a, ll b, ll _md)
    {
        ll ret;
        ret = 1;
        while (b > 0) {
            if (b % 2 == 1)
                ret = ret * a % _md;
            a = a * a % _md;
            b /= 2;
        }
        return ret;
    }
    ll nCr(ll a, ll b)
    {
        ll ret;
        ret = fac[a];
        ret = ret * ifac[b] % md;
        ret = ret * ifac[a - b] % md;
        return ret;
    }
    ll nHr(ll a, ll b)
    {
        return nCr(a + b - 1, b);
    }
    ll factorial(ll a)
    {
        return fac[a];
    }
    ll inverse_factorial(ll a)
    {
        return ifac[a];
    }

   private:
    ll md;
    vector<ll> fac, ifac;
};
