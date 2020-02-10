#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, x[N], y[N], u, v;
int main() {
	scanf("%d", &n);
	if (n % 2 == 1) return puts("NO"), 0;
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	u = x[1] + x[n / 2 + 1];
	v = y[1] + y[n / 2 + 1];
	for (int i = 1; i <= n / 2; i++)
		if (x[i] + x[n / 2 + i] != u || y[i] + y[n / 2 + i] != v) return puts("NO"), 0;
	puts("YES");
}