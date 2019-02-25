#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 55, dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, INF = 0x3f3f3f3f;

int n, x1, y1, x2, y2, dis[N][N], col[N][N], ans = INF;
std::queue<pii> q;
char a[N][N];
int main() {
	scanf("%d%d%d%d%d", &n, &x1, &y1, &x2, &y2);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= n; j++) a[i][j] = a[i][j] == '0';
	}
	memset(dis, 0x3f, sizeof dis);
	dis[x1][y1] = 0;
	for (q.push(pii(x1, y1)); !q.empty(); q.pop()) {
		int x = q.front().first, y = q.front().second;
		col[x][y] = 1;
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (1 <= std::min(nx, ny) && std::max(nx, ny) <= n && a[nx][ny] && dis[nx][ny] == INF) {
				dis[nx][ny] = dis[x][y] + 1;
				q.push(pii(nx, ny));
			}
		}
	}
	if (dis[x2][y2] != INF) return puts("0"), 0;
	dis[x2][y2] = 0;
	for (q.push(pii(x2, y2)); !q.empty(); q.pop()) {
		int x = q.front().first, y = q.front().second;
		col[x][y] = 2;
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (1 <= std::min(nx, ny) && std::max(nx, ny) <= n && a[nx][ny] && dis[nx][ny] == INF) {
				dis[nx][ny] = dis[x][y] + 1;
				q.push(pii(nx, ny));
			}
		}
	}
	for (int a1 = 1; a1 <= n; a1++) {
		for (int b1 = 1; b1 <= n; b1++) {
			for (int a2 = 1; a2 <= n; a2++) {
				for (int b2 = 1; b2 <= n; b2++) {
					if (dis[a1][b1] != INF && dis[a2][b2] != INF && col[a1][b1] == 1 && col[a2][b2] == 2) {
						ans = std::min(ans, (a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
					}
				}
			}
		}
	}
	printf("%d", ans);
}