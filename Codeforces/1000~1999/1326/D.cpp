#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 4e6 + 64;

int n, flag[N], p[N];
char s[N], tt[N];
void manacher() {
	int rb = 0, mid;
	for (int i = 1; i < n; i++) {
		if (i < rb)
			p[i] = std::min(p[2 * mid - i], p[mid] + mid - i);
		else
			p[i] = 1;
		while (tt[i + p[i]] == tt[i - p[i]]) p[i]++;
		if (p[i] + i > rb) rb = p[i] + i, mid = i;
	}
}

int mx, mm, mi, fl;
signed main() {
	for (scanf("%*d"); ~scanf("%s", s);) {
		mm = n = strlen(s);
		tt[0] = '$', tt[1] = '|';
		for (int i = 0; i < n; i++) {
			tt[2 * i + 2] = s[i];
			tt[2 * i + 3] = '|';
		}
		tt[2 * n + 2] = 0;
		n = strlen(tt);
		manacher();

		n--;

		for (int i = 1; i <= n; i++) p[i]--;
		for (int i = 1; i <= n; i++) flag[i] = 0;
		flag[0] = flag[n + 1] = 1;
		for (int i = 1; i <= n; flag[i++] = 1)
			if (tt[i] != tt[n - i + 1]) break;

		// for (int i = 1; i <= n; i++) printf("%lld%c", p[i], " \n"[i == n]);
		// for (int i = 1; i <= n; i++) printf("%lld%c", flag[i], " \n"[i == n]);

		mx = mi = fl = 0;
		for (int i = 1; i <= n; i++) {
			int lb = i - p[i] - 1, rb = n - i - p[i];
			if (flag[lb] && i + p[i] < n - lb + 1)
				if (i > mx) mx = i - 1, mi = i, fl = 0;
			if (flag[rb] && rb < i - p[i])
				if (n - i > mx) mx = n - i, mi = i, fl = 1;
		}
		if (!fl) {
			for (int i = 1; i <= mi + p[mi]; i++)
				if (tt[i] != '|') putchar(tt[i]);
			for (int i = mi - p[mi] - 1; i >= 1; i--)
				if (tt[i] != '|') putchar(tt[i]);
		} else {
			for (int i = n; i >= mi - p[mi]; i--)
				if (tt[i] != '|') putchar(tt[i]);
			for (int i = mi + p[mi] + 1; i <= n; i++)
				if (tt[i] != '|') putchar(tt[i]);
		}
		puts("");
	}
}