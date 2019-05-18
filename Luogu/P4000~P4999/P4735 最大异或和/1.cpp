#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define M1(x, y) (((x) >> (y)) & 1)
#define GET(x, y, z, w, ...) w
#define $(...) GET(__VA_ARGS__, M2, M1)(__VA_ARGS__)

const int N = 1e6 + 61, LG = 24;

extern struct node _[];
int M2(int, int, int);
int cnt;
struct node {
	int lc, rc, v;
	int ins(int x, int id = LG) {
		if (id < 0) return $(0, 0, v + 1);
		if (!$(x, id))
			return $(_[lc].ins(x, id - 1), rc, v + 1);
		else
			return $(lc, _[rc].ins(x, id - 1), v + 1);
	}
} _[N << 5];
inline int M2(int x, int y, int z) { return _[++cnt] = (node){x, y, z}, cnt; }
int rt[N];
int query(int L, int R, int x) {
	int ret = 0;
	for (int i = LG; i >= 0; i--) {
		int node::*p = $(x, i) ? &node::lc : &node::rc;
		int node::*q = $(x, i) ? &node::rc : &node::lc;
		if (_[_[R].*p].v - _[_[L].*p].v)
			L = _[L].*p, R = _[R].*p, ret += 1 << i;
		else
			L = _[L].*q, R = _[R].*q;
	}
	return ret;
}

int n, m, a[N], x, y, z;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	rt[0] = $(0, 0, 0);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), rt[i] = _[rt[i - 1]].ins(a[i] ^= a[i - 1]);
	while (m--) {
		scanf("%s%d", op, &x);
		if (*op == 'A') {
			rt[n + 1] = _[rt[n]].ins(a[n + 1] = a[n] ^ x);
			n++;
		} else {
			scanf("%d%d", &y, &z), x--, y--;
			if (x == y && !x)
				printf("%d\n", a[n] ^ z);
			else
				printf("%d\n", query(rt[std::max(x - 1, 0)], rt[y], z ^ a[n]));
		}
	}
}