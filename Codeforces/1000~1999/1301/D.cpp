#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#define int long long

const int N = 4e3 + 34;

int n, m, k, cnt;

std::string op[N];
int rep[N], c;
void print() {
	puts("YES");
	printf("%lld\n", c);
	for (int i = 1; i <= c; i++) printf("%lld %s\n", rep[i], op[i].c_str());
	exit(0);
}
void add(int x, std::string s) {
	if (!x) return;
	k -= x * s.size();
	rep[++c] = x, op[c] = s;
	if (!k) print();
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	if (n == 1) {
		cnt = 2 * m - 2;
		if (k > cnt) return puts("NO"), 0;

		add(std::min(m - 1, k), "R");
		add(std::min(m - 1, k), "L");

		return 0;
	}
	if (m == 1) {
		cnt = 2 * n - 2;
		if (k > cnt) return puts("NO"), 0;

		add(std::min(n - 1, k), "D");
		add(std::min(n - 1, k), "U");

		return 0;
	}
	cnt = 4 * n * m - 2 * n - 2 * m;
	if (k > cnt) return puts("NO"), 0;

	add(std::min(m - 1, k), "R");

	add(std::min(n - 1, k), "D");
	add(std::min(n - 1, k), "U");
	add(1, "L");

	for (int i = m - 1, tmp; i >= 1; i--) {
		add(tmp = std::min(n - 1, k / 3), "DRL");
		if (k < 3 && tmp < n - 1) {
			add(1, "D");
			add(1, "R");
		}
		add(std::min(n - 1, k), "U");
		add(1, "L");
	}
}