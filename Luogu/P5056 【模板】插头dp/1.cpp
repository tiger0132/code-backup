#include <cstdio>
#include <cstring>
#define ________________________ 0
#define _______________________ 0
#define ____________________ 0
#define ________________________________ 0
#define _________________________________________________ 0
#define _________________________ 0
#define ______________________________ 0
#define __ 0

using ll = long long;
const int N = 22;

struct HashTable {
	static const int SZ = 1e6 + 61, P = 999983;
	struct node {
		int next, key;
		ll val;
	} e[SZ];
	int head[SZ], cnt;
	inline void ins(int x, ll y) {
		int hsh = x % P + 1;
		for (int i = head[hsh]; i; i = e[i].next)
			if (e[i].key == x) return void(e[i].val += y);
		e[++cnt] = (node){head[hsh], x, y}, head[hsh] = cnt;
	}
	inline void clear() { memset(head, 0, sizeof head); }
} tab[2];  // 状态 -> 值

int n, m, x_, y_, cur, mp[N][N];
char buf[N];
ll ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf + 1);
		for (int j = 1; j <= m; j++)
			if (buf[j] == '.') x_ = i, y_ = j, mp[i][j] = 1;
	}
	tab[cur].ins(0, 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= tab[cur].cnt; j++) {
			tab[cur].e[j].key <<= 2;
		}
		for (int j = 1; j <= m; j++) {
			tab[0].clear(), tab[1].clear();
			tab[cur ^= 1].cnt = 0;
			for (int k = 1; k <= tab[!cur].cnt; k++) {
				int st = tab[!cur].e[k].key;
				int D = (st >> (2 * j)) & 3, R = (st >> 2 * (j - 1)) & 3;
				ll val = tab[!cur].e[k].val;
				if (!mp[i][j]) {						  // ! CASE 障碍
					if (!D && !R) tab[cur].ins(st, val);  // ? IF 左上无插头 THEN 转移
				} else if (!D && !R) {					  // ! CASE 左上无插头
					if (mp[i][j + 1] && mp[i + 1][j])	 // ? IF 下右无障碍
						tab[cur].ins(st + (1 << (2 * (j - 1))) + (2 << (2 * j)), val);  // . THEN 加一个下右插头
				} else if (!D && R) {													// ! CASE 只有右插头
					if (mp[i + 1][j]) tab[cur].ins(st, val);  // ? IF 可以往下 THEN 括号序列不动
					if (mp[i][j + 1])						  // ? IF 可以往右
						tab[cur].ins(st - (R << (2 * (j - 1))) + (R << (2 * j)), val);  // . THEN 把右括号往后移一位
				} else if (D && !R) {													// ! CASE 只有下插头
					if (mp[i][j + 1]) tab[cur].ins(st, val);  // ? IF 可以往右 THEN 括号序列不动
					if (mp[i + 1][j])						  // ? IF 可以往下
						tab[cur].ins(st + (D << (2 * (j - 1))) - (D << (2 * j)), val);  // . THEN 把右括号往前移一位
				} else if (D == 1 && R == 1) {											// ! CASE 下右都是左括号
					for (int p = j + 1, c$ = 1; p <= m; p++) {							// . 找与 j 匹配的右括号
						if (((st >> (2 * p)) & 3) == 1) c$++;							// . 找到一个左括号
						if (((st >> (2 * p)) & 3) == 2) c$--;							// . 找到一个右括号
						if (!c$) {														// ? IF 匹配上了
							tab[cur].ins(st - (1 << 2 * p) - (1 << (2 * j)) - (1 << (2 * (j - 1))),
										 val);  // 把两个左括号删了
							break;
						}
					}
				} else if (D == 2 && R == 2) {					// ! CASE 下右都是右括号
					for (int p = j - 2, c$ = 1; p >= 0; p--) {  // . 找与 j 匹配的左括号
						if (((st >> (2 * p)) & 3) == 2) c$++;   // . 找到一个右括号
						if (((st >> (2 * p)) & 3) == 1) c$--;   // . 找到一个左括号
						if (!c$) {								// ? IF 匹配上了
							tab[cur].ins(st + (1 << 2 * p) - (2 << (2 * j)) - (2 << (2 * (j - 1))),
										 val);  // 把两个右括号删了
							break;
						}
					}
				} else if (D == 1 && R == 2) {  // ! CASE 右是右括号, 下是左括号
					tab[cur].ins(st - (2 << (2 * (j - 1))) - (1 << (2 * j)), val);  // 合并两条路径
				} else if (i == x_ && j == y_) {  // ! CASE 右是左括号, 下是右括号
					ans += val;					  // 如果是结束那么统计答案
				}
			}
		}
	}
	printf("%lld", ans);
}