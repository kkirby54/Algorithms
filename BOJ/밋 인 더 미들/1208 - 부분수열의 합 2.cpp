#include <cstdio>
#include <map>

int N, S, mid, arr[41];
std::map<int, int> M;

int sum;
long long ret;

void dfsLeft(int curr) {
	if (curr == mid) {
		M[sum]++;
		return;
	}

	dfsLeft(curr + 1);
	sum += arr[curr];
	dfsLeft(curr + 1);
	sum -= arr[curr];
}

void dfsRight(int curr) {
	if (curr == N) {
		ret += M[S - sum];
		return;
	}

	dfsRight(curr + 1);
	sum += arr[curr];
	dfsRight(curr + 1);
	sum -= arr[curr];

}

int main() {
	scanf("%d %d", &N, &S);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	mid = N / 2;
	dfsLeft(0);
	dfsRight(mid);

	if (S == 0) ret--;
	printf("%lld", ret);

}