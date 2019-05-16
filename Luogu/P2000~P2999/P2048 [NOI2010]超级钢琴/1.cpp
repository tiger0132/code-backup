#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 1e6 + 61, LN = 21;

int n, k, l, r;
pii st[LN][N];
void init() {
	for (int i = 1; (1 << i) <= n; i++) {
		for (int j = 1; j + (1 << i) - 1 <= n; j++) {
			st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
}
int query(int l, int r) {
	int k = log2(r - l + 1);
	return std::max(st[k][l], st[k][r - (1 << k) + 1]).second;
}

int a[N];
struct node {
	int L, l, r, x;
	inline bool operator<(const node& rhs) const { return a[x] - a[L - 1] < a[rhs.x] - a[rhs.L - 1]; }
};

std::priority_queue<node> pq;
long long ans;
int main() {
	scanf("%d%d%d%d", &n, &k, &l, &r);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] += a[i - 1], st[0][i] = pii(a[i], i);
	init();
	for (int i = 1, tl, tr; i <= n - l + 1; i++) {
		tl = i + l - 1, tr = std::min(n, i + r - 1);
		pq.push((node){i, tl, tr, query(tl, tr)});
	}
	while (k--) {
		node x = pq.top();
		ans += a[x.x] - a[x.L - 1], pq.pop();
		if (x.l != x.x) pq.push((node){x.L, x.l, x.x - 1, query(x.l, x.x - 1)});
		if (x.x != x.r) pq.push((node){x.L, x.x + 1, x.r, query(x.x + 1, x.r)});
	}
	printf("%lld", ans);
}