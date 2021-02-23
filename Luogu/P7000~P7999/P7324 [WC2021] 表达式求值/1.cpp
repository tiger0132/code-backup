#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1

typedef long long ll;
const int N = 5e4 + 45, P = 1e9 + 7;
struct Z {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	Z() {}
	Z(int v) : x(v) {}
	Z(long long v) : x(v) {}
	Z(char v) : x(v) {}
	Z operator+(const Z& rhs) const { return norm(x + rhs.x - P); }
	Z operator-(const Z& rhs) const { return norm(x - rhs.x); }
	Z operator*(const Z& rhs) const { return (ll)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (ll)x * rhs.x % P; }
};

int ch[N][2], rt, nc;
char s[N], op[N];
int lb[N];
void build(int& x, int l, int r) {
	if (s[r] == ')' && lb[r] == l) return build(x, l + 1, r - 1);
	x = ++nc;
	if (l == r) return x[op] = s[l], void();
	int pos = lb[r] - 1;
	x[op] = s[pos];
	build(x[L], l, pos - 1);
	build(x[R], pos + 1, r);
}

Z F[N], f[N][2], ans;
void dfs(int x, int S) {
	if (!x[L]) {
		x[f][0] = (S >> (x[op] - '0')) & 1;
		x[f][1] = !((S >> (x[op] - '0')) & 1);
		return;
	}
	dfs(x[L], S), dfs(x[R], S);
	for (int a = 0; a <= 1; a++)
		for (int b = 0; b <= 1; b++) {
			if (x[op] != '>') x[f][std::min(a, b)] += x[L][f][a] * x[R][f][b];
			if (x[op] != '<') x[f][std::max(a, b)] += x[L][f][a] * x[R][f][b];
		}
}

int n, m, len, a[N][22], tmp[22];
int st[N], top;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) scanf("%d", a[j] + i);

	scanf("%s", s + 1), len = strlen(s + 1);
	for (int i = 1; i <= len; i++)
		if (s[i] == '(')
			st[++top] = i;
		else if (s[i] == ')')
			lb[i] = st[top--];
		else
			lb[i] = i;
	build(rt, 1, len);

	for (int S = 0; S < (1 << m); S++) {
		memset(f, 0, sizeof f);
		dfs(rt, S);
		F[S] = rt[f][1];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) tmp[j] = a[i][j];
		std::sort(tmp + 1, tmp + m + 1);
		for (int j = 1; j <= m; j++) {
			int S = 0;
			for (int k = 1; k <= m; k++) S |= (a[i][k] < tmp[j]) << (k - 1);
			ans += F[S] * (tmp[j] - tmp[j - 1]);
		}
	}
	printf("%d\n", ans.x);
}