#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 4e5 + 54, M = 2e7 + 72;

int n, tr[M];
void add(int i, int x) {
	for (i++; i < M; i += i & -i) i[tr] += x;
}
int qry(int i) {
	int r = 0;
	for (i++; i > 0; i -= i & -i) r += i[tr];
	return r;
}
int qry(int l, int r) {
	r = std::min(r, (int)1e7);
	if (l > r) return 0;
	return qry(r) - qry(l - 1);
}

int v[N], ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 1; i <= 16777216; i <<= 1) {
		int a = i, b = i << 1, c = i << 2;
		ll cnt = 0;
		memset(tr, 0, std::min(c, int(1e7 + 71)) * 4);
		for (int j = 1; j <= n; j++) {
			int x = v[j] % b;
			cnt += qry(a - x, b - x - 1) + qry(a + b - x, c - x - 2);
			add(x, 1);
		}
		ans += a * (cnt % 2);
	}
	printf("%d", ans);
}