#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 333;
int qry(char *s) {
	puts(s);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}

char s[N], b[N];
int n, s0, tmp, A, B;
int main() {
	for (int i = 0; i < 300; i++) s[i] = 'a';
	for (int i = 0; i < 300; i++) b[i] = 'b';
	s0 = A = 300 - qry(b);
	if (A == 300) return 0;
	B = 300 - qry(s);
	if (B == 300) return 0;
	n = B + A;
	s[n + 1] = 0;
	for (int i = 0; i < n - 1; i++) {
		s[i] = 'b';
		tmp = qry(s);
		if (tmp == -1) return 0;
		if (tmp == 1 && n < 300) {
			s[n] = 0;
			qry(s);
			return 0;
		}
		if (!tmp) return 0;
		if (tmp >= s0) s[i] = 'a';
		s0 = tmp;
		(s[i] == 'a' ? A : B)--;
	}
	s[n - 1] = A ? 'a' : 'b', s[n] = 0;
	qry(s);
}