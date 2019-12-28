#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

typedef std::pair<int, int> pii;

const int N = 2e5 + 52, M = 5e4 + 45;

int n, m, c[N], ptr[N];
pii ans[M], p[26][M];
char s[N], t[N];
int main() {
	scanf("%d%s%d", &n, s, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%s", t);
		int l = strlen(t);
		for (int j = 0; j < l; j++) c[t[j] - 'a']++;
		for (int j = 0; j < 26; j++) p[j][i] = {c[j], i};
		memset(c, 0, sizeof c);
	}
#define _ p[j][ptr[j] + 1]
	for (int i = 0; i < 26; i++) std::sort(p[i] + 1, p[i] + m + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 26; j++) {
			for (; ptr[j] <= m && _.first == c[j]; ptr[j]++)
				if (++ans[_.second].second == 26) ans[_.second].first = i;
		}
		c[s[i] - 'a']++;
	}
	for (int j = 0; j < 26; j++) {
		for (; ptr[j] <= m && _.first == c[j]; ptr[j]++)
			if (++ans[_.second].second == 26) ans[_.second].first = n;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i].first);
}