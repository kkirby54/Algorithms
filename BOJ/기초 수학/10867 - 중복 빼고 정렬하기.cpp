#include <cstdio>
#include <set>

int N, num;
std::set<int> S;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		S.insert(num);
	}
	for (int e : S) printf("%d ", e);
}