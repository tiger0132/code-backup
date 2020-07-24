#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, out[N], top;
char s[N], t[N];

void flip(int x) {
	out[++top] = x;
	for (int i = 1; i <= x; i++) s[i] ^= 1;
	std::reverse(s + 1, s + x + 1);
}
int main() {
	for (scanf("%*d"); ~scanf("%d%s%s", &n, s + 1, t + 1);) {
		for (int i = n; i >= 1; i--) {
			// if (s[i] == t[i]) continue;
			if (t[i] == s[1]) flip(1);
			flip(i);
		}
		printf("%d ", top);
		for (int i = 1; i <= top; i++) printf("%d ", out[i]);
		puts("");
		top = 0;
	}
}