#include <algorithm>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

typedef long long ll;
const int N = 4e5 + 54;
// s1: a1 + a2 + a3 + ...
// s2: a1 + 2*a2 + 3*a3 + ...
// s3: 1*n*a1 + 2*(n-1)*a2 + 3*(n-2)*a3
ll s1[N], s2[N], s3[N], t[N], sz[N];
int ch[N][2], nc;
void up(int x) {
	x[s1] = x[L][s1] + x[R][s1];
	x[s2] = x[L][s2] + x[R][s2] + x[R][s1] * x[L][sz];
	x[s3] = x[L][s3] + x[R][sz] * x[L][s2] + x[R][s3] + x[L][sz] * x[R][s2];
}
void put(int x, int v) {
	x[t] += v;
	x[s1] += x[sz] * v;
	x[s2] += x[sz] * (x[sz] + 1) / 2 * v;
	x[s3] += x[sz] * (x[sz] + 1) / 2 * v;
}
void pd(int x) {
	if (x[t]) put(x[L], x[t]), put(x[R], x[t]), x[t] = 0;
}
void build(int x, int l, int r) {
	x[sz] = r - l + 1;
	if (l < r) build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r);
}
void upd(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && r <= qr) return put(x, v);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, v), up(x);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v), up(x);
}
void qry(int x, int l, int r) {}

int n, m, x, y, z;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	for (; m--;) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'C') {
			scanf("%d", &z);
		}
	}
}