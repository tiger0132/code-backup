#include <algorithm>
#include <cstdio>
#include <cstring>
#define M2(x, y) ((x >> (2 * (y))) & 3)
#define M1(x) (1 << (2 * (x)))
#define GET(_1, _2, x, ...) x
#define $(...) GET(__VA_ARGS__, M2, M1)(__VA_ARGS__)

struct bigint {
	const int P = 1e9;
	int a[10], n;
	inline bigint(int x = 0) { n = 1, memset(a, 0, sizeof a), a[0] = x; }
	inline void operator=(const bigint& rhs) { memcpy(a, rhs.a, sizeof a), n = rhs.n; }
	inline void operator+=(const bigint& rhs) {
		int tmp[10]{};
		n = std::max(n, rhs.n) + 1;
		for (int i = 0; i < n; i++) tmp[i + 1] += (tmp[i] += a[i] + rhs.a[i]) / P, tmp[i] %= P;
		memcpy(a, tmp, sizeof a);
		while (n > 1 && !a[n - 1]) n--;
	}
	inline void print() {
		printf("%d", a[n - 1]);
		for (int i = n - 2; i >= 0; i--) printf("%09d", a[i]);
	}
};

struct hashmap {
	static const int N = 1e6 + 61, P = 999983;
	struct node {
		int next, key;
		bigint val;
	} e[N];
	int head[N], cnt;
	inline void ins(int x, bigint y) {
		int hsh = x % P + 1;
		for (int i = head[hsh]; i; i = e[i].next)
			if (e[i].key == x) return void(e[i].val += y);
		e[++cnt] = (node){head[hsh], x, y}, head[hsh] = cnt;
	}
	inline void clear() { memset(head, 0, sizeof head); }
} tab[2];

int n, m, cur;
bigint ans;
int main() {
	scanf("%d%d", &m, &n);
	if (n == 1 || m == 1) return puts("1"), 0;
	tab[0].ins(0, 1);
	for (int i = 1, p, c$; i <= n; i++) {
		for (int j = 1; j <= tab[cur].cnt; j++) tab[cur].e[j].key <<= 2;
		for (int j = 1; j <= m; j++) {
			tab[0].clear(), tab[1].clear(), tab[cur ^= 1].cnt = 0;
			for (int k = 1; k <= tab[!cur].cnt; k++) {
				int st = tab[!cur].e[k].key, R = $(st, j - 1), D = $(st, j);
				bigint val = tab[!cur].e[k].val;
				if (!R && !D) {
					if (i < n && j < m) tab[cur].ins(st + $(j - 1) + 2 * $(j), val);
				} else if (R && !D) {
					if (j < m) tab[cur].ins(st + R * ($(j) - $(j - 1)), val);
					if (i < n) tab[cur].ins(st, val);
				} else if (!R && D) {
					if (i < n) tab[cur].ins(st + D * ($(j - 1) - $(j)), val);
					if (j < m) tab[cur].ins(st, val);
				} else if (R == 1 && D == 1) {
					for (p = j + 1, c$ = 1; p <= m && c$; p++) c$ += ($(st, p) == 1) - ($(st, p) == 2);
					if (!c$) p--, tab[cur].ins(st - $(p) - $(j) - $(j - 1), val);
				} else if (R == 2 && D == 2) {
					for (p = j - 2, c$ = 1; p >= 0 && c$; p--) c$ += ($(st, p) == 2) - ($(st, p) == 1);
					if (!c$) p++, tab[cur].ins(st + $(p) - 2 * ($(j) + $(j - 1)), val);
				} else if (R == 2 && D == 1) {
					tab[cur].ins(st - $(j) - 2 * $(j - 1), val);
				} else if (R == 1 && D == 2 && i == n && j == m)
					ans += val;
			}
		}
	}
	ans += ans, ans.print();
}