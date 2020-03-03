#include <algorithm>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2

typedef long long ll;
const int N = 5e4 + 45, M = 5e5 + 55;

struct edge {
	int x, y, z;
	bool operator<(const edge& rhs) const { return z < rhs.z; }
} e1[M], e2[M], ed[M];

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
int mg(int x, int y) {
	if ((x = f(x)) != (y = f(y))) return x[p] = y, 1;
	return 0;
}

int n, m, s, k, c1, c2;
ll ans;
int check(int ofs) {
	memset(p, 0, sizeof p);
	int r = 0, p1 = 1, p2 = 1;
	ans = 0;
	for (; p2 <= c2; p2++) {
		for (; p1 <= c1 && e1[p1].z + ofs <= e2[p2].z; p1++)
			if (mg(e1[p1].x, e1[p1].y)) ans += e1[p1].z + ofs, r++;
		if (mg(e2[p2].x, e2[p2].y)) ans += e2[p2].z;
	}
	for (; p1 <= c1; p1++)
		if (mg(e1[p1].x, e1[p1].y)) ans += e1[p1].z + ofs, r++;
	return r < k;
}

int x, y, z, l, r;
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		if (x == s || y == s)
			e1[++c1] = (edge){x, y, z};
		else
			e2[++c2] = (edge){x, y, z};
		mg(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (f(i) != f(1)) return puts("Impossible"), 0;
	if (c1 < k) return puts("Impossible"), 0;
	std::sort(e1 + 1, e1 + c1 + 1);
	std::sort(e2 + 1, e2 + c2 + 1);
	if (check(-1e9)) return puts("Impossible"), 0;
	for (l = -1e9, r = 1e9; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	check(r);
	printf("%lld", ans - k * r);
}