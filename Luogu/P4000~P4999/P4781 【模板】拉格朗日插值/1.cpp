#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e3 + 32, P = 998244353;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int n, k, a[N], b[N], ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
	for (int i = 1; i <= n; i++) {
		int x = 1;
		for (int j = 1; j <= n; j++)
			if (i != j) x = 1ll * x * (a[i] - a[j] + P) % P;
		x = pw(x, P - 2);
		for (int j = 1; j <= n; j++)
			if (i != j) x = 1ll * x * (k - a[j] + P) % P;
		ans = (ans + 1ll * x * b[i] % P) % P;
	}
	printf("%d", ans);
}