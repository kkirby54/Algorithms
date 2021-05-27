#include <cstdio>
#include <cctype>

int main() {
	char c;
	while ((c = getchar()) != EOF) {
		if (islower(c)) {
			printf("%c", ((c - 'a' + 13) % 26) + 'a');
		}
		else if (isupper(c)) {
			printf("%c", ((c - 'A' + 13) % 26) + 'A');
		}
		else printf("%c", c);
	}

}