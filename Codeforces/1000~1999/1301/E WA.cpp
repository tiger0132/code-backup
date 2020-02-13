#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e2 + 24, M = 33;

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void l(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

char s[N], t[N];
int nxt[N][M];
int n, m;
int main() {
	for (scanf("%*d"); ~scanf("%s%s", s + 1, t + 1);) {
		memset(p, 0, sizeof p);
		n = strlen(s + 1);
		m = strlen(t + 1);
		for (int i = 0; i < 26; i++) nxt[n + 1][i] = nxt[n + 2][i] = n + 1;
		for (int i = n; i >= 1; i--) {
			for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
			nxt[i][s[i] - 'a'] = i;
		}
		int pt = 0;
		for (int i = 1; i <= m; i++) {
			pt = nxt[pt + 1][s[i] - 'a'];
			l(pt, nxt[pt + 1][s[i] - 'a']);
			if (pt > n) break;
			int pt2 = 0;
			for (int j = i + 1; j <= m; j++) {
				pt2 = f(nxt[pt2 + 1][s[j] - 'a']);
				if (pt2 > n) goto mmp;
			}
			printf("i = %d\n", i);
			goto end;
		mmp:;
		}
		puts("NO");
		continue;
	end:;
		puts("YES");
	}
}