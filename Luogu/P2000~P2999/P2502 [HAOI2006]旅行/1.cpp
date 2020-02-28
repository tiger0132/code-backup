#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25, M = 5e3 + 35;
struct edge {
	int x, y, z;
	bool operator<(const edge& rhs) const { return z < rhs.z; }
} e[M];

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, pp, qq, s, t;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
	scanf("%d%d", &s, &t);
	std::sort(e + 1, e + m + 1);
	pp = 1;
	for (int i = 1; i <= m; memset(p, 0, sizeof p), i++)
		for (int j = i; j <= m; j++)
			if (u(e[j].x, e[j].y), f(s) == f(t) && pp * e[i].z > e[j].z * qq) {
				pp = e[j].z, qq = e[i].z;
				break;
			}
	if (!qq) return puts("IMPOSSIBLE"), 0;
	t = std::__gcd(pp, qq);
	pp /= t, qq /= t;
	if (qq == 1)
		printf("%d", pp);
	else
		printf("%d/%d", pp, qq);
}