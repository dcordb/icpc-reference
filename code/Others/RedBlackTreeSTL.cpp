#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

ordered_set X; //multiset, usar con pair, primer valor es el valor real, el segundo es un contador cualquiera

//los siguientes ejemplos es usandolo sin el par
X.insert(1);
X.insert(2);
X.insert(4);
X.insert(8);
X.insert(16);

//find_by_order regresa iterador al kth elemento (contando desde 0)
//order_of_key regresa cantidad de elementos menores estrictos que el dado
//estas operaciones son el O(log n) tambien soporta las operaciones de set normal
//como lower/upper bound, insert, erase, find, etc
//ejemplos

cout<<*X.find_by_order(1)<<endl; // 2
cout<<*X.find_by_order(2)<<endl; // 4
cout<<*X.find_by_order(4)<<endl; // 16
cout<<(end(X)==X.find_by_order(6))<<endl; // true

cout<<X.order_of_key(-5)<<endl;  // 0
cout<<X.order_of_key(1)<<endl;   // 0
cout<<X.order_of_key(3)<<endl;   // 2
cout<<X.order_of_key(4)<<endl;   // 2
cout<<X.order_of_key(400)<<endl; // 5