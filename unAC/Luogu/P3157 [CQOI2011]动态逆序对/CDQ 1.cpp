#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int k, r[N];
void add(int i, int x) {
	for (; i <= k; i += i & -i) r[i] += x;
}
void cl(int i) {
	for (; i <= k; i += i & -i) r[i] = 0;
}
int query(int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += r[i];
	return ret;
}

int q[N], ans[N], A[N], B[N], C[N], F[N];
void cdq(int *p, int n) {
	if (n == 1) return;
	int m = n >> 1, top = 0, p1 = 0, p2 = m;
	cdq(p, m);
	cdq(p + m, n - m);
	memcpy(q, p, n << 2);
	while (p1 < m && p2 < n) {
		int x = q[p1], y = q[p2];
		if (B[x] <= B[y]) {
			p[top++] = x, p1++;
			if (!F[x]) add(B[x], );
		} else {
			p[top++] = y, p2++;
		}
	}
}

int n, n$, m, id[N];
void add(int b, int c, int f) { id[n$] = A[n$] = n$, B[n$] = b, C[n$] = c, F[n$] = f, n$++; }

int a[N], b[N], flag[N], lnk[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), flag[a[i]] = 1, lnk[a[i]] = i;
	for (int i = 1; i <= m; i++) scanf("%d", b + i), flag[b[i]] = 0;
	for (int i = 1; i <= n; i++) {  // 权值
		if (flag[i]) add(lnk[i], i, 1);
	}
	for (int i = m; i >= 1; i--) {
		add(lnk[b[i]], b[i], 0);
	}
	cdq(id, n);
}