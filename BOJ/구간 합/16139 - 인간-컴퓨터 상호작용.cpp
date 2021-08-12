#include <cstdio>
#include <algorithm>

int pSum[27][200002];
char str[200002];
int main() {
	char ch[2];
	int Q, s, e;
	scanf("%s %d", str, &Q);

	for (int i = 0; str[i]; i++) {
		for (int j = 0; j < 26; j++)
			pSum[j][i + 1] = pSum[j][i];

		pSum[str[i] - 'a'][i + 1] += 1;
	}

	for (int i = 0; i < Q; i++) {
		scanf("%s %d %d", &ch, &s, &e);

		printf("%d\n", pSum[ch[0] - 'a'][e+1] - pSum[ch[0] - 'a'][s]);
	}
}