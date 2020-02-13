#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31;

int n, f, l;
char s[N];
int main() {
	for (scanf("%*d"); ~scanf("%s", s);) {
		n = strlen(s);
		f = l = -1;
		int a = 0;
		for (int i = 0; i < n; i++)
			if (s[i] == '1') {
				if (!~f) f = i;
				l = i;
			}
		for (int i = f; i <= l; i++) a += s[i] == '0';
		printf("%d\n", a);
	}
}