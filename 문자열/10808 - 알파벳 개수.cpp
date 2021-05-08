#include <cstdio>

int alphabet[26];
char word[101];

int main() {
	scanf("%s", word);

	for (int i = 0; word[i]; i++) {
		alphabet[word[i] - 97]++;
	}

	for (int i = 0; i < 26; i++) {
		printf("%d ", alphabet[i]);
	}

}