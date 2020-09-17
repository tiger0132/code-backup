#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>

const int N = 2e5 + 52;

struct BIT {
	int tr[N], n;
	void init(int nn) { n = nn; }
	void add(int i, int x) {
		for (i++; i <= n + 1; i += i & -i) i[tr] += x;
	}
	int qry(int i) {
		int r = 0;
		for (i++; i; i -= i & -i) r += i[tr];
		return r;
	}
	int qry(int l, int r) { return qry(r) - qry(l - 1); }
};

struct T {
	std::vector<int> g[N];
	void operator()(int x, int y) { x[g].push_back(y); }

	int dfn[N], sz[N], idx;
	BIT tr;
	void init(int n) { tr.init(n); }
	void dfs(int x) {
		x[dfn] = ++idx, x[sz] = 1;
		for (int nx : x[g]) dfs(nx), x[sz] += nx[sz];
	}
	void add(int x, int y) { tr.add(x[dfn], y); }
	int qry(int x) { return tr.qry(x[dfn], x[dfn] + x[sz] - 1); }
};

struct SAM {
	int link[N], len[N], tr[N][26], nc;
	SAM() { nc = 1; }
	int ins(int last, int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		return cur;
	}
	void build(T &t) {
		t.init(nc);
		for (int i = 2; i <= nc; i++) t(i[link], i);
		t.dfs(1);
	}
	int operator()(char *s) {
		int x = 1;
		while (*s) x = x[tr][*s++ - 97];
		return x;
	}
};

const int M = 1e5 + 51;
struct Trie {
	int ch[M][26], p[M], pos[M], v[M], nc;
	Trie() { nc = 1; }
	int operator()(int x, int c) {
		if (x[ch][c]) return x[ch][c];
		return nc++, (nc[p] = x)[ch][nc[v] = c] = nc;
	}
	void build(SAM &sam) {
		std::queue<int> q;
		for (int i = 0; i < 26; i++)
			if (1 [ch][i]) q.push(1 [ch][i]);
		for (1 [pos] = 1; !q.empty(); q.pop()) {
			int x = q.front();
			x[pos] = sam.ins(x[p][pos], x[v]);
			for (int i = 0; i < 26; i++)
				if (x[ch][i]) q.push(x[ch][i]);
		}
	}
} trie;

std::vector<int> id[N];
int ans[N], q[N];
SAM sam;
T tree;
void dfs(int x) {
	tree.add(x[trie.pos], 1);
	for (int i : x[id]) i[ans] = tree.qry(i[q]);
	for (int i = 0; i < 26; i++)
		if (x[trie.ch][i]) dfs(x[trie.ch][i]);
	tree.add(x[trie.pos], -1);
}

int n, x, y, m, end[N], cur;
char s[N];
int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	cur = 1;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'P')
			end[++m] = cur;
		else if (s[i] == 'B')
			cur = cur[trie.p];
		else
			cur = trie(cur, s[i] - 'a');
	trie.build(sam);
	sam.build(tree);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		i[q] = x[end][trie.pos];
		y[end][id].push_back(i);
	}
	dfs(1);
	for (int i = 1; i <= n; i++) printf("%d\n", i[ans]);
}