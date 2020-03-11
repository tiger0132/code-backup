#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

const int N = 5e5 + 55, LN = 19;
struct rec {
	int ans, id;
	bool operator<(const rec& r) const {
		return ans < r.ans || (ans == r.ans && id > r.id);
	}
} ans;

int n, st[LN][N];
void init() {
	for (int i = 1; (1 << i) <= n; i++)
		for (int v = 1; v + (1 << i) - 1 <= n; v++)
			st[i][v] = std::min(st[i - 1][v], st[i - 1][v + (1 << (i - 1))]);
}
int qry(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return std::min(st[k][l], st[k][r - (1 << k) + 1]);
}

int a[N], b[N], stk[N], lmx[N], lmn[N], rmx[N], rmn[N], top, pp, qq, val;
std::vector<int> v[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) {
		st[0][i] = a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
		v[a[i]].push_back(i);
	}
	init();
	stk[top = 0] = 0;
	for (int i = 1; i <= n; i++) {
		for (; top && a[stk[top]] > a[i];) top--;
		i[lmn] = stk[top] + 1, stk[++top] = i;
	}
	stk[top = 0] = 0;
	for (int i = 1; i <= n; i++) {
		for (; top && a[stk[top]] < a[i];) top--;
		i[lmx] = stk[top] + 1, stk[++top] = i;
	}
	stk[top = 0] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (; top && a[stk[top]] > a[i];) top--;
		i[rmn] = stk[top] - 1, stk[++top] = i;
	}
	stk[top = 0] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (; top && a[stk[top]] < a[i];) top--;
		i[rmx] = stk[top] - 1, stk[++top] = i;
	}
	for (int i = 1; i <= n; i++) {
		val = qry(lmx[i], rmx[i]);
		qq = std::lower_bound(v[val].begin(), v[val].end(), i) - v[val].begin(),
		pp = qq - 1;
		if (pp >= 0 && rmn[v[val][pp]] >= i)
			ans = std::max(ans, {std::min(rmx[i], rmn[v[val][pp]]) -
									 std::max(lmx[i], lmn[v[val][pp]]) + 1,
								 std::max(lmx[i], lmn[v[val][pp]])});
		if (qq < (int)v[val].size() && lmn[v[val][qq]] <= i)
			ans = std::max(ans, {std::min(rmx[i], rmn[v[val][qq]]) -
									 std::max(lmx[i], lmn[v[val][qq]]) + 1,
								 std::max(lmx[i], lmn[v[val][qq]])});
	}
	printf("%d %d\n", ans.ans, ans.id);
}