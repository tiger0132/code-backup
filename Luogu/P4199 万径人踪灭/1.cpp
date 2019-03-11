#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstring>

using ll = long long;
const double P = acos(-1);
const int N = 3e5 + 53, MOD = 1e9 + 7;

struct comp {
	double x, y;
	inline comp(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	inline comp operator+(const comp& rhs) const { return comp(x + rhs.x, y + rhs.y); }
	inline comp operator-(const comp& rhs) const { return comp(x - rhs.x, y - rhs.y); }
	inline comp operator*(const comp& rhs) const { return comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
};

int l, lim = 1, r[N];
void fft(comp* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		comp wn(cos(P / i), op * sin(P / i));
		for (int j = 0; j < lim; j += (i << 1)) {
			comp w(1);
			for (int k = 0; k < i; k++, w = w * wn) {
				comp x = a[j + k], y = w * a[j + i + k];
				a[j + k] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i <= lim; i++) a[i].x = int(a[i].x / lim + .5);
}

int p[N];
void manacher(char* str, int n) {
	int rb = 0, mid;
	for (int i = 1; i < n; i++) {
		if (i < rb)
			p[i] = std::min(p[2 * mid - i], p[mid] + mid - i);
		else
			p[i] = 1;
		while (str[i + p[i]] == str[i - p[i]]) p[i]++;
		if (p[i] + i > rb) {
			rb = p[i] + i;
			mid = i;
		}
	}
}

int qp(ll x, int y) {
	ll ret = 1;
	for (; y; y >>= 1, (x = x * x % MOD))
		if (y & 1) ret = ret * x % MOD;
	return ret;
}

char src[N], s[N] = "$|";
int n, m = 2, flag[N];
comp a[N], b[N];
ll ans[N], sum;
int main() {
	scanf("%s", src);
	n = strlen(src);
	for (int i = 1; i <= n; i++) flag[i] = src[i - 1] == 'a';
	for (int i = 0; i < n; i++) s[m++] = src[i], s[m++] = '|';
	manacher(s, m);
	while (lim < 2 * n) lim <<= 1, l++;
	for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));

	for (int i = 1; i <= n; i++) a[i].x = b[i].x = flag[i];
	fft(a, 1), fft(b, 1);
	for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 1; i < 2 * (n + 1); i++) ans[i] = a[i].x - (1 & ~i);

	memset(a, 0, sizeof a), memset(b, 0, sizeof b);
	for (int i = 1; i <= n; i++) a[i].x = b[i].x = !flag[i];
	fft(a, 1), fft(b, 1);
	for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 1; i < 2 * (n + 1); i++) ans[i] += a[i].x - (1 & ~i);
	for (int i = 1; i < 2 * (n + 1); i++) ans[i] = (ans[i] + (1 & ~i)) / 2 + (1 & ~i);

	for (int i = 1; i < 2 * (n + 1); i++) {
		ans[i] = (qp(2, ans[i]) + MOD - 1) % MOD;
		ans[i] -= p[i] >> 1;
		ans[i] = (ans[i] % MOD + MOD) % MOD;
		sum = (sum + ans[i]) % MOD;
	}
	printf("%lld", sum);
}