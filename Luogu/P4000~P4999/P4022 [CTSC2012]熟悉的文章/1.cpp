#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2.2e6 + 622;

struct SAM {
	int len[N], link[N], tr[N][3], nc, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
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
		last = cur;
	}
	void operator+=(char *s) {
		while (*s) ins(*s++ - 48);
		ins(2);
	}

	int dp[N], que[N];
	bool operator()(char *s, int L) {
		int x = 1, i = 1, mx = 0, l = 0, r = 0;
		for (; *s; i++, s++) {
			int p = *s - 48;
			while (x > 1 && !x[tr][p]) mx = (x = x[link])[len];
			if (x[tr][p]) mx++, x = x[tr][p];
			if (i >= L) {
				dp[i] = dp[i - 1];
				while (l <= r && que[l] < i - mx) l++;
				if (l <= r) dp[i] = std::max(dp[i], dp[que[l]] + i - que[l]);
				while (l <= r && dp[que[r]] - que[r] <= dp[i - L + 1] - (i - L + 1)) r--;
				que[++r] = i - L + 1;
			}
		}
		bool f = dp[i - 1] * 10 >= (i - 1) * 9;
		memset(que, 0, (i + 10) * 4);
		memset(dp, 0, (i + 10) * 4);
		return f;
	}
} sam;

int n, m, l, r;
char s[N];
int main() {
	scanf("%d%d", &n, &m);
	while (m--) scanf("%s", s), sam += s;
	while (n--) {
		scanf("%s", s);
		l = 1, r = strlen(s);
#define mid (l + r) / 2
		while (l <= r)
			if (sam(s, mid))
				l = mid + 1;
			else
				r = mid - 1;
		printf("%d\n", r);
	}
}