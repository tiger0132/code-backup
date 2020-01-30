#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, m, nxt[N][26], ans;
char s[N], t[N];
int main() {
	for (scanf("%*d"); ~scanf("%s%s", s + 1, t + 1);) {
		n = strlen(s + 1), m = strlen(t + 1), ans = 0;
		for (int i = n; i >= 1; --i) {
			for (int j = 0; j < 26; ++j) nxt[i - 1][j] = nxt[i][j];
			nxt[i - 1][s[i] -= 'a'] = i;
		}
		int p = 1;
		for (int i = 1; i <= m; i++) {
			if (nxt[p][s[i]])
				p = nxt[p][s[i]];
			else {
				ans++;
				p = nxt[0][s[i]];
				if (!p) {
					puts("-1");
					goto end;
				}
			}
		}
		printf("%d\n", ans);
	end:;
	}
}