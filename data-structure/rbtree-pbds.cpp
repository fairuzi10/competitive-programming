#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type, // make it int, char, or whatever so it becomes map
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

ordered_set setz;

int main() {
	setz.insert(1);
	setz.insert(2);
	setz.insert(5);
	puts("--- find_by_order ---");
	// return a pointer
	cout << *setz.find_by_order(0) << endl;
	cout << *setz.find_by_order(2) << endl;
	puts("--- order_of_key ---");
	// return an int
	cout << setz.order_of_key(2) << endl;
	cout << setz.order_of_key(6) << endl;
	
	return 0;
}
