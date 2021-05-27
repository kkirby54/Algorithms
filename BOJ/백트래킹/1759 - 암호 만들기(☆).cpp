#include <cstdio>
#include <vector>
#include <algorithm>

int L, C;
char ch[16];
bool isVowel[26];

char ret[16];

void password(int curr, int prev, int vowels, int consonants) {
	if (curr == L) {
		if (vowels >= 1 && consonants >= 2)
			puts(ret);
		return;
	}

	for (int i = prev + 1; i < C; i++) {
		ret[curr] = ch[i];

		if (isVowel[ch[i] - 'a'])
			password(curr+1, i, vowels + 1, consonants);
		else password(curr+1, i, vowels, consonants + 1);
	}


}

int main() {
	scanf("%d %d", &L, &C);
	getchar();

	for (int i = 0; i < C; i++) {
		scanf("%c", &ch[i]);
		getchar();
	}
	std::sort(ch, ch + C);

	isVowel[0] = isVowel[4] = isVowel[8] = isVowel[14] = isVowel[20] = true;

	// 길이는 L.
	password(0, -1, 0, 0);


}