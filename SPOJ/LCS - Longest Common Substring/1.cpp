#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, M = 26;
struct state {
	int len, link, nxt[M];
} st[N];
int sz, last;
void init() { sz = last = 1; }
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

int n, m, lcs, len, p = 1;
char s[N], t[N];
int main() {
	scanf("%s%s", s + 1, t + 1), n = strlen(s + 1), m = strlen(t + 1);
	init();
	for (int i = 1; i <= n; i++) ins(s[i] - 'a');
	for (int i = 1; i <= m; i++) {
		int nx = t[i] - 'a';
		if (st[p].nxt[nx])
			len++, p = st[p].nxt[nx];
		else {
			while (p > 1 && !st[p].nxt[nx]) p = st[p].link;
			if (st[p].nxt[nx])
				len = st[p].len + 1, p = st[p].nxt[nx];
			else
				len = 0;
		}
		lcs = std::max(lcs, len);
	}
	printf("%d", lcs);
}