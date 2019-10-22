typedef long long ll;
ll p[39] = {1}, x, c;
ll lb(ll x) {
	ll r = 0;
	for (int i = 38; i >= 0; i--)
		if (x >= p[i]) x -= p[i], r += p[i];
	return r;
}
main(i, j) {
	for (i = 1; i <= 38; i++) p[i] = p[i - 1] * 3;
	for (scanf("%*d"); ~scanf("%lld", &x);) {
		ll l = x, r = 1350851717672992089;
		while (l <= r) {
			ll mid = (l + r) / 2;
			if (lb(mid) >= x)
				r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%lld\n", r + 1);
	}
}