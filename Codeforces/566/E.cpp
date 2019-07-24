#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31;
std::bitset<N> d2[N], g[N], tmp, mask;
int n, x, y, z, c, p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void m(int x, int y) { (x = f(x)) ^ (y = f(y)) && (x[p] = y); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (scanf("%d", &x); x--;) scanf("%d", &y), d2[i][y] = 1;
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			if ((tmp = d2[i] & d2[j]).count() == 2) {
				x = tmp._Find_first(), y = tmp._Find_next(x);
				if (f(x) ^ f(y))
					m(x, y), printf("%d %d\n", x, y), g[x][x] = g[x][y] = g[y][y] = g[y][x] = mask[x] = mask[y] = 1, c++;
			}
	if (!c) {
		for (int i = 2; i <= n; i++) printf("1 %d\n", i);
		return 0;
	} else if (c == 1) {
		for (int i = 1; i <= n; i++)
			if (d2[i].count() < n) {
				for (int j = 1; j <= n; j++)
					if (!mask[j]) printf("%d %d\n", d2[i][j] ? x : y, j);
				break;
			}
		return 0;
	}
	for (int i = 1; i <= n; i++)
		if (!mask[i]) {
			int mn = 1 << 30;
			for (int j = 1; j <= n; j++)
				if (d2[j][i] && (d2[j] & mask).count() < mn) mn = (tmp = d2[j] & mask).count();
			for (int j = 1; j <= n; j++)
				if (tmp[j] && g[j] == tmp) printf("%d %d\n", j, i);
		}
}