#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

const int P[3] = {998244353, 19260817, int(1e9 + 9)};
const int X[3] = {17, 19, 97};
const int N = 1e5 + 51, M = 1e6 + 61;

std::vector<int> p[3];
struct str {
	int n;
	std::string s;
	std::vector<int> h[3];
	int sub(int id, int l, int r) {
		l++, r++;
		return h[id][r] - 1ll * h[id][l - 1] * p[id][r - l + 1];
	}
	void init(const std::string& sss) {
		s = sss;
		n = s.size();
		for (int k = 0; k < 3; k++) {
			h[k].push_back(0);
			h[k].push_back(s[0]);
			for (int j = 1; j < n; j++)
				h[k].push_back(1ll * h[k].back() * X[k] + s[j] % P[k]);
		}
	}
	void add(const std::string& x) {
		s += x;
		for (int k = 0; k < 3; k++)
			for (int j = n; j < s.size(); j++)
				h[k].push_back(1ll * h[k].back() * X[k] + s[j] % P[k]);
		n = s.size();
	}
} a[N], s;

#define C(x) s.sub(x, s.n - j - 1, s.n - 1) == a[i + 1].sub(x, 0, j)

std::string sss;
int n, ls;
int main() {
	scanf("%d", &n);
	for (int k = 0; k < 3; k++) {
		p[k].push_back(1);
		for (int i = 1; i < M; i++) p[k].push_back(1ll * p[k].back() * X[k] % P[k]);
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> sss;
		a[i].init(sss);
	}
	for (int i = 1; i < n; i++) {
		if (i > 1)
			s.add(a[i].s.substr(ls));
		else
			s.init(a[1].s);
		ls = 0;
		for (int j = std::min(s.n, a[i + 1].n) - 1; j >= 0; j--)
			if (C(0) && C(1) && C(2)) {
				ls = j + 1;
				break;
			}
	}
	std::cout << s.s << a[n].s.substr(ls);
}