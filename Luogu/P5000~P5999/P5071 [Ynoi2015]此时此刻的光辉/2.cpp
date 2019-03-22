#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>

typedef long long ll;

const int N = 1e5+51, M = 168, P = 19260817;
const int prime[M] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

namespace PollardRho {
	typedef __int128_t duliu;
	typedef long long ll;
	const ll _[] = {2, 7, 61}, M = 3; // 4759123141
	ll p_(ll x, ll y, ll z) {
		ll ret = 1;
		for (; y; (x *= x) %= z, y >>= 1) if (y & 1) (ret *= x) %= z;
		return ret;
	}
	bool chk(ll p, int x) {
		ll s = 0, t = p-1;
		for (; !(t & 1); s++) t >>= 1;
		ll y = p_(x, t, p);
		if (y == 1 || y == p-1) return 1;
		while (s--) {
			(y *= y) %= p;
			if (y == p-1) return 1;
		}
		return 0;
	}
	bool miller(ll x) { // 假装 _[x] 里面都是质数
		if (x == 1) return 0;
		for (int i = 0; i < M; i++) {
			if (x == _[i]) return 1;
		}
		for (int i = 0; i < M; i++) {
			if (!(x % _[i]) || !chk(x, _[i])) return 0;
		}
		return 1;
	}
	ll abs(ll x) { return x < 0 ? -x : x; }
	ll pollard(ll n) {
		ll a = rand() % (n - 1) + 1, x = 0, y = 0, t = 1;
		ll k = 1, q;
		while ("lxldl") {
			k <<= 1; q = 1; y = x;
			for (int i = 1; i <= k; i++) {
				x = ((duliu)x * x + a) % n;
				q = ((duliu)q * abs(x - y)) % n;
				if (!(i & 127)) {
					t = std::__gcd(q, n);
					if (t > 1) goto end;
				}
			}
			if ((t = std::__gcd(q, n)) > 1) break;
		}
		end:
		if (t == n) {
			do {
				x = ((duliu)x * x + a) % n;
				t = std::__gcd(abs(x - y), n);
			} while (t == 1);
		}
		return t;
	}
}
int id(int x) {
	static std::map<int, int> mmp;	
	if (!mmp.count(x)) mmp[x] = mmp.size()+1;
	return mmp[x];
}
int size;
struct node {
	int l, r, *ans;
	bool operator<(const node& rhs) const {
		return l / size == rhs.l / size ? r < rhs.r : l < rhs.l;
	}
} q[N];

int a[N], cntp[N][M], cnt[N<<1], ans[N], inv[N<<1];
int f1[N], f2[N];
int n, m, l, r;
ll lans;

void add(int x) {
	(lans *= inv[cnt[x]]) %= P;
	(lans *= ++cnt[x]) %= P;
}
void del(int x) {
	(lans *= inv[cnt[x]]) %= P;
	(lans *= --cnt[x]) %= P;
}
inline void A(int x) {
	if (f1[x]) add(f1[x]);
	if (f2[x]) add(f2[x]);
}
inline void D(int x) {
	if (f1[x]) del(f1[x]);
	if (f2[x]) del(f2[x]);
}

int main() {
	freopen("in.in", "r", stdin);
	freopen("o1.out", "w", stdout);
	srand(19260817);
	scanf("%d%d", &n, &m); size = 317/*ceil(sqrt(n))*/;
    inv[1] = cnt[1] = 1;
	for (int i = 2; i < (N<<1); i++) {
		inv[i] = (P - P/i) * 1ll * inv[P % i] % P;
		cnt[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", a+i);
		for (int j = 0; j < M; j++) {
			cntp[i][j] = cntp[i - 1][j];
			while (a[i] % prime[j] == 0) {
				a[i] /= prime[j];
				cntp[i][j]++;
				// printf("(%d)", prime[j]);
			}
		}
		if (a[i] == 1) continue;
		if (PollardRho::miller(a[i])) {
			f1[i] = id(a[i]);
		} else {
			do {
				f1[i] = PollardRho::pollard(a[i]);
				f2[i] = a[i] / f1[i];
			} while (0);//while (f1[i] == 1 || f2[i] == 1);
		}
		if (f1[i]) f1[i] = id(f1[i]);
		if (f2[i]) f2[i] = id(f2[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].ans = ans+i;
	}
	std::sort(q+1, q+m+1);
	l = 1; r = 0; lans = 1;
	for (int i = 1; i <= m; i++) {
		while (r < q[i].r) A(++r);
		while (l > q[i].l) A(--l);
		while (r > q[i].r) D(r--);
		while (l < q[i].l) D(l++);
		ll out = lans;
		for (int j = 0; j < M; j++) {
			(out *= cntp[r][j] - cntp[l-1][j] + 1) %= P;
		}
		*q[i].ans = out;
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
}