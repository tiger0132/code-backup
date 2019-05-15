#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, M = 1e5 + 51;
void Z(char *s, int n, int *z, int *a, int sz, bool f) {
	memset(z, -1, N << 2), memset(a, -1, N << 2);
	int delim = 0;
	for (int i = 1, l = 0, r = 0; i < n; i++, r--) {
		if (i > r) {
			l = r = i;
			while (r < n && s[r - l] == s[r]) r++;
			z[i] = r - l;
		} else {
			int cur = i - l;
			if (i + z[cur] - 1 < r)
				z[i] = z[cur];
			else {
				l = i;
				while (r < n && s[r] == s[r - l]) r++;
				z[i] = r - l;
			}
		}
		if (s[i] == '|') delim = i;
		if (delim && z[i] && a[z[i]] == -1) a[z[i]] = f ? i - delim - 1 : n - i - 1;
		// if (!delim) z[i] = 0;
	}
	for (int i = 1; i < n; i++) printf("%d%c", a[i], " \n"[i == n - 1]);
}

char buf[N], *s = buf + M, t[M];
int n, m, ans, z1[N], z2[N], pre[N], suf[N];
int main() {
	scanf("%s%d", s, &m), n = strlen(s), *(s - 1) = '|';
	for (int i = 1; i <= m; i++) {
		scanf("%s", t);
		int sz = strlen(t);
		if (sz == 1) continue;
		char *p = s - sz - 1;
		memcpy(p, t, sz);
		Z(p, sz + 1 + n, z1, pre, sz, 1);
		std::reverse(p, p + sz);
		std::reverse(s, s + n);
		Z(p, sz + 1 + n, z2, suf, sz, 0);
		std::reverse(s, s + n);
		for (int j = sz; j >= 0; j--) {
			printf("%c %d %d\n", p[j], pre[j], suf[j]);
			if (suf[j + 1] != -1) {
				if (suf[j] == -1)
					suf[j] = suf[j + 1];
				else
					suf[j] = std::max(suf[j], suf[j + 1]);
			}
			if (pre[j + 1] != -1) {
				if (pre[j] == -1)
					pre[j] = pre[j + 1];
				else
					pre[j] = std::min(pre[j], pre[j + 1]);
			}
		}
		if (suf[sz] != -1 || pre[sz] != -1)
			ans++;
		else
			for (int j = 1; j < sz; j++) {
				if (pre[j] != -1 && suf[sz - j] != -1 && pre[j] + sz - 1 <= suf[sz - j]) {
					ans++;
					break;
				}
			}
	}
	printf("%d", ans);
}