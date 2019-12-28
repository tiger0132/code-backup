#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

const int N = 1e2 + 21, M = 3e4 + 43;

std::vector<int> v[N];
int n, m, x, y, _;
int c[N], f[M];

int dis(int i, int j) { return (j - i + n) % n; }
int proc(int x) {
	int pos = x, rnd = 0, dest = 0, cnt = _;
	memset(c, 0, sizeof c);
	memset(f, 0, sizeof f);
	for (int i = x; pos < dest || cnt < n; rnd += !(i = ++pos % n)) {
		// printf("pos = %d:\n", pos);
		if (c[i] < v[i].size()) {
			int tmp = v[i][c[i]++];
			dest = std::max(dest, tmp += (rnd + (tmp < i)) * n);
			// printf("get candy %d, dest = %d\n", tmp, dest);
			if (c[i] == v[i].size()) /*printf("cnt++ on %d\n", tmp), */
				f[tmp]++;
		}
		cnt += f[pos];
		// printf("now cnt = %d\n\n", cnt);
	}
	return pos - x - 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		v[x - 1].push_back(y - 1);
	}
	for (int i = 0; i < n; i++) {
		_ += v[i].empty();
		std::sort(v[i].begin(), v[i].end(), [i](int x, int y) { return dis(i, x) > dis(i, y); });
	}
	// printf("%d\n", proc(2));
	// return 0;
	for (int i = 0; i < n; i++) {
		printf("%d ", proc(i));
	}
}