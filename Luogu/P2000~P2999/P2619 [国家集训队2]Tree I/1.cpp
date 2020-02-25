#include <algorithm>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2

const int N = 1e6 + 61;
struct edge {
	int x, y, z;
	bool operator<(const edge& rhs) const { return z < rhs.z; }
} e[2][N], ed[N];

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
bool u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) return x[p] = y, 1;
	return 0;
}

int c[2], m, k, ans;
bool check(int ofs) {
	memset(p, 0, sizeof p);
	int ret = 0, p1 = 1, p2 = 1;
	ans = 0;
	while (p1 <= c[0] && p2 <= c[1])
		if (e[0][p1].z + ofs <= e[1][p2].z) {
			if (u(e[0][p1].x, e[0][p1].y)) ans += e[0][p1].z + ofs, ret++;
			p1++;
		} else {
			if (u(e[1][p2].x, e[1][p2].y)) ans += e[1][p2].z;
			p2++;
		}
	for (; p1 <= c[0]; p1++)
		if (u(e[0][p1].x, e[0][p1].y)) ans += e[0][p1].z + ofs, ret++;
	for (; p2 <= c[1]; p2++)
		if (u(e[1][p2].x, e[1][p2].y)) ans += e[1][p2].z;
	return ret < k;
}

int n, l, r;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x, y, z, w; i <= m; i++)
		scanf("%d%d%d%d", &x, &y, &z, &w), e[w][++c[w]] = (edge){x + 1, y + 1, z};
	std::sort(e[0] + 1, e[0] + c[0] + 1);
	std::sort(e[1] + 1, e[1] + c[1] + 1);
	for (l = -100, r = 100; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	check(r);
	printf("%d", ans - k * r);
}