struct binary_string {  // 12 : front(0) - 1010 - end(|N| - 1)
    binary_string() : N(list<char>{'0'}) {}
    binary_string(list<char> _N) : N(_N) { trim_zero(); }
    binary_string(string _N) : N(_N.begin(), _N.end()) { trim_zero(); }
    binary_string(uint64_t _N)
    {
        while (_N > 0) N.push_front((_N & 1) + '0'), _N >>= 1;
        if (N.empty()) N.push_back('0');
        trim_zero();
    }

    binary_string &operator+=(const binary_string &va)
    {
        reverse_iterator<list<char>::iterator> r1 = N.rbegin();
        reverse_iterator<list<char>::const_iterator> r2 = va.N.rbegin();
        int c = 0;
        list<char> ret;
        while (r1 != N.rend() || r2 != va.N.rend() || c > 0) {
            int tm = (r1 != N.rend() ? (*r1 - '0') : 0) + (r2 != va.N.rend() ? (*r2 - '0') : 0) + c;
            c = tm > 1;
            ret.push_front((tm & 1) + '0');
            if (r1 != N.rend()) r1++;
            if (r2 != va.N.rend()) r2++;
        }
        N.swap(ret);
        return *this;
    }

    binary_string &operator-=(const binary_string &va)
    {
        reverse_iterator<list<char>::iterator> r1 = N.rbegin();
        reverse_iterator<list<char>::const_iterator> r2 = va.N.rbegin();
        int b = 0;
        while (r1 != N.rend() || r2 != va.N.rend()) {
            int tm = (r1 != N.rend() ? (*r1 - '0') : 0) - b - (r2 != va.N.rend() ? (*r2 - '0') : 0);
            b = 0;
            if (tm < 0) tm += 2, b = 1;
            if (r1 != N.rend())
                *r1 = tm + '0', r1++;
            else
                N.push_front(tm + '0');
            if (r2 != va.N.rend()) r2++;
        }
        trim_zero();
        return *this;
    }

    binary_string &operator*=(const binary_string &va)
    {
        if ((N.size() == 1 && N.front() == '0') || (va.N.size() == 1 && va.N.front() == '0')) {
            N.clear(), N.push_back('0');
            return *this;
        }
        vector<bool> A, B;
        for (auto ne : N) A.push_back(ne - '0');
        for (auto ne : va.N) B.push_back(ne - '0');
        vector<int> mul(A.size() + B.size(), 0);
        for (int i = A.size() - 1; i >= 0; i--) {
            for (int p = B.size() - 1; p >= 0; p--) {
                int tm = mul[i + p + 1] + A[i] * B[p];
                mul[i + p] += tm >> 1, mul[i + p + 1] = tm & 1;
            }
        }
        N.clear();
        for (auto ne : mul)
            if (!N.empty() || ne > 0) N.push_back(ne + '0');
        if (N.empty()) N.push_back('0');
        return *this;
    }

    binary_string &operator/=(const binary_string &va)
    {
        if (va.N.size() == 1 && va.N.front() == '0') throw runtime_error("Divide by zero");
        string ret;
        binary_string dv;
        for (auto ne : N) {
            dv.N.push_back(ne), dv.trim_zero();
            int c = 0;
            if (va <= dv) dv -= va, c++;
            ret.push_back(c + '0');
        }
        N.clear();
        for (auto c : ret) N.push_back(c);
        trim_zero();
        return *this;
    }

    binary_string &operator%=(const binary_string &va)
    {
        if (va.N.size() == 1 && va.N.front() == '0') throw runtime_error("Divide by zero");
        binary_string dv;
        for (auto ne : N) {
            dv.N.push_back(ne), dv.trim_zero();
            if (va <= dv) dv -= va;
        }
        N.swap(dv.N);
        trim_zero();
        return *this;
    }

    binary_string &operator<<=(int va)
    {
        while (va-- > 0) N.push_back('0');
        return *this;
    }

    binary_string &operator>>=(int va)
    {
        while (va-- > 0 && !N.empty()) N.pop_back();
        if (N.empty()) N.push_back('0');
        return *this;
    }

    binary_string operator+(const binary_string &va) const { return binary_string(*this) += va; }
    binary_string operator-(const binary_string &va) const { return binary_string(*this) -= va; }
    binary_string operator*(const binary_string &va) const { return binary_string(*this) *= va; }
    binary_string operator/(const binary_string &va) const { return binary_string(*this) /= va; }
    binary_string operator%(const binary_string &va) const { return binary_string(*this) %= va; }
    binary_string operator<<(const int va) const { return binary_string(*this) <<= va; }
    binary_string operator>>(const int va) const { return binary_string(*this) >>= va; }
    bool operator==(const binary_string &va) const
    {
        if (N.size() != va.N.size()) return false;
        return equal(N.begin(), N.end(), va.N.begin());
    }
    bool operator!=(const binary_string &va) const { return !(*this == va); }
    bool operator<(const binary_string &va) const
    {
        if (N.size() != va.N.size()) return N.size() < va.N.size();
        return lexicographical_compare(N.begin(), N.end(), va.N.begin(), va.N.end());
    }
    bool operator>(const binary_string &va) const { return va < *this; }
    bool operator<=(const binary_string &va) const { return !(va < *this); }
    bool operator>=(const binary_string &va) const { return !(*this < va); }

    friend ostream &operator<<(ostream &os, const binary_string &va)
    {
        for (auto c : va.N) os << c;
        return os;
    }

    friend istream &operator>>(istream &is, binary_string &va)
    {
        string str;
        is >> str;
        va = binary_string(str);
        return is;
    }

    int length() { return N.size(); }

    void trim_zero()
    {
        while (N.size() > 1 && N.front() == '0') N.pop_front();
    }

    uint64_t bit_to_int()
    {
        if (N.size() > 64) throw runtime_error("|N| exceeds 64");
        uint64_t ret;
        ret = 0;
        for (auto ne : N)
            ret <<= 1, ret += ne - '0';
        return ret;
    }

    list<char> N;
};
