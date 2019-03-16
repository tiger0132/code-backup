// C++14
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using ll = long long;
const int N = 1e6 + 61, P = 998244353;
const ll div2 = 499122177;

int n;
template <typename F>
void fwt(int *a, F f) {
	for (int i = 1; i <= n / 2; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = 0; k < i; k++) f(a[j + k], a[j + k + i]);
}

template <typename F1, typename F2>
void $(int *a, int *b, int *c, F1 f, F2 rf) {
	fwt(a, f), fwt(b, f);
	for (int i = 0; i < n; i++) c[i] = 1ll * a[i] * b[i] % P;
	fwt(a, rf), fwt(b, rf), fwt(c, rf);
}

int a[N], b[N], c[N];
int main() {
	scanf("%d", &n), n = 1 << n;
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	for (int i = 0; i < n; i++) scanf("%d", b + i);
	$(a, b, c, [](int x, int &y) { y = (y + x) % P; }, [](int x, int &y) { y = (y - x + P) % P; });
	for (int i = 0; i < n; i++) printf("%d%c", c[i], " \n"[i == n - 1]);
	$(a, b, c, [](int &x, int y) { x = (x + y) % P; }, [](int &x, int y) { x = (x - y + P) % P; });
	for (int i = 0; i < n; i++) printf("%d%c", c[i], " \n"[i == n - 1]);
	$(a, b, c,
	  [](int &x, int &y) {
		  int t = x;
		  x = (t + y) % P, y = (t - y + P) % P;
	  },
	  [](int &x, int &y) {
		  int t = x;
		  x = (t + y) * div2 % P, y = (t - y + P) * div2 % P;
	  });
	for (int i = 0; i < n; i++) printf("%d%c", c[i], " \n"[i == n - 1]);
}