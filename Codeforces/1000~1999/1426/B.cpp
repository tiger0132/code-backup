#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

int n, m;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		bool center = false;
		for (int i = 1, x, y, z, w; i <= n; i++) {
			scanf("%d%d%d%d", &x, &y, &z, &w);
			if (y == z) center = true;
		}
		puts(center && m % 2 == 0 ? "YES" : "NO");
	}
}