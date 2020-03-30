#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

const int N = 2e5 + 52;

struct SAM {
	int len[N], link[N], tr[N][26], nc, last;
	int mx[N], mn[N];
	SAM() { nc = last = 1; }
	void ins(int HgS) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
		for (; p && !(q = p[tr][HgS]); p = p[link]) p[tr][HgS] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][HgS] == q; p = p[link]) p[tr][HgS] = cl;
			q[link] = cur[link] = cl;
		}
		last = cur;
	}
	void operator+=(char *str) {
		while (*str) ins(*str++ - 97);
	}
	void clear() {
		memset(len, 0, sizeof len);
		memset(link, 0, sizeof link);
		memset(tr, 0, sizeof tr);
		memset(mn, 0x3f, sizeof mn);
		nc = last = 1;
	}
	void exec(char *s) {
		memset(mx, 0, sizeof mx);
		int x = 1, l = 0;
		for (; *s; s++) {
			*s -= 97;
			while (x > 1 && !x[tr][*s]) l = (x = x[link])[len];
			if (x[tr][*s]) l++, x = x[tr][*s];
			x[mx] = std::max(x[mx], l);
		}
		for (int i = nc; i >= 1; i--)
			i[link][mx] = std::max(i[link][mx], std::min(i[mx], i[link][len]));
		for (int i = 1; i <= nc; i++) i[mn] = std::min(i[mn], i[mx]);
	}
} sam;

int t, n, ans;
char s[N];
int main() {
	scanf("%d", &t);
	while (t--) {
		sam.clear();
		ans = 0;
		scanf("%d%s", &n, s), sam += s;
		while (--n) scanf("%s", s), sam.exec(s);
		for (int i = 1; i <= sam.nc; i++) ans = std::max(ans, i[sam.mn]);
		printf("%d\n", ans);
	}
}