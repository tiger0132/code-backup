#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <type_traits>

template <size_t SZ>
struct mat {
	bool rec[SZ][SZ];
	inline mat() { memset(rec, 0, sizeof rec); }
	inline void clear() { memset(rec, 0, sizeof rec); }
	inline void init() {
		memset(rec, 0, sizeof rec);
		for (int i = 0; i < SZ; i++) rec[i][i] = 1;
	}
	inline void operator*=(const mat<SZ> rhs) {
		static std::bitset<SZ> _a[SZ], _b[SZ];
		for (int i = 0; i < SZ; i++)
			for (int j = 0; j < SZ; j++) _a[i][j] = rec[i][j];
		for (int i = 0; i < SZ; i++)
			for (int j = 0; j < SZ; j++) _b[j][i] = rhs.rec[i][j];
		for (int i = 0; i < SZ; i++)
			for (int j = 0; j < SZ; j++) rec[i][j] = (_a[i] & _b[j]).any();
	}
	inline bool* operator[](int i) { return rec[i]; }
};

template <size_t SZ>
void pw(mat<SZ> x, int y, mat<SZ>& ret) {
	for (ret.init(); y; y >>= 1, x *= x)
		if (y & 1) ret *= x;
}

const int N = 3e2 + 23;
struct edge {
	int x, y, d;
	bool operator<(const edge& rhs) const { return d < rhs.d; }
} e[N];

int n, m, dis[N][N], ans = 0x3f3f3f3f;
mat<151> G, tmp, can;
int main() {
	memset(dis, 0x3f, sizeof dis);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].d);
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++) can[i][i] = 1, dis[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		pw(G, e[i].d - e[i - 1].d, tmp);
		can *= tmp;
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				dis[j][k] = std::min(dis[j][k], dis[j][e[i].x] + 1 + dis[e[i].y][k]);
		for (int j = 1; j <= n; j++)
			if (can[1][j]) ans = std::min(ans, e[i].d + dis[j][n]);
		G[e[i].x][e[i].y] = 1;
	}
	printf(ans == 0x3f3f3f3f ? "Impossible" : "%d", ans);
}