#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

const int N = 5e5 + 55;

std::vector<int> v[N];
int n, k, c2, cnt;
char s[N], t[N];
signed main() {
	scanf("%lld%lld%s", &n, &k, s + 1);
	for (int i = 1;; i++) {
		memcpy(t, s, sizeof t);
		for (int j = 1; j < n; j++)
			if (s[j] == 'R' && s[j + 1] == 'L')
				v[i].push_back(j), std::swap(t[j], t[j + 1]), c2++;
		if (v[i].empty()) break;
		cnt = i;
		memcpy(s, t, sizeof s);
	}
	if (k > c2 || k < cnt) return puts("-1"), 0;
	for (int i = 1; i <= cnt; i++) {
		if (c2 - k + 1 >= v[i].size()) {
			printf("%d ", v[i].size());
			for (int j : v[i]) printf("%d ", j);
			c2 -= v[i].size(), k--;
			puts("");
		} else {
			printf("%d ", c2 - k + 1);
			for (int j = 0; j < c2 - k + 1; j++) printf("%d ", v[i][j]);
			puts("");
			for (int j = c2 - k + 1; j < v[i].size(); j++) printf("1 %d\n", v[i][j]);
			for (int j = i + 1; j <= cnt; j++)
				for (int k : v[j]) printf("1 %d\n", k);
			break;
		}
	}
}