#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<int, int> P;

int N;
int d, p;
P PD[10001];
bool visited[10001];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &p, &d);
		PD[i] = P(p, d);
	}

	sort(PD, PD + N, greater<P>());
	int ret = 0;

	for (int i = 0; i < N; i++) {		
		int currD = PD[i].second;
		while (currD >= 1 && visited[currD]) {
			currD--;
		}
		if (currD < 1) continue;

		visited[currD] = true;
		ret += PD[i].first;
	}


	printf("%d", ret);

}