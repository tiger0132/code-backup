#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e6 + 61;
struct edge {
	int to, next;
} e[N << 1];
int head[N], dgr[N], cnt;
void addedge(int x, int y) {
	dgr[y]++;
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
}

int col[N], x_[N], y_[N], l[N], r[N], key[N], f_[N], ord[N];
int n, m, s, t, _, ncnt = 1, idx;
std::queue<int> q;
int main() {
	scanf("%d%d%d", &n, &m, &_);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", x_ + i, y_ + i);
		f_[x_[i]] = 1;
	}
	for (int i = 1; i <= n; i++) {
		col[i] = ncnt, ncnt += f_[i];
		l[i] = r[i] = i;
	}
	n = ncnt;
	for (int i = 1; i <= m; i++) {
		int u = col[x_[i]], v = col[y_[i]];
		u < v ? addedge(u, u + 1) : addedge(u + 1, u);
		key[u] = v;
	}
	for (int i = 1; i <= n; i++)
		if (!dgr[i]) q.emplace(i);
	for (int x; !q.empty(); q.pop()) {
		ord[++idx] = x = q.front();
		for (int f = 1; f;) {
			f = 0;
			if (1 < l[x] && l[x] <= key[l[x] - 1] && key[l[x] - 1] <= r[x]) l[x] = l[l[x] - 1], f = 1;
			if (r[x] < n && l[x] <= key[r[x]] && key[r[x]] <= r[x]) r[x] = r[r[x] + 1], f = 1;
		}
		for (int i = head[x]; i; i = e[i].next)
			if (!--dgr[e[i].to]) q.emplace(e[i].to);
	}
	while (_--) {
		scanf("%d%d", &s, &t), s = col[s], t = col[t];
		puts(l[s] <= t && t <= r[s] ? "YES" : "NO");
	}
}