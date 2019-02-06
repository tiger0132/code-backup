#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

typedef std::tuple<int, int, int, int> t4;
const int N = 22, M = 1024, dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}, INF = 0x3f3f3f3f;

int n, m, p, k, a, b, c, d, e_, lv, x, y, ans = INF;
int key[N][N], wall[N][N][4], vis[M][N][N];
std::queue<t4> q;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &p, &k); k--;) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &e_);
		if (!e_--) e_ = 11;
		for (int i = 0; i < 4; i++) {
			if (c == a + dir[i][0] && d == b + dir[i][1]) {
				wall[a][b][i] = 1 << e_;
				wall[c][d][i ^ 1] = 1 << e_;
				continue;
			}
		}
	}
	for (scanf("%d", &k); k--; key[a][b] |= 1 << (c - 1)) scanf("%d%d%d", &a, &b, &c);
	q.emplace(0, 1, 1, key[1][1]);
	while (!q.empty()) {
		std::tie(lv, x, y, d) = q.front(), q.pop();
		if (x == n && y == m) return !printf("%d", d);
		for (int i = 0; i < 4; i++) {
			if ((wall[x][y][i] & lv) != wall[x][y][i]) continue;
			int nx = x + dir[i][0], ny = y + dir[i][1], nlv = lv | key[nx][ny];
			if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
			if (!vis[nlv][nx][ny]) {
				vis[nlv][nx][ny] = 1;
				q.emplace(nlv, nx, ny, d + 1);
			}
		}
	}
	puts("-1");
}