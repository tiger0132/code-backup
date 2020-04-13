#include <algorithm>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 4e5 + 54;

int a[N];
struct SGT {
	int ch[N][2], s[N], lmn[N], lmx[N], rmn[N], rmx[N], ld[N], rd[N], d[N], ans[N], nc;
	SGT() { nc = 1; }
	void up(int x) {
		x[s] = x[L][s] + x[R][s];
		x[lmn] = std::min(x[L][lmn], x[L][s] + x[R][lmn]);
		x[lmx] = std::max(x[L][lmx], x[L][s] + x[R][lmx]);
		x[rmn] = std::min(x[L][rmn] + x[R][s], x[R][rmn]);
		x[rmx] = std::max(x[L][rmx] + x[R][s], x[R][rmx]);
		x[ld] = std::max({x[L][ld], x[R][ld] - x[L][s], x[L][d] + x[R][lmx]});
		x[rd] = std::max({x[L][rd] + x[R][s], x[R][rd], x[R][d] - x[L][rmn]});
		x[d] = std::max(x[R][d] - x[L][s], x[L][d] + x[R][s]);
		x[ans] =
			std::max({x[L][ans], x[R][ans], x[R][ld] - x[L][rmn], x[L][rd] + x[R][lmx]});
	}
	void put(int x, int y) {
		x[lmx] = x[rmx] = std::max(y, 0);
		x[lmn] = x[rmn] = std::min(y, 0), x[s] = y;
		x[ld] = x[rd] = x[d] = x[ans] = 1;
	}
	void build(int x, int l, int r) {
		if (l == r) return put(x, a[l]);
		build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), up(x);
	}
	void upd(int x, int l, int r, int i, int y) {
		if (l == r) return a[i] = y, put(x, y);
		(i <= mid ? upd(x[L], l, mid, i, y) : upd(x[R], mid + 1, r, i, y)), up(x);
	}
} sgt;

int n, q, x, y;
char s[N];
int main() {
	scanf("%d%d%s", &n, &q, s + 1), n = 2 * n - 2;
	for (int i = 1; i <= n; i++) a[i] = s[i] == '(' ? 1 : -1;
	sgt.build(1, 1, n);
	for (printf("%d\n", sgt.ans[1]); q--; printf("%d\n", sgt.ans[1])) {
		scanf("%d%d", &x, &y);
		int p = a[x], q = a[y];
		sgt.upd(1, 1, n, x, q);
		sgt.upd(1, 1, n, y, p);
	}
}