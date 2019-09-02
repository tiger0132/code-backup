#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef unsigned short u;
const int N = 6e4 + 46, M = 1 << 26;

int sz;
struct node {
	int l, r, *ans;
	bool operator<(const node& rhs) const {
		return l / sz == rhs.l / sz ? l / sz % 2 ? r < rhs.r : r > rhs.r : l < rhs.l;
	}
} q[N];

int n, m, a[N], lnk[N][26], l[N], ans[N], lans;
bool vis[M];
char s[N];
u c[M];

void add(int x) {
	lans += a[x][c]++;
	for (int i = 0; i < l[x]; i++) lans += lnk[x][i][c];
}
void del(int x) {
	lans -= --a[x][c];
	for (int i = 0; i < l[x]; i++) lans -= lnk[x][i][c];
}
int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	sz = n / sqrt(m);
	for (int i = 0; i <= n; i++) {
		if (i) a[i] = a[i - 1] ^ (1 << (s[i] - 'a'));
		a[i][vis] = true;
	}
	for (int i = 0; i <= n; i++)
		for (int j = 1; j < (1 << 26); j <<= 1)
			if ((a[i] ^ j)[vis]) lnk[i][l[i]++] = a[i] ^ j;
	for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].ans = ans + i;
	std::sort(q + 1, q + m + 1);
	int l = 2, r = 1;
	a[1][c]++;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) add(--l - 1);
		while (r < q[i].r) add(++r);
		while (l < q[i].l) del(l++ - 1);
		while (r > q[i].r) del(r--);
		*q[i].ans = lans;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}