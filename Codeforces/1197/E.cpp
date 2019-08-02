#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 2e5 + 52, INF = 0x3f3f3f3f, P = 1e9 + 7;

int n, x, y, inmx, fmn, ans, in[N], out[N], f[N], g[N];
std::vector<int> prev[N];
pii t[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x, &y), t[i] = pii(y, x);
	std::sort(t + 1, t + n + 1);
	for (int i = 1; i <= n; i++) in[i] = t[i].first, out[i] = t[i].second;
	inmx = *std::max_element(in + 1, in + n + 1);
	for (int i = 1; i <= n; i++) {
		int nxt = std::lower_bound(in + 1, in + n + 1, out[i]) - in;
		prev[nxt].push_back(i);
	}
	g[0] = 1, fmn = INF;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + in[i] - in[i - 1];
		g[i] = g[i - 1];
		for (int j : prev[i]) {
			int w = f[j] + in[i] - out[j];
			if (w < f[i]) f[i] = w, g[i] = 0;
			if (f[i] == w) g[i] = (g[i] + g[j]) % P;
		}
		if (out[i] <= inmx) continue;
		if (f[i] < fmn) fmn = f[i], ans = 0;
		if (f[i] == fmn) ans = (ans + g[i]) % P;
	}
	printf("%d", ans);
}