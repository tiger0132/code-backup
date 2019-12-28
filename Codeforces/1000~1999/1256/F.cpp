#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;
int n, c[26], c2[26], inv;
char s[N], t[N];
bool f, f2;
int main() {
	for (scanf("%*d"); ~scanf("%d%s%s", &n, s + 1, t + 1);) {
		inv = 0, f = true, f2 = false;
		for (int i = 0; i < 26; i++) i[c] = i[c2] = 0;
		for (int i = 1; i <= n; i++) (s[i] - 'a')[c]++;
		for (int i = 0; i < 26; i++) f2 |= i[c] > 1;
		for (int i = 1; i <= n; i++) (t[i] - 'a')[c]--;
		for (int i = 0; i < 26; i++) f &= !i[c], i[c] = 0;
		if (!f) {
			puts("NO");
			continue;
		}
		if (f2) {
			puts("YES");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = s[i] - 'a' + 1; j < 26; j++) inv ^= j[c];
			for (int j = t[i] - 'a' + 1; j < 26; j++) inv ^= j[c2];
			(s[i] - 'a')[c] ^= 1, (t[i] - 'a')[c2] ^= 1;
		}
		puts(inv & 1 ? "NO" : "YES");
	}
}