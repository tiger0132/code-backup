#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 51;

int a[N], b[N], c[N], pos[N], ans[N];
std::vector<int> fail[N];
int n, m;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		int patch = 0;

		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = 1; i <= n; i++) scanf("%d", b + i);
		for (int i = 1; i <= m; i++) scanf("%d", c + i);
		for (int i = 1; i <= n; i++) {
			fail[i].clear();
			pos[i] = 0;
		}
		for (int i = 1; i <= n; i++)
			if (a[i] != b[i])
				fail[b[i]].push_back(i);
			else
				pos[b[i]] = i;
		for (int i = m; i >= 1; i--)
			if (!fail[c[i]].empty()) {
				ans[i] = patch = fail[c[i]].back();
				fail[c[i]].pop_back();
			} else if (pos[c[i]])
				ans[i] = patch = pos[c[i]];
			else if (patch)
				ans[i] = patch;
			else
				goto no;
		for (int i = 1; i <= n; i++)
			if (!fail[i].empty()) goto no;
		puts("YES");
		for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
		continue;
	no:
		puts("NO");
	}
}