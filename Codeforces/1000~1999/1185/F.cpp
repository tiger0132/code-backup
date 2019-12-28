#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#define int long long
#define $(x) (1 << ((x)-1))

typedef std::pair<int, int> pii;
const int N = 1e3 + 31, M = 512, INF = 0x3f3f3f3f3f3f3f3f;

int n, m, x, y, z, c, mn, p, q, mx, fl[N], s[N], f[N];
pii t1[N], t2[N];
signed main() {
	memset(t1, 0x3f, sizeof t1);
	memset(t2, 0x3f, sizeof t2);
	mn = INF;
	for (scanf("%lld%lld", &n, &m); n--; s[z]++)
		for (z = !scanf("%lld", &x); x--; z |= $(y)) scanf("%lld", &y);
	for (int i = 1; i <= m; i++) {
		for (z = !scanf("%lld%lld", &c, &x); x--; z |= $(y)) scanf("%lld", &y);
		if (pii{c, i} < t1[z])
			t2[z] = t1[z], t1[z] = pii{c, i};
		else if (pii{c, i} < t2[z])
			t2[z] = {c, i};
	}
	for (int i = 1; i < M; i++)
		for (int j = 1; j < M; j++)
			if (t1[i].first != INF && t1[j].first != INF) fl[i | j] = 1;
	for (int i = 1; i < M; mx = std::max(mx, f[i++]))
		if (fl[i])
			for (int j = i; j; j = (j - 1) & i) f[i] += s[j];
	for (int i = 1; i < M; i++)
		for (int j = 1; j < M; j++)
			if (f[i | j] == mx) {
				x = t1[i].first + (i == j ? t2[j].first : t1[j].first);
				if (x < mn) mn = x, p = t1[i].second, q = i == j ? t2[j].second : t1[j].second;
			}
	printf("%lld %lld", p, q);
}