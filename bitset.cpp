struct dynamic_bitset {
    typedef unsigned long long ull;
    dynamic_bitset(int n)
    {
        assert(n > 0);
        sz = n;
        bit_s.resize((sz - 1) / 64 + 1);
        max_64 = (1ull << 63) | ((1ull << 63) - 1ull);
        del_carry = max_64 >> (64 - sz % 64) % 64;
    }
    void set(int lo = -1)
    {
        assert(lo < sz);
        if (lo == -1) {
            fill(bit_s.begin(), bit_s.end(), max_64);
            bit_s.back() &= del_carry;
        }
        else
            bit_s[lo / 64] |= 1ull << (lo % 64);
    }
    void reset(int lo = -1)
    {
        assert(lo < sz);
        if (lo == -1)
            fill(bit_s.begin(), bit_s.end(), 0ull);
        else
            bit_s[lo / 64] &= ~(1ull << (lo % 64));
    }
    void flip(int lo)
    {
        assert(lo < sz);
        bit_s[lo / 64] ^= 1ull << (lo % 64);
    }
    int size()
    {
        return sz;
    }
    int count()
    {
        int i, cnt;
        cnt = 0;
        for (i = 0; i < bit_s.size(); i++)
            cnt += __builtin_popcount(bit_s[i]);
        return cnt;
    }
    void print()
    {
        int i, p;
        string str;
        for (i = sz % 64; i >= 0; i--)
            str.push_back('0' + ((bit_s.back() >> i) & 1ull));
        for (i = bit_s.size() - 2; i >= 0; i--)
            for (p = 63; p >= 0; p--)
                str.push_back('0' + ((bit_s[i] >> p) & 1ull));
        cout << str << "\n";
    }
    bool all_bit()
    {
        int i;
        if (bit_s.back() != del_carry)
            return false;
        for (i = 0; i < bit_s.size() - 1; i++)
            if (bit_s[i] != max_64)
                return false;
        return true;
    }
    bool any_bit()
    {
        int i;
        for (i = 0; i < bit_s.size(); i++)
            if (bit_s[i] != 0)
                return true;
        return false;
    }
    bool none_bit()
    {
        int i;
        for (i = 0; i < bit_s.size(); i++)
            if (bit_s[i] != 0)
                return false;
        return true;
    }
    bool operator[](const int& va)
    {
        assert(va < sz);
        return (bit_s[va / 64] >> (va % 64)) != 0ull;
    }
    dynamic_bitset operator<<(const int& va)
    {
        dynamic_bitset ret(sz);
        ret.bit_s = bit_s;
        ret.left(va);
        return ret;
    }
    dynamic_bitset& operator<<=(const int& va)
    {
        this->left(va);
        return *this;
    }
    dynamic_bitset operator>>(const int& va)
    {
        dynamic_bitset ret(sz);
        ret.bit_s = bit_s;
        ret.right(va);
        return ret;
    }
    dynamic_bitset& operator>>=(const int& va)
    {
        this->right(va);
        return *this;
    }
    dynamic_bitset operator|(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        dynamic_bitset ret = va;
        for (i = 0; i < bit_s.size(); i++)
            ret.bit_s[i] |= bit_s[i];
        return ret;
    }
    dynamic_bitset& operator|=(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        for (i = 0; i < bit_s.size(); i++)
            this->bit_s[i] |= va.bit_s[i];
        return *this;
    }
    dynamic_bitset operator&(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        dynamic_bitset ret = va;
        for (i = 0; i < bit_s.size(); i++)
            ret.bit_s[i] &= bit_s[i];
        return ret;
    }
    dynamic_bitset& operator&=(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        for (i = 0; i < bit_s.size(); i++)
            this->bit_s[i] &= va.bit_s[i];
        return *this;
    }
    dynamic_bitset operator^(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        dynamic_bitset ret = va;
        for (i = 0; i < bit_s.size(); i++)
            ret.bit_s[i] ^= bit_s[i];
        return ret;
    }
    dynamic_bitset& operator^=(const dynamic_bitset& va)
    {
        int i;
        assert(va.sz == sz);
        for (i = 0; i < bit_s.size(); i++)
            this->bit_s[i] ^= va.bit_s[i];
        return *this;
    }

   private:
    int sz;
    ull del_carry, max_64;
    vector<ull> bit_s;
    void left(int va)
    {
        int i, n;
        ull cr, next_cr;
        n = min(int(bit_s.size()), va / 64);
        if (n > 0)
            for (i = bit_s.size() - 1; i >= 0; i--)
                if (i - n >= 0)
                    bit_s[i] = bit_s[i - n];
                else
                    bit_s[i] = 0;
        n = va % 64, cr = 0;
        if (n > 0)
            for (i = 0; i < bit_s.size(); i++) {
                next_cr = bit_s[i] >> (64 - n);
                bit_s[i] = (bit_s[i] << n) | cr;
                cr = next_cr;
            }
        bit_s.back() &= del_carry;
    }
    void right(int va)
    {
        int i, n;
        ull cr, next_cr;
        n = min(int(bit_s.size()), va / 64);
        if (n > 0)
            for (i = 0; i < bit_s.size(); i++)
                if (i + n < bit_s.size())
                    bit_s[i] = bit_s[i + n];
                else
                    bit_s[i] = 0;
        n = va % 64, cr = 0;
        if (n > 0)
            for (i = bit_s.size() - 1; i >= 0; i--) {
                next_cr = bit_s[i] << (64 - n);
                bit_s[i] = (bit_s[i] >> n) | cr;
                cr = next_cr;
            }
    }
};
