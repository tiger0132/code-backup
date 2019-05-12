#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>

const int N = 3e5 + 53;

std::pair<int, int> b[N];
int n, mn = 1e9, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = std::make_pair(a[i], i);
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) {
		int pos = b[i].second;
		if (pos != 1) mn = std::min(mn, std::min(a[1], a[pos]) / (pos - 1));
		if (pos != n) mn = std::min(mn, std::min(a[n], a[pos]) / (n - pos));
		// printf("%d, %d\n", std::min(a[1], a[pos]) / (pos - 1), std::min(a[n], a[pos]) / (n - pos));
	}
	printf("%d", mn);
}