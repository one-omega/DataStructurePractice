#include <bits/stdc++.h>
using namespace std;
int table[100001];
int a[100001], n;

void table_sort() {
	for (int P = 1; P < n; P++) {
		int temp = table[P];
		int i;
		for (i = P; i > 0 && a[table[i-1]] > a[temp]; i--) {
			table[i] = table[i-1];
		}
		table[i] = temp;
	}
}

void physics_sort() {
	int temp = a[0];
	for (int i = 0; i < n; i++) {
		int temp = a[i];
		int t = i;
		while (table[i] != i && table[i] != table[table[i]]) {
			a[i] = a[table[i]];
			int pos = i;
			i = table[i];
			table[pos] = pos;
		}
		a[i] = temp;
		i = t;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		table[i] = i;
	}
	table_sort();
	for (int i = 0; i < n; i++) {
		if (i < n-1)
			cout << a[table[i]] << " ";
		else
			cout << a[table[i]] << '\n';
	}
	physics_sort();
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
    return 0;
}