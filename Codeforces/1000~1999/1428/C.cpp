#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

char s[N];
int n;
int main() {
	for (scanf("%*d"); ~scanf("%s", s + 1);) {
		n = strlen(s + 1);
		int c = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i] == 'B') {
				if (c)
					ans++, c--;
				else
					c++;
			} else
				c++;
		}
		printf("%d\n", n - ans * 2);
	}
}