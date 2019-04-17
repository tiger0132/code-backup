#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;
void SA(int n, char *s, int *sa) {
	static int rk[N], v[N], tmp[N], m = 127;
	for (int i = 1; i <= n; i++) rk[i] = s[i], v[i] = i;
	for (int i = 1; i <= n; i++) tmp[rk[v[i]]]++;
	for (int i = 1; i <= m; i++) tmp[i] += tmp[i - 1];
	for (int i = n; i >= 1; i--) sa[tmp[rk[v[i]]]--] = v[i];
	for (int k = 1, p; k <= n && p < n; k <<= 1) {
		p = 0;
		for (int i = n - k + 1; i <= n; i++) v[++p] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) v[++p] = sa[i] - k;
		memset(tmp, 0, sizeof tmp);
		for (int i = 1; i <= n; i++) tmp[rk[v[i]]]++;
		for (int i = 1; i <= m; i++) tmp[i] += tmp[i - 1];
		for (int i = n; i >= 1; i--) sa[tmp[rk[v[i]]]--] = v[i], v[i] = 0;
		std::swap(rk, v), rk[sa[1]] = 1, p = 1;
		for (int i = 2; i <= n; i++) rk[sa[i]] = (v[sa[i]] == v[sa[i - 1]] && v[sa[i] + k] == v[sa[i - 1] + k]) ? p : ++p;
		m = p;
	}
}

int n, sa[N];
char s[N];
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = n + 1; i <= 2 * n; i++) s[i] = s[i - n];
	SA(n *= 2, s, sa);
	for (int i = 1; i <= n; i++)
		if (sa[i] <= n / 2) putchar(s[sa[i] + n / 2 - 1]);
}