#include <cstdio>

int alphabet[26];
char word[101];

int main() {
	scanf("%s", word);
	
	for (int i = 0; i < 26; i++) alphabet[i] = -1;

	for (int i = 0; word[i]; i++) {
		if (alphabet[word[i] - 'a'] == -1)
			alphabet[word[i] - 'a'] = i;
	}

	for (int i = 0; i < 26; i++) {
		printf("%d ", alphabet[i]);
	}

}