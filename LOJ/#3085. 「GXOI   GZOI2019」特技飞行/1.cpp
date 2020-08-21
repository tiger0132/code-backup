#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 5e5 + 55;
struct pt {
	double x, y1, y2;
	int op;
	bool operator<(const pt& r) const { return x < r.x; }
};

int top, tr[N];
void upd(int i, int x) {
	for (; i <= top; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (; i; i &= i - 1) r += tr[i];
	return r;
}

int n, k, a, b, c, st, ed, y0[N], y1[N], id[N], cnt;
long long ans, ans2;
std::vector<pt> v;
std::set<pii> s;
double tmp[N];
int main() {
	scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &st, &ed);
	for (int i = 1; i <= n; i++) scanf("%d", y0 + i);
	for (int i = 1; i <= n; i++) scanf("%d", y1 + i);

	for (int i = n; i >= 1; i--) {
		for (const pii& j : s) {
			if (j.first > y1[i]) break;
			double kk =
				1. * (y0[j.second] - y0[i]) / (y0[j.second] - y0[i] + y1[i] - j.first);
			double x = st + kk * (ed - st), y = y0[i] + kk * (y1[i] - y0[i]);
			v.push_back({x + y, tmp[++top] = x - y, 0, 0});
			cnt++;
		}
		s.insert(pii(y1[i], i));
	}

	scanf("%d", &k);
	double r;
	for (int i = 1, x, y; i <= k; i++) {
		scanf("%d%d%lf", &x, &y, &r);
		x += y, y = x - 2 * y;
		v.push_back({x - r, y - r, y + r, -1});
		v.push_back({x + r, y - r, y + r, 1});
	}

	std::sort(v.begin(), v.end());
	std::sort(tmp + 1, tmp + top + 1);

	for (const pt& i : v) {
		int y1 = std::lower_bound(tmp + 1, tmp + top + 1, i.y1) - tmp;
		int y2 = std::lower_bound(tmp + 1, tmp + top + 1, i.y2) - tmp;
		if (i.op)
			upd(y1, -i.op), upd(y2, i.op);
		else
			ans += c * !!qry(y1);
	}

	ans2 = ans;
	for (int i = 1; i <= n; i++) id[i] = i;
	std::sort(id + 1, id + n + 1, [](int x, int y) { return y1[x] < y1[y]; });
	for (int i = 1; i <= n; i++)
		if (id[i]) {
			ans2 += b - a;
			for (int j = i, k = id[i]; k; j = k, k = id[k]) id[j] = 0;
		}
	ans += cnt * a;
	ans2 += (cnt - n) * b + n * a;
	if (ans > ans2) std::swap(ans, ans2);

	printf("%lld %lld\n", ans, ans2);
}