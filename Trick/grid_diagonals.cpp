vector daig_01(n, vector(n, 0));
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++)
		daig_01[i][j] = i + j;
}

for (auto i : daig_01)
	PRINT(i);

vector daig_02(n, vector(n, 0));
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++)
		daig_02[i][j] = i - j + n -  1;
}
for (auto i : daig_02)
	PRINT(i);
