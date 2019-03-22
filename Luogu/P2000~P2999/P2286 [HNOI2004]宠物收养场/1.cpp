#include <cmath>
#include <cstdio>
#include <set>

typedef std::set<int>::iterator $;

std::set<int> s;
int ans;
void calc(int y) {
	$ L = --s.lower_bound(y), R = s.lower_bound(y);
	if (y - *L <= *R - y && *L != 0xc0c0c0c0) {
		(ans += y - *L) %= 1000000;
		s.erase(L);
	} else if (*R != 0x3f3f3f3f) {
		(ans += *R - y) %= 1000000;
		s.erase(R);
	}
}

int n, x, y, f;
int main() {
	s.insert(0x3f3f3f3f);
	s.insert(0xc0c0c0c0);
	for (scanf("%d", &n); n--;) {
		scanf("%d%d", &x, &y);
		if (s.size() == 2) f = x;
		if (f == x)
			s.insert(y);
		else
			calc(y);
	}
	printf("%d", ans);
}