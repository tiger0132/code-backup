#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 2e5 + 52, P = 1e9 + 7;

struct mod_t {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	mod_t() {}
	mod_t(int v) : x(v) {}
	mod_t(long long v) : x(v) {}
	mod_t(char v) : x(v) {}
	mod_t operator+(const mod_t& rhs) const { return norm(x + rhs.x - P); }
	mod_t operator-(const mod_t& rhs) const { return norm(x - rhs.x); }
	mod_t operator*(const mod_t& rhs) const { return (L)x * rhs.x % P; }
	void operator++(int z) { norm2(x += 1 - P); }
	void operator+=(const mod_t& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const mod_t& rhs) { norm2(x -= rhs.x); }
	void operator*=(const mod_t& rhs) { x = (L)x * rhs.x % P; }
};

mod_t _3k = 1, _3k1 = 1, _3k2 = 1, _3k3 = 1;
mod_t qqq, aqq, qbq, qqc, abq, aqc, qbc, abc;
mod_t a, b, c, q, ab, aq, qb, qq;
char s[N];
int n, cnt;
int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++)
		if (s[i] == '?') cnt++;
	for (int i = 0; i < cnt; i++) {
		_3k *= 3;
		if (i >= 1) _3k1 *= 3;
		if (i >= 2) _3k2 *= 3;
		if (i >= 3) _3k3 *= 3;
	}
	for (int i = 1; i <= n; i++)
		if (s[i] == 'a') {
			a++;
		} else if (s[i] == 'b') {
			ab += a, qb += q;
			b++;
		} else if (s[i] == 'c') {
			c++;
			qqc += qq;
			qbc += qb;
			aqc += aq;
			abc += ab;
		} else if (s[i] == '?') {
			qqq += qq;
			qbq += qb;
			aqq += aq;
			abq += ab;
			qq += q, aq += a;
			q++;
		}
	printf(
		"%d\n",
		(abc * _3k + (aqq + qbq + qqc) * _3k2 + (abq + aqc + qbc) * _3k1 + qqq * _3k3).x);
}