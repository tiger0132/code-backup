#include <algorithm>
#include <cstdio>
#include <cstring>

char s[3], t[3], p[4] = "abc";
int n;

int main() {
	scanf("%d%s%s", &n, s, t);
	if (s[0] == t[0] && s[1] == t[1]) s[0] = t[1];
	if (s[0] != s[1] && s[0] == t[1] && s[1] == t[0]) {
		puts("YES");
		char c;
		for (int i = 'a'; i <= 'c'; i++)
			if (s[0] != i && s[1] != i) c = i;
		for (int i = 0; i < n; i++) putchar(s[0]);
		for (int i = 0; i < n; i++) putchar(c), putchar(s[1]);
		return 0;
	}
	if (s[1] == t[1] && s[0] != s[1] && t[0] != t[1] && n > 1) {
		puts("YES");
		for (int i = 0; i < n; i++) putchar(s[1]);
		for (int i = 0; i < n; i++) putchar(s[0]), putchar(t[0]);
		return 0;
	}
	if (s[0] == t[0] && s[0] != s[1] && t[0] != t[1] && n > 1) {
		puts("YES");
		for (int i = 0; i < n; i++) putchar(s[1]), putchar(t[1]);
		for (int i = 0; i < n; i++) putchar(s[0]);
		return 0;
	}
	do {
		for (int i = 0; i < 3 - (n == 1); i++)
			if ((p[i] == s[0] && p[(i + 1) % 3] == s[1]) ||
				(p[i] == t[0] && p[(i + 1) % 3] == t[1]))
				goto end;
		puts("YES");
		for (int i = 0; i < n; i++) printf("%s", p);
		return 0;
	end:;
	} while (std::next_permutation(p, p + 3));
	puts("NO");
}