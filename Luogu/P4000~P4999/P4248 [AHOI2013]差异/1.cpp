#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e6 + 61;
void SA(int n, char *s, int *sa, int *ht) {
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
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	int lb = 0;
	for (int i = 1; i <= n; i++) {
		if (!rk[i]) continue;
		lb = std::max(0, lb - 1);
		for (int j = sa[rk[i] - 1]; lb + i <= n && lb + j <= n && s[lb + i] == s[lb + j];) lb++;
		ht[rk[i]] = lb;
	}
}

int n, sa[N], ht[N], lb[N], rb[N];
long long ans;
char s[N];
int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	SA(n, s, sa, ht);
	ht[0] = ht[n + 1] = -1e9;
	ans = n * (n - 1ll) / 2 * (n + 1);
	for (int i = 1; i <= n; i++) lb[i] = i - 1, rb[i] = i + 1;
	for (int i = 2; i <= n; i++)
		while (ht[lb[i]] > ht[i]) lb[i] = lb[lb[i]];
	for (int i = n; i >= 2; i--)
		while (ht[rb[i]] >= ht[i]) rb[i] = rb[rb[i]];
	for (int i = 2; i <= n; i++) ans -= 2ll * ht[i] * ((1ll * rb[i] - i) * (i - lb[i]));
	printf("%lld", ans);
}