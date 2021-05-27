#include <cstdio>
#include <cstring>
#include <algorithm>

class Score {
public:
	char name[11];
	int k, e, m;

	bool operator<(const Score& a) {
		if (k == a.k) {
			if (e == a.e) {
				if (m == a.m) {
					return strcmp(a.name, name) > 0 ? 1 : 0;
				}
				return m > a.m;
			}
			return e < a.e;
		}
		return k > a.k;
	}
};

Score S[100001];
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s %d %d %d", S[i].name, &S[i].k, &S[i].e, &S[i].m);
	}

	std::sort(S, S + N);
	for (int i = 0; i < N; i++) {
		printf("%s\n", S[i].name);
	}
}