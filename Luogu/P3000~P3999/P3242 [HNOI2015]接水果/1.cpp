#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, LN = 16;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

struct opr {
	int op, x, y1, y2, k, ofs, *ans;
	// 1, x, y1, y2, k, ofs, 0
	// 2, x, y, 0, k, 0, &ans
};

// 倍增
int fa[N][LN], lb[N], rb[N], dep[N], sz[N], idx;
void dfs(int x, int p, int d) {
	x[sz] = 1, x[lb] = ++idx, x[fa][0] = p, x[dep] = d;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x, d + 1), x[sz] += nx[sz];
	x[rb] = idx;
}
int get(int x, int y) {
	int sub = y[dep] - x[dep] - 1;
	for (int i = LN - 1; i >= 0; i--)
		if ((sub >> i) & 1) y = y[fa][i];
	return y;
}

int n, tr[N];
void add(int i, int x) {
	for (; i <= n; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (; i > 0; i ^= i & -i) r += tr[i];
	return r;
}

// 整体二分
int sv[N];  // 排序之后矩形的权值
void proc(opr* p, int n, int l, int r) {
	static opr q1[N], q2[N];
	if (!n) return;
	if (l == r) {
		for (int i = 0; i < n; i++)
			if (p[i].op == 2) *p[i].ans = sv[l];
		return;
	}
	int mid = (l + r) / 2, p1 = 0, p2 = 0;
	for (int i = 0; i < n; i++)
		if (p[i].op == 1) {
			if (p[i].k <= sv[mid]) {
				add(p[i].y1, p[i].ofs), add(p[i].y2 + 1, -p[i].ofs);
				q1[p1++] = p[i];
			} else
				q2[p2++] = p[i];
		} else {
			int v = qry(p[i].y1);
			if (p[i].k <= v)
				q1[p1++] = p[i];
			else
				p[i].k -= v, q2[p2++] = p[i];
		}
	memcpy(p, q1, sizeof(opr) * p1);
	memcpy(p + p1, q2, sizeof(opr) * p2);
	proc(p, p1, l, mid), proc(p + p1, p2, mid + 1, r);
}

int _m, m, p, q, ans[N];
opr rec[N];
int main() {
	scanf("%d%d%d", &n, &p, &q);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);

	// 倍增预处理
	dfs(1, 1, 0);
	for (int j = 1; j < LN; j++)
		for (int i = 1; i <= n; i++) i[fa][j] = i[fa][j - 1][fa][j - 1];

	// 盘子
	for (int i = 0, x, y, k; i < p; i++) {
		scanf("%d%d%d", &x, &y, &k);
		if (x[lb] > y[lb]) std::swap(x, y);
		if (x[lb] < y[lb] && y[rb] <= x[rb]) {
			int z = get(x, y);
			if (z[lb] > 1) {
				sv[m] = k, rec[m++] = (opr){1, 1, y[lb], y[rb], k, 1, 0};
				sv[m] = k, rec[m++] = (opr){1, z[lb], y[lb], y[rb], k, -1, 0};
			}

			if (z[rb] < n) {
				sv[m] = k, rec[m++] = (opr){1, y[lb], z[rb] + 1, n, k, 1, 0};
				sv[m] = k, rec[m++] = (opr){1, y[rb] + 1, z[rb] + 1, n, k, -1, 0};
			}
		} else {
			sv[m] = k, rec[m++] = (opr){1, x[lb], y[lb], y[rb], k, 1, 0};
			sv[m] = k, rec[m++] = (opr){1, x[rb] + 1, y[lb], y[rb], k, -1, 0};
		}
	}
	_m = m;

	// 果子
	for (int i = 0, x, y, k; i < q; i++) {
		scanf("%d%d%d", &x, &y, &k);
		if (x[lb] > y[lb]) std::swap(x, y);
		rec[m++] = (opr){2, x[lb], y[lb], 0, k, 0, ans + i};
	}

	std::sort(sv, sv + _m);
	std::sort(rec, rec + m, [](const opr& x, const opr& y) {
		return x.x < y.x || (x.x == y.x && x.op < y.op);
	});

	proc(rec, m, 0, _m - 1);
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
