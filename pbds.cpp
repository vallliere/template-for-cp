#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set(t) tree<t, null_type, less<t>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset(t) tree<t, null_type, less_equal<t>, rb_tree_tag, tree_order_statistics_node_update>
