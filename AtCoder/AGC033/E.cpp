#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef long long L;
const int N = 2e5 + 52, P = 1e9 + 7;

struct mod_t {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	mod_t() {}
	mod_t(int v) : x(v) {}
	mod_t(long long v) : x(v) {}
	mod_t(char v) : x(v) {}
	mod_t operator+(const mod_t& rhs) const { return norm(x + rhs.x - P); }
	mod_t operator-(const mod_t& rhs) const { return norm(x - rhs.x); }
	mod_t operator*(const mod_t& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const mod_t& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const mod_t& rhs) { norm2(x -= rhs.x); }
	void operator*=(const mod_t& rhs) { x = (L)x * rhs.x % P; }
} f[N];

int n, m, l, mn, cur = 1;
char s[N];
void solve() {
	mod_t sum = f[0] = 1, ans = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = sum;
		sum += f[i - 1];
	}
	for (int i = 0; i < n - 1; i++) ans += f[i] * (n - i);
	printf("%d\n", ans.x);
}
int main() {
	scanf("%d%d%s", &n, &m, s + 1), mn = n;
	for (int i = 1, fl = 1; i <= m; i++)
		if (s[i] == s[1])
			cur++;
		else {
			if (cur && (fl || cur % 2)) mn = std::min(mn, cur);
			cur = fl = 0;
		}
	if (cur > m) return solve(), 0;

	mod_t sum = f[0] = 1, ans = 0;
	mn++;
	for (int i = 2; i <= n; i++) {
		if (i >= mn + 1) sum -= f[i - mn - 1];
		if (i % 2 == 0) sum += f[i] = sum;
	}
	for (int i = 0; i <= n; i++)
		if (n - i <= mn && (n - i) % 2 == 0) ans += f[i] * (n - i);
	printf("%d\n", ans.x);
}