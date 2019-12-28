main(a, b, c, x, y) {
	scanf("%d%d%d", &a, &b, &c);
	x = a - b - c, y = a - b + c;
	if (!x && !y)
		puts("0");
	else if (x < 0 && y < 0)
		puts("-");
	else if (x > 0 && y > 0)
		puts("+");
	else
		puts("?");
}