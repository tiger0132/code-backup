#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

const int N = 3e5 + 53, P = 1e9 + 7;
struct node {
	int l, r;
	mutable int v;
	node(int x = 0, int y = 0, int z = 0) { l = x, r = y, v = z; }
	inline bool operator<(const node& rhs) const { return l < rhs.l; }
};
typedef std::set<node>::iterator I;
std::set<node> s;
I split(int x) {
	I it = s.lower_bound({x});
	if (it != s.end() && it->l == x) return it;
	it--;
	int l = it->l, r = it->r, v = it->v;
	s.erase(it), s.emplace(l, x - 1, v);
	return s.emplace(x, r, v).first;
}
int sum(int L, int R) {
	int ret = 0;
	split(L), split(R + 1);
	for (I l = s.lower_bound({L}), r = s.lower_bound({R + 1}); l != r; ++l) ret = (ret + (l->r - l->l + 1ll) * l->v % P) % P;
	return ret;
}
void set(int L, int R, int x) {
	split(L), split(R + 1);
	s.erase(s.lower_bound({L}), s.lower_bound({R + 1})), s.emplace(L, R, x);
}
void add(int L, int R, int x) {
	split(L), split(R + 1);
	for (I l = s.lower_bound({L}), r = s.lower_bound({R + 1}); l != r; ++l) l->v = (l->v + x) % P;
}
void copy(int L1, int R1, int L2, int R2) {
	static std::vector<node> v;
	v.clear();
	int ofs = L2 - L1;
	split(L1), split(R1 + 1);
	for (I l = s.lower_bound({L1}), r = s.lower_bound({R1 + 1}); l != r; ++l) v.emplace_back(l->l + ofs, l->r + ofs, l->v);
	split(L2), split(R2 + 1);
	s.erase(s.lower_bound({L2}), s.lower_bound({R2 + 1}));
	for (node i : v) s.emplace(i);
}
void swap(int L1, int R1, int L2, int R2) {
	static std::vector<node> v;
	v.clear();
	int ofs = L2 - L1;
	split(L1), split(R1 + 1);
	for (I l = s.lower_bound({L1}), r = s.lower_bound({R1 + 1}); l != r; ++l) v.emplace_back(l->l + ofs, l->r + ofs, l->v);
	split(L2), split(R2 + 1);
	for (I l = s.lower_bound({L2}), r = s.lower_bound({R2 + 1}); l != r; ++l) v.emplace_back(l->l - ofs, l->r - ofs, l->v);
	s.erase(s.lower_bound({L1}), s.lower_bound({R1 + 1})), s.erase(s.lower_bound({L2}), s.lower_bound({R2 + 1}));
	for (node i : v) s.emplace(i);
}
void rev(int L, int R) {
	static std::vector<node> v;
	v.clear(), split(L), split(R + 1);
	for (I l = s.lower_bound({L}), r = s.lower_bound({R + 1}); l != r; ++l) v.emplace_back(L + R - l->r, L + R - l->l, l->v);
	s.erase(s.lower_bound({L}), s.lower_bound({R + 1}));
	for (node i : v) s.emplace(i);
}

int n, m, op, x, y, z, w, _;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &x), s.emplace(i, i, x);
	s.emplace(n + 1, n + 1, -1);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if ("\0\0####"[op]) scanf("%d", &z);
		if ("\0\0\0\0##"[op]) scanf("%d", &w);
		switch (op) {
			case 1:
				printf("%d\n", sum(x, y));
				break;
			case 2:
				set(x, y, z);
				break;
			case 3:
				add(x, y, z);
				break;
			case 4:
				copy(x, y, z, w);
				break;
			case 5:
				swap(x, y, z, w);
				break;
			case 6:
				rev(x, y);
		}
	}
	for (node i : s)
		if (~i.v)
			for (int j = i.l; j <= i.r; j++) printf("%d ", i.v);
}