#include <algorithm>
#include <bitset>
#include <iostream>

const int N = 2e3 + 32;
std::bitset<N> a[N], b[N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		b[i] = a[i];
		a[i] |= a[i - 1];
	}
	for (int i = n; i >= 1; i--) b[i] |= b[i + 1];
	for (int i = 1; i <= n; i++)
		if ((a[i - 1] | b[i + 1]).count() == m) return puts("YES"), 0;
	puts("NO");
}