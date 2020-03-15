#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <unordered_map>
#include <vector>

typedef long long ll;
const int N = 5e5 + 55;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt, p;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
int dfn[N], low[N], ins[N], scc[N], scnt, idx;
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
			y = st.top(), st.pop(), y[ins] = 0, y[scc] = scnt;
			if (y == x) break;
		}
}

struct rec {
	int u, v, c, w, id;
} ed[N];

int n, m, mp_sz;
int $(int id, ll col) {
	static std::unordered_map<ll, int> mp;
	ll x = col * n + id;
	if (!mp.count(x)) return mp[x] = ++mp_sz;
	return mp[x];
}

int nc;
bool check(int k) {
	static int _head[N], _cnt;
	bool f = true;
	memcpy(_head, head, sizeof head), _cnt = cnt;
	for (int i = k + 1; i <= m; i++) addedge(i + m, i);
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	scnt = idx = 0;
	for (int i = 1; i <= nc; i++)
		if (!i[dfn]) dfs(i);
	for (int i = 1; i <= m; i++)
		if (i[scc] == (i + m)[scc]) f = false;
	memcpy(head, _head, sizeof head), cnt = _cnt;
	return f;
}

std::vector<int> ed_cv[N], ed_v[N], ans;
int pre_id[N], suf_id[N];
int l, r;
int main() {
	scanf("%d%d", &n, &m), nc = m * 2;
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d%d", &ed[i].u, &ed[i].v, &ed[i].c, &ed[i].w), ed[i].id = i;
	std::sort(ed + 1, ed + m + 1, [](const rec& x, const rec& y) { return x.w < y.w; });
	for (int i = 1; i <= m; i++) {
		ed_cv[$(ed[i].u, ed[i].c)].push_back(i);
		ed_cv[$(ed[i].v, ed[i].c)].push_back(i);
		ed_v[ed[i].u].push_back(i);
		ed_v[ed[i].v].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
#define ID ed_v[i][j]
		int sz = ed_v[i].size();
		for (int j = 0; j < sz; j++) {
			pre_id[j] = ++nc;
			addedge(pre_id[j], ID);
			if (j) addedge(pre_id[j], pre_id[j - 1]);
		}
		for (int j = sz - 1; ~j; j--) {
			suf_id[j] = ++nc;
			addedge(suf_id[j], ID);
			if (j < sz - 1) addedge(suf_id[j], suf_id[j + 1]);
		}
		for (int j = 0; j < sz; j++) {
			if (j) addedge(ID + m, pre_id[j - 1]);
			if (j < sz - 1) addedge(ID + m, suf_id[j + 1]);
		}
#undef ID
	}
	for (int i = 1; i <= mp_sz; i++) {
#define ID ed_cv[i][j]
		int sz = ed_cv[i].size();
		for (int j = 0; j < sz; j++) {
			pre_id[j] = ++nc;
			addedge(pre_id[j], ID + m);
			if (j) addedge(pre_id[j], pre_id[j - 1]);
		}
		for (int j = sz - 1; ~j; j--) {
			suf_id[j] = ++nc;
			addedge(suf_id[j], ID + m);
			if (j < sz - 1) addedge(suf_id[j], suf_id[j + 1]);
		}
		for (int j = 0; j < sz; j++) {
			if (j) addedge(ID, pre_id[j - 1]);
			if (j < sz - 1) addedge(ID, suf_id[j + 1]);
		}
#undef ID
	}
#define mid (l + r) / 2
	for (l = 0, r = m; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	if (l > m) return puts("No"), 0;
	check(l);
	puts("Yes");
	for (int i = 1; i <= m; i++)
		if (i[scc] > (i + m)[scc]) ans.push_back(ed[i].id);
	printf("%d %lu\n", ed[l].w, ans.size());
	for (int i : ans) printf("%d ", i);
}