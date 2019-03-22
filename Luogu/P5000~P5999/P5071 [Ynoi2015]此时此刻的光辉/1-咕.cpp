#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <map>
#define int long long

const int N = 1e5+51, M = 11, P = 19260817;

int size;

struct node {
	int l, r, *ans;
	bool operator<(const node& rhs) const {
		return l / size == rhs.l / size ? r < rhs.r : l < rhs.l;
	}
} q[N];

int u[N], v[N][M], w[N][M];
int a[N], ans[N], cnt[N];
int n, m, l, r, lans;

int inv(int x) {
	int y = P-2, _ = 1;
	for (; y; (x *= x) %= P, y >>= 1) if (y & 1) (_ *= x) %= P;
	return _;
}
void add(int x, int o) {
	for (int i = 1; i <= u[x]; i++) {
		(lans *= inv(cnt[v[x][i]] + 1)) %= P;
		(cnt[v[x][i]] += o * w[x][i]) %= P;
		(cnt[v[x][i]] += P) %= P;
		(lans *= cnt[v[x][i]] + 1) %= P;
	}
}
std::map<int, int> mmp;
int id(int x) {
	if (!mmp.count(x)) mmp[x] = mmp.size()+1;
	return mmp[x];
}
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
		while (!(t & 1)) {
			t >>= 1;
			s++;
		}
		ll y = p_(x, t, p);
		if (y == 1 || y == p-1) return 1;
		while (s--) {
			(y *= y) %= p;
			if (y == p-1) return 1;
		}
		return 0;
	}
	bool prime(ll x) { // 假装 _[x] 里面都是质数
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
	int st[102], cntx[102], top;
	void proc(ll x, ll cnt = 1) {
		if (x == 1) return;
		if (prime(x)) {
			st[++top] = x;
			cntx[top] = cnt;
			return;
		}
		ll p = pollard(x), _x = 0;
		while (!(x % p)) {
			x /= p;
			_x++;
		}
		proc(p, cnt * _x); proc(x, cnt);
	}
	void work(ll x, ll i) {
		top = 0;
		proc(x);
		std::sort(st+1, st+top+1);
		for (int j = 1; j <= top; j++) {
			if (v[i][u[i]] != id(st[j])) {
				v[i][++u[i]] = id(st[j]);
			}
			w[i][u[i]] += cntx[j];
		}
	}
}
signed main() {
	// freopen("in.in", "r", stdin);
	srand(time(0));
	scanf("%lld%lld", &n, &m);
	size = ceil(sqrt(n));
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a+i);
		PollardRho::work(a[i], i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld", &q[i].l, &q[i].r);
		q[i].ans = ans+i;
	}
	std::sort(q+1, q+m+1);
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= u[i]; j++) {
	// 		printf("(%lld^%lld)", v[i][j], w[i][j]);
	// 	} puts("");
	// }
	l = 1; r = 0; lans = 1;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) add(--l, 1);
		while (r < q[i].r) add(++r, 1);
		while (l < q[i].l) add(l++, -1);
		while (r > q[i].r) add(r--, -1);
		*q[i].ans = lans;
	}
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", ans[i]);
	}
}

#if 0
5 1
2 4 3 5 10
1 5
#endif