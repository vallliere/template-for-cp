struct binary_string {
    binary_string() : N(string("0")) {}
    binary_string(string _N) : N(_N) { trim_zero(); }
    binary_string(int64_t _N)
    {
        N = "";
        while (_N > 0) N += (_N & 1) + '0', _N >>= 1;
        if (!N.size()) N += '0';
        reverse(all(N));
        trim_zero();
    }

    binary_string &operator+=(const binary_string &va)
    {
        int c, tm, x, y;
        x = N.size() - 1, y = va.N.size() - 1, c = 0;
        string ret = "";
        while (x >= 0 || y >= 0 || c > 0) {
            tm = (x >= 0 ? N[x] - '0' : 0) + (y >= 0 ? va.N[y] - '0' : 0) + c;
            c = tm > 1;
            ret.push_back((tm & 1) + '0');
            x--, y--;
        }
        reverse(ret.begin(), ret.end());
        N.swap(ret);
        return *this;
    }

    binary_string &operator-=(const binary_string &va)
    {
        int b, x, y, tm;
        x = N.size() - 1, y = va.N.size() - 1, b = 0;
        while (x >= 0 || y >= 0) {
            tm = (x >= 0 ? N[x] - '0' : 0) - b - (y >= 0 ? va.N[y] - '0' : 0);
            b = 0;
            if (tm < 0) tm += 2, b = 1;
            N[x] = tm + '0';
            x--, y--;
        }
        trim_zero();
        return *this;
    }

    binary_string &operator*=(const binary_string &va)
    {
        int tm;
        if (N == "0" || va.N == "0") {
            N = "0";
            return *this;
        }
        vector<int> mul(N.size() + va.N.size(), 0);
        for (int i = N.size() - 1; i >= 0; i--) {
            for (int p = va.N.size() - 1; p >= 0; p--) {
                tm = (N[i] - '0') * (va.N[p] - '0') + mul[i + p + 1];
                mul[i + p] += tm >> 1, mul[i + p + 1] = tm & 1;
            }
        }
        string ret = "";
        for (int i = 0; i < mul.size(); i++) ret += mul[i] + '0';
        N.swap(ret);
        trim_zero();
        return *this;
    }

    binary_string &operator/=(const binary_string &va)
    {
        int c;
        if (va.N == "0" && *this < va) {
            N = "0";
            return *this;
        }
        string ret = "";
        binary_string dv;
        for (char ne : N) {
            dv.N.push_back(ne);
            dv.trim_zero();
            c = 0;
            if (va <= dv)
                dv -= va, c++;
            ret += c + '0';
        }
        N.swap(ret);
        trim_zero();
        return *this;
    }

    binary_string &operator%=(const binary_string &va)
    {
        if (va.N == "0") {
            N = "0";
            return *this;
        }
        binary_string dv;
        for (char ne : N) {
            dv.N.push_back(ne);
            dv.trim_zero();
            if (va <= dv)
                dv -= va;
        }
        N.swap(dv.N);
        trim_zero();
        return *this;
    }

    binary_string operator+(const binary_string &va) const { return binary_string(*this) += va; }
    binary_string operator-(const binary_string &va) const { return binary_string(*this) -= va; }
    binary_string operator*(const binary_string &va) const { return binary_string(*this) *= va; }
    binary_string operator/(const binary_string &va) const { return binary_string(*this) /= va; }
    binary_string operator%(const binary_string &va) const { return binary_string(*this) %= va; }
    bool operator==(const binary_string &va) const { return N == va.N; }
    bool operator!=(const binary_string &va) const { return N != va.N; }
    bool operator<(const binary_string &va) const { return va.N.size() > N.size() || (va.N.size() == N.size() && va.N > N); }
    bool operator>(const binary_string &va) const { return va.N.size() < N.size() || (va.N.size() == N.size() && va.N < N); }
    bool operator<=(const binary_string &va) const { return !(va < *this); }
    bool operator>=(const binary_string &va) const { return !(*this < va); }

    friend ostream &operator<<(ostream &os, const binary_string &va)
    {
        return os << va.N;
    }

    friend istream &operator>>(istream &is, binary_string &va)
    {
        is >> va.N;
        va.trim_zero();
        return is;
    }

    int length() { return N.size(); }

    void trim_zero()
    {
        size_t lo = N.find_first_not_of('0');
        if (lo == string::npos) {
            N = "0";
            return;
        }
        N = N.substr(lo);
    }

    string N;
};
