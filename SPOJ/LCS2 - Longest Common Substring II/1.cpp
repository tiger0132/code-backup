#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, M = 26;
struct state {
	int len, link, nxt[M];
} st[N];
int last, sz;
void init() { last = sz = 1; }
void ins(int c) {
	int cur = ++sz, p = last, q, cl;
	for (st[cur].len = st[p].len + 1; p && !(q = st[p].nxt[c]); p = st[p].link)
		st[p].nxt[c] = cur;
	if (!p)
		st[cur].link = 1;
	else if (st[p].len + 1 == st[q].len)
		st[cur].link = q;
	else {
		st[cl = ++sz] = {st[p].len + 1, st[q].link, {}};
		memcpy(st[cl].nxt, st[q].nxt, sizeof(int[M]));
		for (; p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = cl;
		st[cur].link = st[q].link = cl;
	}
	last = cur;
}

int n, mn[N], mx[N], ans;
char s[N];
int main() {
	init();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) ins(s[i] - 'a');
	memset(mn, 0x3f, sizeof mn);
	while (~scanf("%s", s + 1)) {
		memset(mx, 0, sizeof mx);
		n = strlen(s + 1);
		for (int i = 1, p = 1, len = 0; i <= n; i++) {
			int nx = s[i] - 'a';
			while (p > 1 && !st[p].nxt[nx]) len = st[p = st[p].link].len;
			if (st[p].nxt[nx])
				len++, p = st[p].nxt[nx];
			else
				len = 0;
			mx[p] = std::max(mx[p], len);
		}
		for (int i = sz; i >= 1; i--)
			mx[st[i].link] =
				std::max(mx[st[i].link], std::min(mx[i], st[st[i].link].len));
		for (int i = 1; i <= sz; i++) mn[i] = std::min(mn[i], mx[i]);
	}
	for (int i = 1; i <= sz; i++) ans = std::max(ans, mn[i]);
	printf("%d", ans);
}