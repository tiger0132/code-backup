#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#define x first
#define y second

typedef std::pair<int, int> pii;
const int N = 3e5 + 53, P = 998244353;

int n, l, a1, a2, a3, fac[N];
pii a[N];
int main() {
	scanf("%d", &n), a1 = a2 = a3 = fac[0] = 1;
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y), fac[i] = 1ll * fac[i - 1] * i % P;
	std::sort(a + 1, a + n + 1);
	for (int i = l = 1; i <= n; i++)
		if (a[i].x != a[l].x) a1 = 1ll * a1 * fac[i - l] % P, l = i;
	a1 = 1ll * a1 * fac[n - l + 1] % P;

	std::sort(a + 1, a + n + 1, [](const pii& x, const pii& y) { return x.y < y.y; });
	for (int i = l = 1; i <= n; i++)
		if (a[i].y != a[l].y) a2 = 1ll * a2 * fac[i - l] % P, l = i;
	a2 = 1ll * a2 * fac[n - l + 1] % P;

	std::sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; i++)
		if (a[i - 1].y > a[i].y)
			return !printf("%lld", ((1ll * fac[n] - a1 - a2) % P + P) % P);
	for (int i = l = 1; i <= n; i++)
		if (a[i].x != a[l].x || a[i].y != a[l].y) a3 = 1ll * a3 * fac[i - l] % P, l = i;
	a3 = 1ll * a3 * fac[n - l + 1] % P;

	printf("%lld", ((1ll * fac[n] - a1 - a2 + a3) % P + P) % P);
}