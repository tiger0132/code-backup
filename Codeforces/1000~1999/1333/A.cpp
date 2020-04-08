#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

int n, m;

int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);)
		for (int i = 0; i < n; i++, puts(""))
			for (int j = 0; j < m; j++)
				putchar((i + j) % 2 && !(!i && j == 1 && (n * m) % 2 == 0) ? 'W' : 'B');
}