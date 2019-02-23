#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

int n, l, r = 1e9, a[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i += 2) printf("%d ", a[i]);
	for (int i = n - (n & 1); i >= 1; i -= 2) printf("%d ", a[i]);
}