#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long ll;
const int N = 1e5 + 51;

struct node {
	int x, y, z;
	bool operator<(const node& r) const { return x < r.x; }
} p[N];

struct query {
	int x, y1, y2, op;
	ll* ans;
	bool operator<(const query& r) const { return x < r.x; }
} q[N << 1];

ll bit[N * 3];
int n, top;
void add(int i, int x) {
	for (; i <= top; i += i & -i) bit[i] += x;
}
ll qry(int i) {
	ll r = 0;
	for (; i > 0; i -= i & -i) r += bit[i];
	return r;
}

int m, x1, y1, x2, y2, b[N * 3];
ll ans[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z), b[++top] = p[i].y;
	std::sort(p + 1, p + n + 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (y1 > y2) std::swap(y1, y2);
		q[i * 2 - 1] = (query){x1 - 1, y1, y2, -1, ans + i};
		q[i * 2] = (query){x2, y1, y2, 1, ans + i};
		b[++top] = y1, b[++top] = y2;
	}
	std::sort(b + 1, b + top + 1);
	for (int i = 1; i <= n; i++)
		p[i].y = std::lower_bound(b + 1, b + top + 1, p[i].y) - b;
	for (int i = 1; i <= 2 * m; i++) {
		q[i].y1 = std::lower_bound(b + 1, b + top + 1, q[i].y1) - b;
		q[i].y2 = std::lower_bound(b + 1, b + top + 1, q[i].y2) - b;
	}
	std::sort(q + 1, q + 2 * m + 1);
	int j = 1;
	for (int i = 1; i <= n; i++) {
		int x = p[i].x, y = p[i].y, z = p[i].z;
		for (; q[j].x < x && j <= 2 * m; j++)
			*q[j].ans += q[j].op * (qry(q[j].y2) - qry(q[j].y1 - 1));
		add(y, z);
	}
	for (; j <= 2 * m; j++) *q[j].ans += q[j].op * (qry(q[j].y2) - qry(q[j].y1 - 1));
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}