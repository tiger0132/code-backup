#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51;

int n, tr[N];
void add(int i, int x) {
	for (; i <= n; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (; i; i -= i & -i) r += tr[i];
	return r;
}

int x, ans, tmp, c, last[N], cnt[N];
std::queue<int> q;
signed main() {
	scanf("%d", &n), n <<= 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		if (!cnt[x]++)
			add(last[x] = i, 1);
		else if (cnt[x] == 2) {
			add(last[x], -1);
			ans += tmp = qry(i) - qry(last[x]);
			for (int j = i - 1; tmp--; j--) q.push(j - c);
			c += 2;
		}
	}
	printf("%d\n", ans);
	while (!q.empty()) printf("%d\n", q.front()), q.pop();
}