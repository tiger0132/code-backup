#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

const int N = 2e3 + 32;

int n, k, x, y, v[N][N], a[N];
FILE *in, *out, *ans;
bool f1 = 1, f2 = 1;
int main() {
	in = fopen("1.in", "r");
	out = fopen("1.out", "r");
	ans = fopen("1.ans", "r");
	fscanf(in, "%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		for (fscanf(in, "%*d%d", &x); x--;) fscanf(in, "%d", &y), v[i][y] = 1;
	for (int i = 1; i <= k; i++) fscanf(in, "%d", a + i);
	for (int i = 1; i <= k; i++) {
		fscanf(out, "%d%*d", &x);
		fscanf(ans, "%d%*d", &y);
		if (x == -1 || y == -1) return puts(x == y ? "YES" : "NO"), 0;
		if (x) f1 &= v[x][a[i]];
		if (y) f2 &= v[y][a[i]];
	}
	printf("%d %d\n", f1, f2);
}