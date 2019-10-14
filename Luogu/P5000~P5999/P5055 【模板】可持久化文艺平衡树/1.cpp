#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// clang-format off
#define L ch][0
#define R ch][1
#define _(a) id[a] = x[a]
typedef long long ll;
const int N = 2e7 + 72;
int ch[N][2], v[N], r[N], pri[N], sz[N], nc;
ll s[N];
void up(int x) { x[sz] = x[L][sz] + x[R][sz] + 1, x[s] = x[L][s] + x[R][s] + x[v]; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
int alloc(int x) {
	int id = ++nc; return id[L] = id[R] = id[r] = 0, id[s] = id[v] = x, id[sz] = 1, id[pri] = rand(), id;
}
int cl(int x) {
	int id = ++nc; return _(L), _(R), _(v), _(s), _(r), _(pri), _(sz), id;
}
void pd(int x) {
	if (!x[r]) return;
	if (x[L]) rv(x[L] = cl(x[L]));
	if (x[R]) rv(x[R] = cl(x[R]));
	x[r] = 0;
}
void spl(int id, int k, int& x, int& y) {
	if (!id) return void(x = y = 0);
	pd(id);
	if (id[L][sz] < k) return x = cl(id), spl(x[R], k - x[L][sz] - 1, x[R], y), up(x);
	y = cl(id), spl(y[L], k, x, y[L]), up(y);
}
int u(int x, int y) {
	if (!x || !y) return x | y;
	pd(x), pd(y);
	if (x[pri] < y[pri]) return x[R] = u(x[R], y), up(x), x;
	return y[L] = u(x, y[L]), up(y), y;
}
void prt(int x) {
	if (x[L]) prt(x[L]);	
	printf("[%d %d]", x[v], x[s]);
	if (x[R]) prt(x[R]);	
}
// clang-format on

int tp, cnt, op, a, b, c, rt[N];
ll x, y, la;
signed main() {
	srand(20081105);
	for (scanf("%*d"); ~scanf("%d%d%lld", &tp, &op, &x);) {
		x ^= la, cnt++;
		if (op == 2) {
			spl(rt[tp], x, b, c);
			spl(b, x - 1, a, b);
			rt[cnt] = u(a, c);
		} else {
			scanf("%lld", &y), y ^= la;
			if (op == 1) {
				spl(rt[tp], x, a, c);
				b = alloc(y);
			} else {
				spl(rt[tp], x - 1, a, b);
				spl(b, y - x + 1, b, c);
				if (op == 3)
					rv(b);
				else
					printf("%lld\n", la = b[s]);
			}
			rt[cnt] = u(u(a, b), c);
		}
	}
}