#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, k, a[N], l[N], p[N];
void rm(int x) { x[l][p] = x[p], x[p][l] = x[l]; }
int main() {
	scanf("%d%d", &n, &k);
	if (k == 1 || k == 2 * n - 1) return puts("No"), 0;
	puts("Yes");
	if (n == 2) return puts("1\n2\n3"), 0;
	for (int i = 0; i < 2 * n; i++) i[p] = i - 1, i[l] = i + 1;
	if (k == 2) {
		rm(a[n - 1] = 3);
		rm(a[n + 0] = 2);
		rm(a[n + 1] = 1);
		rm(a[n + 2] = 4);
	} else {
		rm(a[n - 1] = k - 1);
		rm(a[n + 0] = k + 0);
		rm(a[n + 1] = k + 1);
		rm(a[n + 2] = k - 2);
	}
	n = n * 2 - 1;
	for (int i = 1, c = 0 [l]; i <= n; printf("%d\n", a[i++]))
		if (!a[i]) a[i] = c, c = c[l];
}