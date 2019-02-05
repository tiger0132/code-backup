#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, G = 3, G_ = 332748118, P = 998244353;

int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], lim, l;
int ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int wn = p(G, (P - 1) / (i << 1));
		for (int j = 0; j < lim; j += i << 1) {
			int w = 1;
			for (int k = 0; k < i; k++, w = 1ll * w * wn % P) {
				int x = a[j + k], y = a[i + j + k];
				a[j + k] = (x + y) % P;
				a[i + j + k] = (x - y + P) % P;
			}
		}
	}
}

int n, a[N], b[N], t[N];
void go(int x) {
	if (x == 1) return void(b[0] = p(a[0], P - 2));
	go((x + 1) / 2);
	lim = 1, l = 0;
	while (lim < n * 2) lim <<= 1, l++;
	for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	memset(t, 0, sizeof t);
	memcpy(t, a, x << 2);
	ntt(b, 1), ntt(t, 1);
	for (int i = 0; i <= lim; i++) b[i] = (2 - 1ll * b[i] * t[i] % P + P) % P * b[i] % P;
	ntt(b, -1);
	int tmp = p(x, P - 2);
	std::reverse(a + 1, a + n);
	for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * tmp % P;
	for (int i = x; i < lim; i++) b[i] = 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	go(n);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}