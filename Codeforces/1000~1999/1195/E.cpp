#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>

typedef long long ll;
const int N = 3e3 + 33, L = 12;

int n, m, a, b, g, x, y, z;
std::deque<int> q;
int ar[N][N], r_mn[N][N];
ll ans;
int main() {
	scanf("%d%d%d%d%d%d%d%d", &n, &m, &a, &b, &g, &x, &y, &z);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) ar[i][j] = g, g = (1ll * g * x + y) % z;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			while (!q.empty() && ar[i][q.back()] >= ar[i][j]) q.pop_back();
			q.push_back(j);
			while (q.front() <= j - b) q.pop_front();
			if (j >= b) r_mn[i][j - b + 1] = ar[i][q.front()];
		}
		q.clear();
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			while (!q.empty() && r_mn[q.back()][j] >= r_mn[i][j]) q.pop_back();
			q.push_back(i);
			while (q.front() <= i - a) q.pop_front();
			if (i >= a) ans += r_mn[q.front()][j];
		}
		q.clear();
	}
	printf("%lld", ans);
}