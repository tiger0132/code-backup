#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 51;

int f[N][5][5], nf[5][5], ans;
std::vector<int> g[N];
inline int max(int x, int y) { return x > y ? x : y; }
inline int max(std::initializer_list<int> x) { return std::max(x); }
inline int sb(int *x) { return max(x[1], x[2]); }
inline int nt(int *x) { return max({x[1], x[2], x[3]}); }
void dfs(int x, int p) {
	int deg0 = 0;
	f[x][1][1] = -10, f[x][1][2] = 0;
	f[x][2][1] = f[x][2][2] = f[x][2][3] = -10;
	f[x][3][1] = f[x][3][2] = f[x][3][3] = -10;
	f[x][4][1] = f[x][4][2] = f[x][4][3] = -10;
	for (int nx : x[g])
		if (nx != p) {
			dfs(nx, x);

			nf[1][1] = max(f[x][1][1] + 1, sb(f[nx][1]) + deg0);
			nf[1][2] = deg0 + 1;
			nf[2][1] = max(f[x][2][1], f[nx][2][2]);
			nf[2][2] = max(f[x][2][2], max(f[nx][2][3], sb(f[nx][1])) + 1);
			nf[2][3] = max(f[x][2][3] + 1, f[x][1][1] + sb(f[nx][1]));
			nf[3][1] = max({
				f[x][3][1] + 1,										  //
				f[x][2][1] + sb(f[nx][1]) + deg0 - 1,				  //
				f[x][2][2] + sb(f[nx][1]) + deg0 - 2,				  //
				max({f[nx][3][1], f[nx][3][2], f[nx][3][3]}) + deg0,  //
				sb(f[x][1]) + sb(f[nx][2]),							  //
				sb(f[x][1]) + max(sb(f[nx][1]), f[nx][2][3])		  //
			});
			nf[3][2] = max(f[x][3][2] + 1, sb(f[x][1]) + sb(f[nx][1]));
			nf[3][3] = max({
				f[x][3][3] + 1,				//
				f[x][3][2] + sb(f[nx][1]),	//
				f[x][2][3] + sb(f[nx][1])	//
			});
			nf[4][1] = max({
				f[x][4][1],									  //
				sb(f[x][2]) + sb(f[nx][2]) - 1,				  //
				sb(f[x][2]) + max(sb(f[nx][1]), f[nx][2][3])  //
			});
			nf[4][2] = max(f[x][4][2] + 1, f[nx][3][1] + deg0);
			nf[4][3] = max({
				f[x][4][3] + 1,				 //
				nt(f[x][3]),				 //
				nt(f[x][3]) + sb(f[nx][1]),	 //
				sb(f[x][1]) + nt(f[nx][3]),	 //
				f[x][2][3] + nt(f[nx][2])	 //
			});

			memcpy(f[x], nf, sizeof nf), deg0++;
		}
	ans = max({
		ans,																  //
		f[x][1][1] + (x != 1), f[x][1][2] + (x != 1),						  //
		f[x][2][1], f[x][2][2], f[x][2][3] + (x != 1),						  //
		f[x][3][1] + (x != 1), f[x][3][2] + (x != 1), f[x][3][3] + (x != 1),  //
		f[x][4][1], f[x][4][2] + (x != 1), f[x][4][3] + (x != 1)			  //
	});
}

int T, x, n;
int main() {
	for (scanf("%d%d", &T, &x); T--;) {
		scanf("%d", &n);
		if (x == 1) scanf("%*d%*d");
		if (x == 2) scanf("%*d%*d%*d%*d");
		for (int i = 1; i <= n; i++) i[g].clear();
		for (int i = 1, x, y; i < n; i++) {
			scanf("%d%d", &x, &y);
			x[g].push_back(y);
			y[g].push_back(x);
		}
		ans = 0, dfs(1, 1);
		printf("%d\n", ans);
	}
}