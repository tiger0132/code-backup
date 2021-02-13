#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31;

char g[N][N];
int n, m;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		for (int i = 1; i <= n; i++) scanf("%s", g[i] + 1);
		if (m % 2) {
			puts("YES");
			for (int i = 1; i <= m + 1; i++) printf("%d%c", 2 - i % 2, " \n"[i == m + 1]);
			continue;
		}
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (g[i][j] == g[j][i]) {
					puts("YES");
					for (int k = 1; k <= m + 1; k++)
						printf("%d%c", k % 2 ? i : j, " \n"[k == m + 1]);
					goto end;
				}
		for (int i = 1; i <= n; i++) {
			int ai = 0, ao = 0, bi = 0, bo = 0;
			for (int j = 1; j <= n; j++)
				if (i != j) {
					if (g[j][i] == 'a') ai = j;
					if (g[i][j] == 'a') ao = j;
					if (g[j][i] == 'b') bi = j;
					if (g[i][j] == 'b') bo = j;
				}
			if ((!ai || !bo) && (bi && bo)) ai = bi, ao = bo;
			if (ai && ao) {
				int cyc = m / 2;
				puts("YES");
				if (cyc % 2) {
					for (int j = 1; j <= cyc / 2 + 1; j++) printf("%d %d ", ai, i);
					for (int j = 1; j <= cyc / 2; j++) printf("%d %d ", ao, i);
					printf("%d\n", ao);
				} else {
					for (int j = 1; j <= cyc / 2; j++) printf("%d %d ", i, ai);
					for (int j = 1; j <= cyc / 2; j++) printf("%d %d ", i, ao);
					printf("%d\n", i);
				}
				goto end;
			}
		}
		puts("NO");
	end:;
	}
}