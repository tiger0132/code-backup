#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;
struct BIT {
	int a[N], n;
	int lowbit(int x) { return x & -x; }
	void add(int i, int x) {
		for (; i <= n; i += lowbit(i)) a[i] += x;
	}
	int query(int i) {
		int ret = 0;
		for (; i; i -= lowbit(i)) ret += a[i];
		return ret;
	}
	int query(int l, int r) { return query(r) - query(l - 1); }
	void init(int n_, int *a) {
		n = n_;
		for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]);
	}
} bit[26];

int n, m, op, x, y, ans, a[26][N];
char s[N], c[2];
int main() {
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	for (int i = 0; i < 26; i++) {
		for (int j = 1; j <= n; j++) a[i][j] = a[i][j - 1] + (s[j] == i + 97);
		bit[i].init(n, a[i]);
	}
	while (m--) {
		scanf("%d%d", &op, &x);
		if (op == 1) {
			scanf("%s", c), y = *c - 97;
			bit[s[x] - 97].add(x, -1);
			bit[(s[x] = *c) - 97].add(x, 1);
		} else {
			scanf("%d", &y);
			ans = 0;
			for (int i = 0; i < 26; i++) ans += bit[i].query(x, y) > 0;
			printf("%d\n", ans);
		}
	}
}