#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62;

void getZ(char *s, int *z) {
	int n = strlen(s);
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) z[i] = std::min(z[i - l], r - i + 1);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

struct {
	long long tr[N * 2];
	void add(int i, int x) {
		for (i++; i < N; i += i & -i) tr[i] += x;
	}
	long long qry(int i) {
		long long r = 0;
		for (i++; i > 0; i -= i & -i) r += tr[i];
		return r;
	}
} b1, b2;

int n, m, saz[N], sbz[N], *za, *zb;
char a[N], b[N], sa[N], sb[N];
long long ans;
int main() {
	scanf("%d%d%s%s%s", &n, &m, a, b, sb);
	strcpy(sa, sb);
	std::reverse(sb, sb + m);
	sa[m - 1] = sb[m - 1] = '#';
	std::reverse(b, b + n);
	strcat(sa, a), strcat(sb, b);
	getZ(sa, saz), getZ(sb, sbz);
	za = saz + m;
	zb = sbz + m;
	std::reverse(zb, zb + n);
	for (int j = 0; j < m - 1; j++) b1.add(zb[j], 1), b2.add(zb[j], zb[j]);
	for (int i = 0; i < n; i++) {
		long long v1 = b1.qry(N - 1) - b1.qry(m - za[i] - 1);
		long long v2 = b2.qry(N - 1) - b2.qry(m - za[i] - 1);

		ans += v1 * (za[i] - m + 1ll) + v2;

		b1.add(zb[i], -1), b2.add(zb[i], -zb[i]);
		if (i + m - 1 < n) b1.add(zb[i + m - 1], 1), b2.add(zb[i + m - 1], zb[i + m - 1]);
	}
	printf("%lld\n", ans);
}