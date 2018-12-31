#include <algorithm>
#include <cstdio>

const int N = 1e3+31;

int n, a[N], b[N], x[N], y[N];
int p, q;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", a+i, b+i);
	for (int i = 1; i <= n; i++) scanf("%d%d", x+i, y+i);
	p = q = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		if (a[i] < a[p] || (a[i] == a[p] && b[i] < b[p])) p = i;
		if (x[i] < x[p] || (x[i] == x[p] && y[i] < y[p])) q = i;
	}
	printf("%d %d\n", a[p] + x[q], b[p] + y[q]);
}