#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#define M0(x) memset(x, 0, sizeof x)
#define F first
#define S second

typedef std::pair<int, int> pii;
const int N = 2e3 + 32, SZ = 33;

pii r0[SZ], r1[SZ];
int t, n, m, ub;
char s[N][N];
int main() {
	for (scanf("%d", &t); t--;) {
		M0(r0), M0(r1), ub = -1;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%s", s[i] + 1);
			for (int j = 1; j <= m; j++) {
				if (s[i][j] == '.') continue;
				int c = s[i][j] - 'a';
				ub = std::max(ub, c);
				if (!r0[c].F)
					r0[c] = r1[c] = {i, j};
				else {
					r0[c].F = std::min(r0[c].F, i);
					r0[c].S = std::min(r0[c].S, j);
					r1[c].F = std::max(r1[c].F, i);
					r1[c].S = std::max(r1[c].S, j);
				}
			}
		}
		for (int i = 0; i <= ub; i++)
			if (r0[i].F != r1[i].F && r0[i].S != r1[i].S) {
				puts("NO");
				goto end;
			}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 25; k >= 0; k--) {
					if (r0[k].F <= i && i <= r1[k].F && r0[k].S <= j && j <= r1[k].S) {
						if (k == s[i][j] - 'a') break;
						puts("NO");
						goto end;
					}
				}
			}
		}
		puts("YES");
		printf("%d\n", ub + 1);
		for (int i = ub - 1; i >= 0; i--)
			if (!r0[i].F) r0[i] = r0[i + 1], r1[i] = r1[i + 1];
		for (int i = 0; i <= ub; i++) printf("%d %d %d %d\n", r0[i].F, r0[i].S, r1[i].F, r1[i].S);
	end:;
	}
}