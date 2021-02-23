#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1

const int N = 6e5 + 56, M = 1.4e7 + 741, K = 21;

int rt[N], ch[M][2], sum[M], pari[M], nc;
inline void up(int x) {
	x[pari] = x[L][pari] ^ x[R][pari];
	x[sum] = ((x[L][sum] ^ x[R][sum]) << 1) | x[R][pari];
}
void ins(int x, int v) {
	for (int i = 0; i < K; i++, v >>= 1) {
		x[sum] ^= v;
		x[pari] ^= 1;
		if (x[ch][v & 1])
			x = x[ch][v & 1];
		else
			x = x[ch][v & 1] = ++nc;
	}
	x[pari] ^= 1;
}
int mg(int x, int y) {
	if (!x || !y) return x | y;
	x[sum] ^= y[sum], x[pari] ^= y[pari];
	x[L] = mg(x[L], y[L]);
	x[R] = mg(x[R], y[R]);
	return x;
}
void upd(int x) {
	std::swap(x[L], x[R]);
	if (x[L]) upd(x[L]);
	if (x[L] || x[R]) up(x);
}

std::vector<int> g[N];
long long ans;
int v[N];
void dfs(int x) {
	x[rt] = ++nc;
	for (int nx : x[g]) {
		dfs(nx);
		x[rt] = mg(x[rt], nx[rt]);
	}
	upd(x[rt]);
	ins(x[rt], x[v]);
	ans += x[rt][sum];
}

int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		x[g].push_back(i);
	}
	dfs(1);
	printf("%lld\n", ans);
}