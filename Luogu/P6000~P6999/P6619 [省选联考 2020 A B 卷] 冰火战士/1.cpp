#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62, K = 20;

int cnt;
struct {
	int tr[N];
	void add(int i, int x) {
		for (; i <= cnt; i += i & -i) tr[i] += x;
	}
	int qry(int i) {
		int r = 0;
		for (; i; i &= i - 1) r += tr[i];
		return r;
	}
} bf, bg;

int n, op[N], t[N], x[N], y[N], tmp[N];
int tg;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", op + i, t + i);
		if (op[i] == 1) scanf("%d%d", x + i, y + i), tmp[++cnt] = x[i];
	}
	std::sort(tmp + 1, tmp + cnt + 1);
	cnt = std::unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
	for (int i = 1; i <= n; i++) {
		if (op[i] == 1) {
			x[i] = std::lower_bound(tmp + 1, tmp + cnt + 1, x[i]) - tmp;
			if (!t[i])
				bf.add(x[i], y[i]);
			else
				bg.add(x[i] + 1, -y[i]), tg += y[i];
		} else {
			int p = t[i];
			if (!t[p])
				bf.add(x[p], -y[p]);
			else
				bg.add(x[p] + 1, y[p]), tg -= y[p];
		}

		int cur1 = -tg, pos1 = 0;
		for (int j = K; j >= 0; j--) {
			if ((pos1 | (1 << j)) > cnt) continue;
			int d = bf.tr[pos1 | (1 << j)] - bg.tr[pos1 | (1 << j)];
			if (cur1 + d < 0) cur1 += d, pos1 |= 1 << j;
		}
		int ans1 = 2 * bf.qry(pos1);
		if (pos1 == cnt) {
			if (ans1)
				printf("%d %d\n", tmp[pos1], ans1);
			else
				puts("Peace");
			continue;
		}

		int gl = bg.qry(pos1 + 1);
		int cur2 = 0, pos2 = 0;
		for (int j = K; j >= 0; j--) {
			if ((pos2 | (1 << j)) > cnt) continue;
			int d = bg.tr[pos2 | (1 << j)];
			if (cur2 + d >= gl) cur2 += d, pos2 |= 1 << j;
		}
		int ans2 = 2 * (cur2 + tg);
		if (!std::max(ans1, ans2))
			puts("Peace");
		else if (ans1 > ans2)
			printf("%d %d\n", tmp[pos1], ans1);
		else
			printf("%d %d\n", tmp[pos2], ans2);
	}
}