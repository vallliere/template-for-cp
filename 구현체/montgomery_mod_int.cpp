template <uint32_t mod_t>
struct montgomery_mod_int {
    using mod_int = montgomery_mod_int;

    /*
    mod_t * R = 1 mod (1 << 32)
    {f(R) = 1 / R - mod_t -> 0}, {f'(R) = - 1 / R^2}
    R_{n+1} = R_{n} - f(R_{n}) / f'(R_{n}) = R_{n} * (2 - mod_t * R_{n})
    */
    static constexpr uint32_t get_R()
    {
        uint32_t ret = mod_t;
        for (int i = 0; i < 4; ++i) ret *= 2 - mod_t * ret;
        return ret;
    }

    static constexpr uint32_t R = get_R();
    static constexpr uint32_t M64 = -uint64_t(mod_t) % mod_t;
    static_assert(mod_t < (1 << 30), "invalid, mod >= 2 ^ 30");
    static_assert((mod_t & 1) == 1, "invalid, mod % 2 == 0");
    static_assert(R * mod_t == 1, "invalid, mod_t * R != 1 mod (1 << 32)");

    uint32_t N;

    constexpr montgomery_mod_int() : N(0) {}
    constexpr montgomery_mod_int(const int64_t &_N) : N(reduce(uint64_t(_N % mod_t + mod_t) * M64)) {};

    constexpr mod_int &operator+=(const mod_int &va)
    {
        if (int(N += va.N - 2 * mod_t) < 0) N += 2 * mod_t;
        return *this;
    }

    constexpr mod_int &operator-=(const mod_int &va)
    {
        if (int(N -= va.N) < 0) N += 2 * mod_t;
        return *this;
    }

    constexpr mod_int &operator*=(const mod_int &va)
    {
        N = reduce(uint64_t(N) * va.N);
        return *this;
    }

    constexpr mod_int &operator/=(const mod_int &va)
    {
        *this *= va.inverse();
        return *this;
    }

    constexpr mod_int operator+(const mod_int &va) const { return mod_int(*this) += va; }
    constexpr mod_int operator-(const mod_int &va) const { return mod_int(*this) -= va; }
    constexpr mod_int operator*(const mod_int &va) const { return mod_int(*this) *= va; }
    constexpr mod_int operator/(const mod_int &va) const { return mod_int(*this) /= va; }
    constexpr bool operator==(const mod_int &va) const { return (N >= mod_t ? N - mod_t : N) == (va.N >= mod_t ? va.N - mod_t : va.N); }
    constexpr bool operator!=(const mod_int &va) const { return (N >= mod_t ? N - mod_t : N) != (va.N >= mod_t ? va.N - mod_t : va.N); }
    constexpr mod_int operator-() const { return mod_int() - mod_int(*this); }
    constexpr mod_int operator+() const { return mod_int(*this); }

    friend ostream &operator<<(ostream &os, const mod_int &va)
    {
        return os << va.get();
    }

    friend istream &operator>>(istream &is, mod_int &va)
    {
        int64_t t;
        is >> t;
        va = montgomery_mod_int<mod_t>(t);
        return is;
    }

    static constexpr uint32_t reduce(const uint64_t &va) { return (va + uint64_t(uint32_t(va) * uint32_t(-R)) * mod_t) >> 32; }

    constexpr mod_int pow(uint64_t va) const
    {
        mod_int ret(1), mul(*this);
        while (va > 0) {
            if (va & 1) ret *= mul;
            mul *= mul;
            va >>= 1;
        }
        return ret;
    }

    constexpr mod_int inverse() const
    {  // exgcd
        int x1, y1, x2, y2;
        x1 = get(), y1 = mod_t, x2 = 1, y2 = 0;
        while (y1 > 0) {
            x2 -= x1 / y1 * y2, x1 %= y1;
            swap(x1, y1), swap(x2, y2);
        }
        return mod_int(x2);
    }

    static constexpr uint32_t get_mod() { return mod_t; }

    constexpr uint32_t get() const
    {
        uint32_t ret = reduce(N);
        return ret >= mod_t ? ret - mod_t : ret;
    }
};
