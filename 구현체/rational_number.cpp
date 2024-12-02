struct rational {
    ll a, b;  // (b / a)
    rational() : a(0), b(0) {}
    rational(ll _a, ll _b) : a(_a), b(_b) {}

    void update()
    {
        ll n;
        if (b == 0)
            a = (a > 0) - (a < 0);
        else {
            if (b < 0)
                a = -a, b = -b;
            n = gcd(a, b);
            a /= n, b /= n;
        }
    }

    friend ostream& operator<<(ostream& ofs, const rational& val)
    {
        ofs << "(" << val.b << " / " << val.a << ")";
        return ofs;
    }
    rational operator+(const rational& val) { return rational({a * val.a, b * val.a + val.b * a}); }
    rational operator+=(const rational& val) { return *this = *this + val; }
    rational operator-(const rational& val) { return rational({a * val.a, b * val.a - val.b * a}); }
    rational operator-=(const rational& val) { return *this = *this - val; }
    rational operator*(const rational& val) { return rational({a * val.a, b * val.b}); }
    rational operator*=(const rational& val) { return *this = *this * val; }
    rational operator/(const rational& val) { return rational({a * val.b, b * val.a}); }
    rational operator/=(const rational& val) { return *this = *this / val; }
    bool operator>(const rational& val) { return b * val.a > val.b * a; }
    bool operator>=(const rational& val) { return b * val.a >= val.b * a; }
    bool operator<(const rational& val) { return b * val.a < val.b * a; }
    bool operator<=(const rational& val) { return b * val.a <= val.b * a; }
    bool operator==(const rational& val) { return b * val.a == val.b * a; }
};
