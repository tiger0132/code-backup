#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, K = 2e5 + 52;

int tr[K], k;
void add(int i, int x) {
	for (; i <= k; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (; i; i -= i & -i) r += tr[i];
	return r;
}

int a[N], b[N], c[N], ans[N], tmp[N], cnt[N];
void cdq(int *id, int n) {
	if (n == 1) return;
	int m = n / 2, j = m, p = 0;
	cdq(id, m), cdq(id + m, n - m);
	for (int i = 0; i < m; i++) {
		for (; j[id][b] < i[id][b] && j < n; j++) {
			tmp[p++] = j[id];
			j[id][ans] += qry(j[id][c]);
		}
		tmp[p++] = i[id];
		add(i[id][c], i[id][cnt]);
	}
	for (; j < n; j++) {
		tmp[p++] = j[id];
		j[id][ans] += qry(j[id][c]);
	}
	for (int i = 0; i < m; i++) add(i[id][c], -i[id][cnt]);
	memcpy(id, tmp, n * sizeof(int));
}

int n, id[N], newid[N], top, out[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", a + i, b + i, c + i);
		i[id] = i;
	}
	std::sort(id, id + n, [](int x, int y) {
		return x[a] < y[a] || (x[a] == y[a] && x[b] < y[b]) ||
			   (x[a] == y[a] && x[b] == y[b] && x[c] < y[c]);
	});
	top = 1;
	newid[0] = id[0];
	for (int i = 1; i < n; i++) {
		int x = i[id], y = (top - 1)[newid];
		y[cnt]++;
		if (x[a] != y[a] || x[b] != y[b] || x[c] != y[c]) (top++)[newid] = x;
	}
	(top - 1)[newid][cnt]++;
	cdq(newid, top);
	for (int i = 0; i < top; i++)
		(i[newid][ans] + i[newid][cnt] - 1)[out] += i[newid][cnt];
	for (int i = 0; i < n; i++) printf("%d\n", out[i]);
}

/*
如果只按 ab 排序，不能保证左区间里的 max c <= 右区间里的 min c，不能正确计算贡献

Hack:
2 3
1 1 2
1 1 1
*/