#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


template<typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// template<typename T> using o_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;


/**
 *  o_set<int> s; s.insert(1); s.insert(4); s.insert(200);
 *  cout << *s.find_by_order(1) << endl; // k'th element
 *  cout << s.order_of_key(100) << endl; // number of element less than k

 *  o_map<int, int> mp; mp.insert({1, 2}); mp.insert({4, 5}); mp.insert({200, 0});
 *  cout << mp.find_by_order(1)->first << endl; // k'th element
 *  cout << mp.order_of_key(100) << endl; // number of first element less than k
**/