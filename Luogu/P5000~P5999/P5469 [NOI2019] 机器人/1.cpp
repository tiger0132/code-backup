#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 6e2 + 26, P = 1e9 + 7;

struct Z {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	Z() { x = 0; }
	Z(int v) : x(v) {}
	Z(long long v) : x(v) {}
	Z(char v) : x(v) {}
	Z operator+(const Z& rhs) const { return norm(x + rhs.x - P); }
	Z operator-(const Z& rhs) const { return norm(x - rhs.x); }
	Z operator-() const { return norm(-x); }
	Z operator*(const Z& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (L)x * rhs.x % P; }
};
Z pw(Z x, int y) {
	Z r = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

Z fac[N], ifac[N];
void init() {
	0 [fac] = 0 [ifac] = 1;
	for (int i = 1; i < N; i++) i[fac] = (i - 1)[fac] * i;
	ifac[N - 1] = pw(fac[N - 1], P - 2);
	for (int i = N - 2; i; i--) i[ifac] = (i + 1)[ifac] * (i + 1);
}
inline Z pm(int x) { return x & 1 ? P - 1 : 1; }

Z dif[N][N];
struct poly {
	std::vector<Z> v;  // v[i] = F(i)
	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(std::vector<Z> nv) : v(nv) {}
	inline int size() const { return v.size(); }
	inline void resize(int n) { return v.resize(n); }
	inline Z operator[](int i) const { return v[i]; }
	inline Z& operator[](int i) { return v[i]; }
	void expand(int sz) {  // 扩点值~
		int n = size();
		resize(sz);
		if (sz <= n) return;
		for (int i = 0; i < n; i++) dif[0][i] = v[i];
		for (int i = 1; i < n; i++)
			for (int j = i; j < n; j++) dif[i][j] = dif[i - 1][j] - dif[i - 1][j - 1];
		for (int i = n; i < sz; i++) {
			dif[n - 1][i] = dif[n - 1][i - 1];
			for (int j = n - 2; j >= 0; j--) dif[j][i] = dif[j][i - 1] + dif[j + 1][i];
			v[i] = dif[0][i];
		}
	}
	poly operator+(const poly& rhs) const {
		poly ret(std::max(size(), rhs.size()));
		int len = std::min(size(), rhs.size());
		for (int i = 0; i < len; i++) ret[i] = v[i] + rhs[i];
		for (int i = len; i < size(); i++) ret[i] = v[i];
		for (int i = len; i < rhs.size(); i++) ret[i] = rhs[i];
		return ret;
	}
	poly operator*(poly rhs) const {  // should expand; it's a * shr(b)
		int len = size() + rhs.size();
		poly lhs(v), ret(len);
		lhs.expand(len), rhs.expand(len - 1);
		for (int i = 1; i < len; i++) ret[i] = lhs[i] * rhs[i - 1];	 // note rhs[i - 1]
		return ret;
	}
	Z operator()(int x, int d) const {	// d is offset
		Z ret;
		int n = size();
		std::vector<Z> tmp(n + 1);
		Z qwq = 1;
		tmp[n] = 1;
		for (int i = n - 1; i >= 0; i--) tmp[i] = tmp[i + 1] * Z::norm(x - i - d);
		for (int i = 0; i < n; i++) {
			ret += v[i] * qwq * tmp[i + 1] * pm(n - i - 1) * ifac[i] * ifac[n - i - 1];
			qwq *= Z::norm(x - i - d);
		}
		return ret;
	}
	void psum() {
		for (int i = 1; i < size(); i++) v[i] += v[i - 1];
		// v.push_back(operator()(size(), 0));
	}
} f[2525];

int n, last, pos, a[N], b[N];
int id[N][N], cnt;
bool vis[N][N];
void dfs0(int l, int r) {
	if (id[l][r]) return;
	id[l][r] = ++cnt;
	if (l <= r)
		for (int i = l; i <= r; i++)
			if (abs(i + i - l - r) <= 2) dfs0(l, i - 1), dfs0(i + 1, r);
}
void dfs(int l, int r) {
	if (vis[l][r]) return;
	vis[l][r] = true;
	if (l > r) {
		f[id[l][r]].resize(1);
		f[id[l][r]][0] = 1;
	} else {
		Z t = f[id[l][r]](pos, last);
		f[id[l][r]].resize(1);
		f[id[l][r]][0] = t;
		for (int i = l; i <= r; i++)
			if (abs(i + i - l - r) <= 2 && (a[i] <= pos && pos < b[i])) {
				dfs(l, i - 1), dfs(i + 1, r);
				f[id[l][r]] = f[id[l][r]] + f[id[l][i - 1]] * f[id[i + 1][r]];
			}
	}
	f[id[l][r]].psum();
	f[id[l][r]].expand(r - l + 2);
	// if (f[id[l][r]].size() > r - l + 4)
	// 	printf("[%d, %d] (%d): %d\n", l, r, pos, f[id[l][r]].size());
	// printf("[%d, %d] (%d): ", l, r, pos);
	// for (Z i : f[id[l][r]].v) printf("%d ", i.x);
	// puts("");
}

std::vector<int> k;
int main() {
	init();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", a + i, b + i);
		k.push_back(a[i]);
		k.push_back(++b[i]);
	}
	std::sort(k.begin(), k.end());
	k.erase(std::unique(k.begin(), k.end()), k.end());
	dfs0(1, n);
	for (int i : k) {
		pos = i;
		memset(vis, 0, sizeof vis);
		for (int l = 1; l <= n; l++)
			for (int r = 1; r <= n; r++)
				if (id[l][r]) dfs(l, r);
		last = i;
	}
	printf("%d\n", f[id[1][n]][0].x);
}