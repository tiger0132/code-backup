#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>

const int N = 1e2 + 21, M = 3e4 + 43, INF = 0x3f3f3f3f;

std::deque<int> v[N];
int n, m, x, y, _;
int mx, nxt[N];

int dis(int i, int j) { return (j - i + n) % n; }
int proc(int x) {
	int rnd = mx - 1, dest = 0, pos, cnt = _;
	for (pos = (mx - 1) * n + nxt[x]; pos < dest || cnt < n; pos++) {
		if (mx == v[pos % n].size()) {
			int tmp = v[pos % n][0];
			dest = std::max(dest, tmp += (rnd + (tmp < pos % n)) * n);
			cnt++;
		}
	}
	return dest;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		v[x - 1].push_back(y - 1);
	}
	for (int i = 0; i < n; i++) {
		mx = std::max(mx, (int)v[i].size());
		std::sort(v[i].begin(), v[i].end(), [i](int x, int y) { return dis(i, x) < dis(i, y); });
	}
	for (int i = n - 1; i; i--) {
		if (v[i].size() == mx)
			nxt[i] = i, _++;
		else
			nxt[i] = nxt[i + 1];
	}
	if (v[n - 1].size() < mx) nxt[n - 1] = nxt[1];
	for (int i = 0; i < n; i++) {
		printf("%d ", proc(i));
	}
}