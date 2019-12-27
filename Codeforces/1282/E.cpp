#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>

typedef long long ll;
const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt, d[N];
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, d[x]++;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt, d[y]++;
}

ll f(int x, int y) { return x * (ll)1e5 + y; }

int n, a, b, c, u[N], v[N], w[N], nxt[N], vis[N];
std::map<ll, int> mp;
std::queue<int> q;
int ord[N], idx;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n - 2; i++) {
			scanf("%d%d%d", &a, &b, &c);
			if (a > b) std::swap(a, b);
			if (a > c) std::swap(a, c);
			if (b > c) std::swap(b, c);
			if (mp.count(f(a, b))) addedge(mp[f(a, b)], i);
			if (mp.count(f(a, c))) addedge(mp[f(a, c)], i);
			if (mp.count(f(b, c))) addedge(mp[f(b, c)], i);
			mp[f(a, b)] = mp[f(a, c)] = mp[f(b, c)] = i;
			u[i] = a, v[i] = b, w[i] = c;
		}
		for (int i = 1; i <= n - 2; i++)
			if (!--i[d]) q.push(i);
		for (; !q.empty(); q.pop())
			for (int x = ord[++idx] = q.front(), i = x[head], nx; i; i = e[i].next)
				if (!--(nx = e[i].to)[d]) q.push(nx);
		u[ord[n - 2]][nxt] = v[ord[n - 2]], v[ord[n - 2]][vis] = 1;
		v[ord[n - 2]][nxt] = w[ord[n - 2]], w[ord[n - 2]][vis] = 1;
		w[ord[n - 2]][nxt] = u[ord[n - 2]], u[ord[n - 2]][vis] = 1;
		for (int i = n - 3; i >= 1; i--) {
			a = u[ord[i]], b = v[ord[i]], c = w[ord[i]];
			if (!a[vis]) std::swap(a, c);
			if (!b[vis]) std::swap(b, c);
			if (a[nxt] != b) std::swap(a, b);
			if (a[nxt] != b) return 1;
			a[nxt] = c, c[nxt] = b, c[vis] = 1;
		}
		for (int i = a, j = 0; j != a; j = i = i[nxt])
			printf("%d%c", i, " \n"[i[nxt] == a]);
		for (int i = 1; i <= n - 2; i++) printf("%d%c", ord[i], " \n"[i == idx]);
		memset(head, 0, (n + 1) * 4), cnt = idx = 0;
		memset(d, 0, (n + 1) * 4);
		memset(nxt, 0, (n + 1) * 4);
		memset(vis, 0, (n + 1) * 4);
		mp.clear();
	}
}