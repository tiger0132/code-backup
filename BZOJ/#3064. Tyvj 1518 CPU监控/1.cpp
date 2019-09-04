#include <algorithm>
#include <cstdio>
#include <cstring>

// clang-format off
#define L ch][0
#define R ch][1
const int N = 4e5 + 54, INF = 0x3f3f3f3f;
int ch[N][2], l[N], r[N], mid[N], c;
int max[N], add[N], set[N], hmax[N], hadd[N], hset[N];
bool fset[N];
void up(int x) {
	x[max] = std::max(x[L][max], x[R][max]);
	x[hmax] = std::max(x[L][hmax], x[R][hmax]);
}
void addp(int x, int v, int h) {
	x[hadd] = std::max(x[hadd], x[add] + h);
	x[hmax] = std::max(x[hmax], x[max] + h);
	x[add] += v, x[max] += v;
}
void setp(int x, int v, int h) {
	if (x[fset]) 
		x[hset] = std::max(x[hset], h);
	else
		x[fset] = true, x[hset] = h;
	x[hmax] = std::max(x[hmax], h);
	x[set] = x[max] = v;
}
void pd(int x) {
	if (x[L][fset])
		setp(x[L], x[L][set] + x[add], x[L][set] + x[hadd]);
	else
		addp(x[L], x[add], x[hadd]);
	if (x[R][fset])
		setp(x[R], x[R][set] + x[add], x[R][set] + x[hadd]);
	else
		addp(x[R], x[add], x[hadd]);
	if (x[fset]) setp(x[L], x[set], x[hset]), setp(x[R], x[set], x[hset]);
	x[fset] = false, x[add] = x[set] = x[hadd] = x[hset] = 0;
}
void build(int x, int ql, int qr, int* a) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2;
	if (ql == qr) return void(x[max] = x[hmax] = a[ql]);
	build(x[L] = ++c, ql, x[mid], a), build(x[R] = ++c, x[mid] + 1, qr, a), up(x);
}
int qry1(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[max];
	pd(x);
	int ret = -INF;
	if (ql <= x[mid]) ret = std::max(ret, qry1(x[L], ql, qr));
	if (x[mid] < qr) ret = std::max(ret, qry1(x[R], ql, qr));
	return ret;
}
int qry2(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[hmax];
	pd(x);
	int ret = -INF;
	if (ql <= x[mid]) ret = std::max(ret, qry2(x[L], ql, qr));
	if (x[mid] < qr) ret = std::max(ret, qry2(x[R], ql, qr));
	return ret;
}
void upd1(int x, int ql, int qr, int v) {
	if (ql <= x[l] && x[r] <= qr) {
		if (x[fset])
			setp(x, x[set] + v, x[set] + v);
		else
			addp(x, v, v);
		return;
	}
	pd(x);
	if (ql <= x[mid]) upd1(x[L], ql, qr, v);
	if (x[mid] < qr) upd1(x[R], ql, qr, v);
	up(x);
}
void upd2(int x, int ql, int qr, int v) {
	if (ql <= x[l] && x[r] <= qr) return setp(x, v, v);
	pd(x);
	if (ql <= x[mid]) upd2(x[L], ql, qr, v);
	if (x[mid] < qr) upd2(x[R], ql, qr, v);
	up(x);
}
// clang-format on

int n, a[N], m, x, y, z;
char op[2];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	build(c = 1, 1, n, a);
	for (scanf("%d", &m); m--;) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'Q')
			printf("%d\n", qry1(1, x, y));
		else if (*op == 'A')
			printf("%d\n", qry2(1, x, y));
		else if (*op == 'P')
			scanf("%d", &z), upd1(1, x, y, z);
		else
			scanf("%d", &z), upd2(1, x, y, z);
	}
}