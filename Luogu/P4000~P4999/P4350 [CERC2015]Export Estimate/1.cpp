#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>

const int N = 3e5 + 53;

struct edge {
	int x, y, z;
	bool operator<(const edge& r) const { return z < r.z; }
} e[N];

int p[N], sz[N], d[N], d0, d2, cyc;
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y, y[sz] += x[sz];
}

int n, m, q, id[N], a1[N], a2[N], a[N];
bool cmp(int x, int y) { return x[a] > y[a]; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
	std::sort(e + 1, e + m + 1);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) scanf("%d", a + i), i[id] = i;
	std::sort(id + 1, id + q + 1, cmp);
	d0 = n;
	for (int i = 1; i <= n; i++) i[sz] = 1;
	for (int i = 1, j = m; i <= q; i++) {
		for (; e[j].z >= a[id[i]] && j >= 1; j--) {
			int s = e[j].x, t = e[j].y, rt, fl = f(s) != f(t);

			if (fl)
				cyc -= !f(s)[sz] + !f(t)[sz];
			else
				cyc -= !f(s)[sz];
			u(s, t), rt = f(s);

			d0 -= !s[d] + !t[d];
			d2 -= (s[d] == 2) + (t[d] == 2);
			rt[sz] += (s[d] == 2) + (t[d] == 2);

			s[d]++, t[d]++;

			d2 += (s[d] == 2) + (t[d] == 2);
			rt[sz] -= (s[d] == 2) + (t[d] == 2);
			cyc += !rt[sz];
		}
		a1[id[i]] = n - d0 - d2 + cyc;
		a2[id[i]] = m - j - d2 + cyc;
	}
	for (int i = 1; i <= q; i++) printf("%d %d\n", a1[i], a2[i]);
}