#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>

struct node {
	int l, r;
	bool operator<(const node& rhs) const { return r < rhs.r; }
};
std::map<int, int> b[61];
std::vector<node> v;
std::set<int> s;
int n, a[61], l[61], r[61], ans, top;
int L[61], R[61];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] += a[i - 1];
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int k = a[j] - a[i - 1];
			if (!b[i].count(k)) b[i][k] = j, s.insert(k);
		}
	}
	for (int i : s) {
		v.clear();
		top = 0;
		int last;
		for (int j = 1; j <= n; j++) {
			if (b[j].count(i)) v.push_back((node){j, b[j][i]});
		}
		std::sort(v.begin(), v.end());
		l[++top] = v[0].l, r[top] = last = v[0].r;
		for (int j = 0; j < v.size(); j++) {
			if (v[j].l > last) {
				l[++top] = v[j].l, r[top] = v[j].r;
				last = v[j].r;
			}
		}
		if (top > ans) {
			memcpy(L, l, sizeof L);
			memcpy(R, r, sizeof R);
			ans = top;
		}
	}
	printf("%d\n", ans);
	for (int i = 1; i <= ans; i++) printf("%d %d\n", L[i], R[i]);
}