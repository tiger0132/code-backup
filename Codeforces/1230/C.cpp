#include <algorithm>
#include <cstdio>
#include <cstring>

int n, m, x[233], y[233], a[233], g[11][11], lans, ans;
int main() {
	scanf("%d%d", &n, &m);
	if (n < 7) return !printf("%d", m);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i);
	for (a[1] = 1; a[1] <= 6; a[1]++)
		for (a[2] = 1; a[2] <= 6; a[2]++)
			for (a[3] = 1; a[3] <= 6; a[3]++)
				for (a[4] = 1; a[4] <= 6; a[4]++)
					for (a[5] = 1; a[5] <= 6; a[5]++)
						for (a[6] = 1; a[6] <= 6; a[6]++)
							for (a[7] = 1; a[7] <= 6; a[7]++) {
								memset(g, 0, sizeof g);
								lans = 0;
								for (int i = 1; i <= m; i++)
									if (!g[a[x[i]]][a[y[i]]])
										lans++,
											g[a[x[i]]][a[y[i]]] = g[a[y[i]]][a[x[i]]] = 1;
								ans = std::max(ans, lans);
							}
	printf("%d", ans);
}