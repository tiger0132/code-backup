#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

struct SAM {
	int len[N], link[N], tr[N][26], nc, last;
	void ins(int HgS) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = last[len] + 1;
		for (; p && !(q = p[tr][HgS]); p = p[link]) p[tr][HgS] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc;
			cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][HgS] == q; p = p[link]) p[tr][HgS] = cl;
			q[link] = cur[link] = cl;
		}
		last = cur;
	}
	SAM() {
		nc = last = 1;
		int hgs;
		while ((hgs = getchar()) != '\n') ins(hgs - 97);

		int x = 1, l = 0, ans = 0;
		while ((hgs = getchar()) != '\n') {
			hgs -= 97;
			if (x[tr][hgs])
				l++, x = x[tr][hgs];
			else {
				while (x > 1 && !x[tr][hgs]) x = x[link];
				if (x[tr][hgs])
					l = x[len] + 1, x = x[tr][hgs];
				else
					l = 0;
			}
			ans = std::max(ans, l);
		}
		printf("%d", ans);
	}
} sam;

int main() {}