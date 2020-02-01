// can't AC UOJ #317

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stack>

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dfn[N], low[N], ins[N], col[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, st.push(x), x[ins] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low])
		for (int y = scnt++; !st.empty();) {
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt;
			if (y == x) break;
		}
}

int x[N], a[N], y[N], b[N], ze[N];
char str[N], t1[2], t2[2];
char ban[N], rec[N][2];
int n, d, m;
int main() {
	srand((unsigned long long)new char);
	scanf("%d%d%s%d", &n, &d, str + 1, &m);
	for (int i = 1; i <= n; i++) i[str] -= 'a';
	for (int i = 1; i <= m; i++) {
		scanf("%d%s%d%s", x + i, t1, y + i, t2);
		a[i] = *t1 - 'A', b[i] = *t2 - 'A';
	}
	for (int S = 0; S < (1 << d); S++) ze[S] = S;
	std::random_shuffle(ze, ze + (1 << d));
	for (int _ = 0; _ < (1 << d); _++) {
		int S = ze[_];
		memset(head, 0, sizeof head);
		memset(dfn, 0, sizeof dfn);
		scnt = cnt = idx = 0;

		for (int i = 1, j = 0; i <= n; i++) {
			if ((i[ban] = i[str]) == 23) i[ban] = (S >> j++) & 1;
			i[rec][0] = !i[ban];
			i[rec][1] = 2 - (i[ban] == 2);
		}
		for (int i = 1; i <= m; i++) {
			int s = x[i], t = y[i];
			if (a[i] == s[ban]) continue;
			int s0 = (a[i] == s[rec][1]);
			int t0 = (b[i] == t[rec][1]);
			if (b[i] == t[ban]) t = s, t0 = !s0;
			addedge(s + s0 * n, t + t0 * n);
			addedge(t + !t0 * n, s + !s0 * n);
		}
		for (int i = 1; i <= 2 * n; i++)
			if (!dfn[i]) dfs(i);
		for (int i = 1; i <= n; i++)
			if (col[i] == col[n + i]) goto end;
		for (int i = 1; i <= n; i++) putchar(i[rec][col[i] > col[n + i]] + 'A');
		return 0;
	end:;
		if (clock() >= 0.98 * CLOCKS_PER_SEC) return puts("-1"), 0;
	}
	puts("-1");
}