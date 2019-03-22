#include <cstdio>

const int N = 1e5+15;

int ch[N][2], par[N], val[N], sz[N], cnt[N], ncnt, root;

int chk(int x) { return ch[par[x]][1] == x; }
void pushup(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
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
void insert(int x) {
	int cur = root, p = 0;
	while (cur && x != val[cur]) {
		p = cur;
		cur = ch[cur][x > val[cur]];
	}
	if (cur) cnt[cur]++;
	else {
		cur = ++ncnt;
		if (p) ch[p][x > val[p]] = cur;
		val[cur] = x; par[cur] = p;
		sz[cur] = cnt[cur] = 1;
	}
	slay(cur);
}
int kth(int k) {
	int cur = root;
	while (1) {
		if (ch[cur][0] && k <= sz[ch[cur][0]]) {
			cur = ch[cur][0];
		} else if (k > sz[ch[cur][0]] + cnt[cur]) {
			k -= sz[ch[cur][0]] + cnt[cur];
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
	int& del = ch[next][0];
	if (cnt[del] > 1) {
		cnt[del]--;
		slay(del);
	} else del = 0;
}

int n, op, x;

int main() {
	insert(0x3f3f3f3f);
	insert(0xcfcfcfcf);
	for (scanf("%d", &n); n--; ) {
		scanf("%d%d", &op, &x);
		switch (op) {
			case 1: insert(x); break;
			case 2: remove(x); break;
			case 3: find(x); printf("%d\n", sz[ch[root][0]]); break;
			case 4: printf("%d\n", val[kth(x+1)]); break;
			case 5: printf("%d\n", val[pre(x, 0)]); break;
			case 6: printf("%d\n", val[pre(x, 1)]); break;
		}
	}
}