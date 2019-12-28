main(a, b, c, d) {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	puts(a + b == c + d || a + c == b + d || a + d == b + c || a + b + c == d ||
				 a + b + d == c || a + c + d == b || b + c + d == a
			 ? "YES"
			 : "NO");
}