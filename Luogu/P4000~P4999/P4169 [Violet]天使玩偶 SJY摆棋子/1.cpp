#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62, K = 1e6 + 61;
int tr[K];
void upd(int i, int x) {
	for (; i < K; i += i & -i) tr[i] = std::max(tr[i], x);
}
void del(int i) {
	for (; i < K; i += i & -i) tr[i] = 0xc0c0c0c0;
}
int qry(int i) {
	int r = 0xc0c0c0c0;
	for (; i; i -= i & -i) r = std::max(r, tr[i]);
	return r;
}

int op[N], x[N], y[N], ans[N], tmp[N];
void cdq(int *id, int n) {
	if (n == 1) return;
	int m = n / 2, j = m, p = 0;
	cdq(id, m), cdq(id + m, n - m);
	for (int i = 0; i < m; i++) {
		for (; j[id][x] < i[id][x] && j < n; j++) {
			if (j[id][op] == 2)
				j[id][ans] = std::min(j[id][ans], j[id][x] + j[id][y] - qry(j[id][y]));
			tmp[p++] = j[id];
		}
		if (i[id][op] == 1) upd(i[id][y], i[id][x] + i[id][y]);
		tmp[p++] = i[id];
	}
	for (; j < n; j++) {
		if (j[id][op] == 2)
			j[id][ans] = std::min(j[id][ans], j[id][x] + j[id][y] - qry(j[id][y]));
		tmp[p++] = j[id];
	}
	for (int i = 0; i < m; i++)
		if (i[id][op] == 1) del(i[id][y]);
	memcpy(id, tmp, n * sizeof(int));
}

int id[N], mx, my;
int n, m;
int main() {
	memset(ans, 0x3f, sizeof ans);
	memset(tr, 0xc0, sizeof tr);
	scanf("%d%d", &n, &m), m += n;
	for (int i = 0; i < m; i++) {
		i[id] = i, i[op] = 1;
		if (i >= n) scanf("%d", i + op);
		scanf("%d%d", i + x, i + y), i[x]++, i[y]++;
		mx = std::max(mx, i[x]);
		my = std::max(my, i[y]);
	}
	mx++, my++;
	cdq(id, m);
	for (int i = 0; i < m; i++) i[id] = i, i[y] = my - i[y], std::swap(i[x], i[y]);
	cdq(id, m);
	for (int i = 0; i < m; i++) i[id] = i, i[y] = mx - i[y], std::swap(i[x], i[y]);
	cdq(id, m);
	for (int i = 0; i < m; i++) i[id] = i, i[y] = my - i[y], std::swap(i[x], i[y]);
	cdq(id, m);
	for (int i = 0; i < m; i++)
		if (i[op] == 2) printf("%d\n", i[ans]);
}