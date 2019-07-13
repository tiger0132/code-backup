main(a) {
	scanf("%d", &a);
	if (a % 4 == 1) puts("0 A");
	if (a % 4 == 0) puts("1 A");
	if (a % 4 == 3) puts("2 A");
	if (a % 4 == 2) puts("1 B");
}