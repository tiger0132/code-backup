#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e5 + 51;

std::map<int, int> mp;
int sz;
int id(int x) {
	if (!mp.count(x)) return mp[x] = ++sz;
	return mp[x];
}

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int n, a[N], b[N], ans, fl = 1;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[n + 1] ^= a[i];
	for (int i = 1; i <= n; i++) scanf("%d", b + i), b[n + 1] ^= b[i];
	for (int i = 1, x, y; i <= n; i++)
		if (a[i] != b[i]) {
			ans++;
			if ((x = f(id(a[i]))) != (y = f(id(b[i])))) x[p] = y;
			if (a[i] == a[n + 1] && fl) ans--, fl = 0;
			if (b[i] == b[n + 1] && fl) ans--, fl = 0;
			if (a[i] == b[n + 1] && fl) ans--, fl = 0;
			if (b[i] == a[n + 1] && fl) ans--, fl = 0;
		}
	std::sort(a + 1, a + n + 2);
	std::sort(b + 1, b + n + 2);
	for (int i = 1; i <= n + 1; i++)
		if (a[i] != b[i]) return puts("-1"), 0;
	for (int i = 1; i <= sz; i++) ans += !i[p];
	printf("%d", ans);
}