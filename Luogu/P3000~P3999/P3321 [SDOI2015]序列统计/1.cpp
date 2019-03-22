#include <algorithm>
#include <cstdio>
#include <cstring>

const int P = 1004535809, G = 3, GInv = 334845270, N = 4e4 + 44;
int p(int x, int y, int z = P) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % z)
		if (y & 1) ret = 1ll * ret * x % z;
	return ret;
}

int r[N], lim, l;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int gn = p(op == 1 ? G : GInv, (P - 1) / (i << 1));
		for (int j = 0; j < lim; j += 2 * i) {
			int g = 1;
			for (int k = 0; k < i; k++, g = 1ll * g * gn % P) {
				int x = a[j + k], y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = p(lim, P - 2);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % P;
}
void mul(int n, int *a, int *b) {
	static int c[N], d[N];
	memcpy(c, a, lim << 2), memcpy(d, b, lim << 2);
	ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) a[i] = 1ll * c[i] * d[i] % P;
	ntt(a, -1);
	for (int i = 0; i < n; i++) a[i] = (a[i] + a[i + n]) % P;
	memset(a + n, 0, n << 2);
}
void init_mul(int n) {
	lim = 1, l = 0;
	while (lim <= n) lim <<= 1, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

int log[N];
void initLog(int m) {
	static int st[N]{}, top = 0;
	int n = m - 1, g;
	for (int i = 2; n > 1 && i * i <= n; i++)
		for ((n % i) || (st[++top] = i); !(n % i);) n /= i;
	if (n > 1) st[++top] = n;
	for (int i = 2; i < m; i++) {
		for (int j = 1; j <= top; j++)
			if (p(i, (m - 1) / st[j], m) == 1) goto end;
		g = i;
		break;
	end:;
	}
	for (int i = 0, j = 1; i < m - 1; i++, j = j * g % m) log[j] = i;
}

int n, m, k, s, a[N], b[N] = {1}, c[N], x;
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &s);
	initLog(m);
	for (int i = 1; i <= s; i++) scanf("%d", &x), (x %= m) && (a[log[x]] = 1);
	init_mul(m * 2);
	for (; n; n >>= 1, mul(m - 1, a, a))
		if (n & 1) mul(m - 1, b, a);
	printf("%d", b[log[k]]);
}