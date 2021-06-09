#include <cstdio>
#include <list>

int C, N, K;

void josephus(int n, int k) {
	std::list<int> survivors;
	for (int i = 1; i <= n; i++) survivors.push_back(i);

	// 죽이고, k-1만큼 이동한다.
	std::list<int>::iterator kill = survivors.begin();
	
	while (n > 2) {
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();

		// 그 다음에 kill에서 k-1만큼 이동해
		for (int i = 0; i < k - 1; i++) {
			++kill;
			if (kill == survivors.end()) kill = survivors.begin();
		}
		n--;
	}

	printf("%d %d\n", survivors.front(), survivors.back());
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &K);

		josephus(N, K);
	}

}