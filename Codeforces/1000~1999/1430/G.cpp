#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 18;

int f[1 << N], l[1 << N], d[1 << N], out[1 << N], a[1 << N];
int n, m, U;
int ans[N];
int main() {
	memset(f, 0x3f, sizeof f), f[0] = 0;
	scanf("%d%d", &n, &m), U = (1 << n) - 1;
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z), x--, y--;
		out[1 << x] |= 1 << y;
		a[1 << x] += z, a[1 << y] -= z;
	}
	for (int S = 1; S <= U; S++) {
		out[S] = out[S ^ (S & -S)] | out[S & -S];
		a[S] = a[S ^ (S & -S)] + a[S & -S];
	}
	for (int S = 1; S <= U; S++)
		for (int T = S; T; T = (T - 1) & S)
			if (!(T & out[S ^ T]) && !(out[T] & T))
				if (f[S ^ T] + a[U ^ S] < f[S]) {
					f[S] = f[S ^ T] + a[U ^ S];
					l[S] = S ^ T;
					d[S] = d[S ^ T] + 1;
				}
	for (int S = U; S; S = l[S])
		for (int i = 0; i < n; i++)
			if ((S >> i) & 1) ans[i] = d[S];
	for (int i = 0; i < n; i++) printf("%d%c", ans[i] - 1, " \n"[i == n - 1]);
}