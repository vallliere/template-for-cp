
#include <bits/extc++.h>
mt19937 seed(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> gen_random(1e8, 1e9);

struct splitmix64_hash {
    static uint64_t splitmix64(uint64_t va)
    {
        va += 0x9e3779b97f4a7c15;
        va = (va ^ (va >> 30)) * 0xbf58476d1ce4e5b9;
        va = (va ^ (va >> 27)) * 0x94d049bb133111eb;
        return va ^ (va >> 31);
    }
    size_t operator()(uint64_t va) const
    {
        static const uint64_t FIXED_RANDOM = gen_random(seed);
        return splitmix64(va + FIXED_RANDOM);
    }
};
template <typename type1, typename type2, typename hash_t = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<type1, type2, hash_t>;
