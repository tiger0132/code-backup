#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>

const int N = 1e3 + 31, M = 133;

int n, t, pre[M], nxt[M], v[M];
char s[N];
int main() {
	for (scanf("%*d"); ~scanf("%s", s);) {
		memset(pre, 0, sizeof pre);
		memset(nxt, 0, sizeof nxt);
		memset(v, 0, sizeof v);
		n = strlen(s);
		s[0][v] = 1;
		for (int i = 1, p = s[0]; i < n; p = s[i], s[i++][v] = 1)
			if (s[i] == p[pre])
				;
			else if (s[i] == p[nxt])
				;
			else if (s[i][v])
				goto end;
			else if (!p[pre])
				p[pre] = s[i], s[i][nxt] = p;
			else if (!p[nxt])
				p[nxt] = s[i], s[i][pre] = p;
			else
				goto end;
		puts("YES");
		for (int i = 'a'; i <= 'z'; i++)
			if (!i[v]) putchar(i);
		for (t = s[0]; t[pre];) t = t[pre];
		for (; t; t = t[nxt]) putchar(t);
		puts("");
		continue;
	end:;
		puts("NO");
	}
}