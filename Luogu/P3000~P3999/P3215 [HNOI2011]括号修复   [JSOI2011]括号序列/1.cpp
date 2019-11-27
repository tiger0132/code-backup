#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 1e5 + 51, M = 4e5 + 54;
int s[M], lmx[M], lmn[M], rmx[M], rmn[M], sz[M], v[M];
int ch[M][2], p[M], Ts[M], Tr[M], Ti[M], Rt, nc;
void up(int x) {
	x[s] = x[L][s] + x[v] + x[R][s];
	x[lmx] = std::max(x[L][lmx], x[L][s] + x[v] + x[R][lmx]);
	x[lmn] = std::min(x[L][lmn], x[L][s] + x[v] + x[R][lmn]);
	x[rmx] = std::max(x[L][rmx] + x[v] + x[R][s], x[R][rmx]);
	x[rmn] = std::min(x[L][rmn] + x[v] + x[R][s], x[R][rmn]);
	x[sz] = x[L][sz] + x[R][sz] + 1;
}
void set(int x, int y) {
	x[s] = y * x[sz], x[v] = y;
	x[lmx] = x[rmx] = std::max(x[s], 0);
	x[lmn] = x[rmn] = std::min(x[s], 0);
	x[Ts] = y, x[Tr] = x[Ti] = 0;
}
void inv(int x) {
	std::swap(x[lmx], x[lmn]), std::swap(x[rmx], x[rmn]);
	x[lmx] = -x[lmx], x[lmn] = -x[lmn], x[rmx] = -x[rmx], x[rmn] = -x[rmn];
	x[s] = -x[s], x[v] = -x[v];
	x[Ts] ? x[Ts] = -x[Ts] : x[Ti] ^= 1;
}
void rev(int x) {
	if (x[Ts]) return;
	std::swap(x[lmx], x[rmx]), std::swap(x[lmn], x[rmn]), std::swap(x[L], x[R]);
	x[Tr] ^= 1;
}
void pd(int x) {
	if (x[Ts]) set(x[L], x[Ts]), set(x[R], x[Ts]);
	if (x[Tr]) rev(x[L]), rev(x[R]);
	if (x[Ti]) inv(x[L]), inv(x[R]);
	x[Ts] = x[Ti] = x[Tr] = 0;
}
bool c(int x) { return x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = ch[x][!k];
	ch[z][c(y)] = x, p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x, int g = 0) {
	for (int y; (y = x[p]) != g; rt(x)) y[p] != g && (rt(c(x) == c(y) ? y : x), 0);
	g || (Rt = x);
}
int kth(int x, int k) {
	if (pd(x), (x[L] && k <= x[L][sz])) return kth(x[L], k);
	return k == x[L][sz] + 1 ? x : kth(x[R], k - x[L][sz] - 1);
}
int spl(int ql, int qr) {
	int pp = kth(Rt, ql), qq = kth(Rt, qr + 2);
	return sp(pp), sp(qq, pp), qq;
}
int alloc(int y) {
	return ++nc, nc[L] = nc[R] = nc[p] = 0, nc[sz] = 1, set(nc, y), nc[Ts] = 0, nc;
}
int build(int ql, int qr, char* str) {
	if (ql > qr) return 0;
	int m = (ql + qr) / 2, x = alloc(str[m] == '(' ? 1 : -1);
	if (ql == qr) return x;
	if (x[L] = build(ql, m - 1, str)) x[L][p] = x;
	if (x[R] = build(m + 1, qr, str)) x[R][p] = x;
	return up(x), x;
}

char str[N], op[11], z[2];
int n, m, x, y;
int main() {
	scanf("%d%d%s", &n, &m, str + 2);
	Rt = build(1, n + 2, str);
	while (m--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'R') {
			scanf("%s", z);
			int id = spl(x, y);
			set(id[L], *z == '(' ? 1 : -1), up(id), up(Rt);
		} else if (*op == 'Q') {
			int id = spl(x, y)[L];
			printf("%d\n", (-id[lmn] + 1) / 2 + (id[rmx] + 1) / 2);
		} else if (*op == 'I') {
			int id = spl(x, y);
			inv(id[L]), up(id), up(Rt);
		} else {
			int id = spl(x, y);
			rev(id[L]), up(id), up(Rt);
		}
	}
}