#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

typedef std::set<int>::iterator $;
const int N = 1e5 + 51;

namespace BIT {
int a[N], n;
int lowbit(int x) { return x & -x; }
void add(int i, int x) {
	for (; i <= n; i += lowbit(i)) a[i] += x;
}
int qry(int i) {
	int ret = 0;
	for (; i; i -= lowbit(i)) ret += a[i];
	return ret;
}
void add(int l, int r, int x) { add(l, x), add(r + 1, -x); }
};  // namespace BIT

int n, m, tmp, v, rt, op[N], x[N], a[N], par[N], ch[N][2];
std::set<int> s;
$ it;
int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", op + i);
		if (op[i] == 1) scanf("%d", x + i), a[++n] = x[i];
	}
	BIT::n = n;
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) x[i] = std::lower_bound(a + 1, a + n + 1, x[i]) - a;
	for (int i = 1; i <= m; i++) {
		if (op[i] == 1) {
			if (!rt)
				rt = x[i], BIT::add(x[i], x[i], 1), puts("1");
			else {
				int pv = 0, pdep = 0, qv = 0, qdep = 0;
				if ((it = s.lower_bound(x[i])) != s.begin())
					pdep = BIT::qry(pv = *--it) + 1;
				if ((it = s.lower_bound(x[i] + 1)) != s.end())
					qdep = BIT::qry(qv = *it) + 1;
				if (pdep > qdep) {
					x[i][par] = pv, pv[ch][1] = x[i];
					BIT::add(x[i], x[i], pdep - BIT::qry(x[i]));
					printf("%d\n", pdep);
				} else {
					x[i][par] = qv, qv[ch][0] = x[i];
					BIT::add(x[i], x[i], qdep - BIT::qry(x[i]));
					printf("%d\n", qdep);
				}
			}
			s.insert(x[i]);
		} else if (op[i] == 2) {
			v = *s.begin();
			printf("%d\n", tmp = BIT::qry(v));
			if (tmp == 1) continue;
			BIT::add(v, v, 1 - tmp);
			v[par][ch][0] = v[ch][1];
			v[ch][1][par] = v[par];
			BIT::add(v[par], n, 1);
			(rt[par] = v)[ch][1] = rt, (rt = v)[par] = 0;
		} else if (op[i] == 3) {
			v = *--s.end();
			printf("%d\n", tmp = BIT::qry(v));
			if (tmp == 1) continue;
			BIT::add(v, v, 1 - tmp);
			v[par][ch][1] = v[ch][0];
			v[ch][0][par] = v[par];
			BIT::add(1, v[par], 1);
			(rt[par] = v)[ch][0] = rt, (rt = v)[par] = 0;
		} else if (op[i] == 4) {
			v = *s.begin();
			printf("%d\n", tmp = BIT::qry(v));
			if (tmp == 1) {
				(rt = rt[ch][1])[par] = 0;
				BIT::add(1, n, -1);
			} else {
				BIT::add(v + 1, v[par] - 1, -1);
				v[par][ch][0] = v[ch][1];
				v[ch][1][par] = v[par];
			}
			s.erase(v);
		} else if (op[i] == 5) {
			v = *--s.end();
			printf("%d\n", tmp = BIT::qry(v));
			if (tmp == 1) {
				(rt = rt[ch][0])[par] = 0;
				BIT::add(1, n, -1);
			} else {
				BIT::add(v[par] + 1, v - 1, -1);
				v[par][ch][1] = v[ch][0];
				v[ch][0][par] = v[par];
			}
			s.erase(v);
		}
		// for (int i = 1; i <= n; i++) printf("%d%c", par[i], " \n"[i == n]);
	}
}