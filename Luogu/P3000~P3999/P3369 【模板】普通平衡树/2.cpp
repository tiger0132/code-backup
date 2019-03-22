#include <cstdio>
#define _ inline
#define L(x) ch[x][0]
#define R(x) ch[x][1]

const int N = 1e5+15;

namespace $ {
	int ch[N][2], p[N], v[N], s[N], c$[N], n;
	_ void up(int x) { s[x] = s[L(x)] + s[R(x)] + c$[x]; }
	_ int c(int x) { return R(p[x]) == x; }
	_ void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w; p[w] = y;
		ch[z][c(y)] = x; p[x] = z;
		ch[x][!k] = y; p[y] = x;
		up(y); up(x);
	}
	_ void sp(int& r, int x, int g = 0) {
		for (int y; (y = p[x]) != g; rt(x)) {
			if (p[y] != g) rt(c(x) == c(y) ? y : x);
		}
		if (!g) r = x;
	}
	_ void ins(int& r, int x) {
		int y = r, z = 0;
		for (; y && x != v[y]; y = ch[y][x > v[y]]) z = y;
		if (y) c$[y]++;
		else {
			y = ++n;
			if (z) ch[z][x > v[z]] = y;
			v[y] = x; p[y] = z; c$[y] = s[y] = 1;
		}
		sp(r, y);
	}
	_ void fd(int& r, int x) {
		int y = r;
		while (ch[y][x > v[y]] && x != v[y]) y = ch[y][x > v[y]];
		sp(r, y);
	}
	_ int pre(int& r, int x, int f) {
		fd(r, x);
		if ((!f && v[r] < x) || (f && v[r] > x)) return r;
		int y = ch[r][f]; while (ch[y][!f]) y = ch[y][!f];
		return y;
	}
	_ void rm(int& r, int x) {
		int y = pre(r, x, 0), z = pre(r, x, 1);
		sp(r, y); sp(r, z, y); int& w = ch[z][0];
		if (c$[w] --> 1) sp(r, w);
		else w = 0;
	}
	_ int kth(int&r, int x) {
		for (int y = r; ; ) {
			if (L(y) && x <= s[L(y)]) y = L(y);
			else if (x > s[L(y)] + c$[y]) {
				x -= s[L(y)] + c$[y];
				y = R(y);
			} else return y;
		}
	}
}

int n, r$, op, x;

int main() {
	$::ins(r$, 0x3f3f3f3f);
	$::ins(r$, 0xcfcfcfcf);
	for (scanf("%d", &n); n--; ) {
		scanf("%d%d", &op, &x);
		switch (op) {
			case 1: $::ins(r$, x); break;
			case 2: $::rm(r$, x); break;
			case 3: $::fd(r$, x); printf("%d\n", $::s[$::ch[r$][0]]); break;
			case 4: printf("%d\n", $::v[$::kth(r$, x+1)]); break;
			case 5: printf("%d\n", $::v[$::pre(r$, x, 0)]); break;
			case 6: printf("%d\n", $::v[$::pre(r$, x, 1)]); break;
		}
	}
}