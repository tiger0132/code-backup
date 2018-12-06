// 咕咕咕

#include <cstdio>
#define int long long

const int N = 2e5+25;

int ch[N][2], par[N], val[N], sum[N], sz[N], ncnt, root;

int chk(int x) { return ch[par[x]][1] == x; }
void pushup(int x) {
	sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
}
int newNode(int x) {
	int cur = ++ncnt;
	val[cur] = sum[cur] = x; sz[cur] = 1;
	return cur;
}
void rotate(int x) {
	int y = par[x], z = par[y], k = chk(x), w = ch[x][!k];
	ch[y][k] = w; par[w] = y;
	ch[z][chk(y)] = x; par[x] = z;
	ch[x][!k] = y; par[y] = x;
	pushup(y); pushup(x);
}
void slay(int x, int goal = 0) {
	while (par[x] != goal) {
		int y = par[x], z = par[y];
		if (z != goal) rotate(chk(x) == chk(y) ? y : x);
		rotate(x);
	}
	if (!goal) root = x;
}
int kth(int k) {
	int cur = root;
	while (1) {
		if (ch[cur][0] && k <= sz[ch[cur][0]]) {
			cur = ch[cur][0];
		} else if (k > sz[ch[cur][0]] + 1) {
			k -= sz[ch[cur][0]] + 1;
			cur = ch[cur][1];
		} else return cur;
	}
}
void find(int x) {
	int cur = root;
	while (ch[cur][x > val[cur]] && x != val[cur]) {
		cur = ch[cur][x > val[cur]];
	}
	slay(cur);
}
int pre(int x, int f) {
	find(x);
	if ((!f && val[root] < x) || (f && val[root] > x)) return root;
	int cur = ch[root][f];
	while (ch[cur][!f]) cur = ch[cur][!f];
	return cur;
}
void remove(int x) {
	int last = pre(x, 0), next = pre(x, 1);
	slay(last); slay(next, last);
	ch[next][0] = 0;
}
int build(int l, int r, int *arr) {
	if (l > r) return 0;
	int mid = (l+r)>>1;
	int x = build(l, mid-1, arr);
	int cur = cur = newNode(arr[mid]);
	int y = build(mid+1, r, arr);
	if (l == r) return cur;
	if (x) par[x] = cur;
	if (y) par[y] = cur;
	pushup(cur);
	return cur;
}
int query(int l, int r) {
	int x = kth(l), y = kth(r+2); 
}

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}
int val[N], L[N], R[N], v[N], idx;
void dfs(int x, int par) {
	val[++idx] = v[x]; L[x] = idx;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par) continue;
		dfs(nx, x);
	}
	val[++idx] = -v[x]; R[x] = idx;
}

int n, m, x, y;
char op[2];

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 2; i <= n; i++) {
		scanf("%lld", &x);
		addedge(i, x);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", v+i);
	}
	val[++idx] = 0;
	dfs(1, -1);
	val[++idx] = 0;
	root = build(1, idx, val);
	while (m--) {
		scanf("%s%lld", op, &x);
		switch (*op) {
			case 'Q':
				
				break;
		}
	}
}