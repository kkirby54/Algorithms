#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int arr[1005];
vector<int> vec;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) vec.push_back(i);

	for (int i = 0; i < N; i++)
		scanf("%d", arr + i);

	int vSize = N;
	int curr = 0;

	for (int i = 0; i < N; i++) {
		printf("%d ", vec[curr] + 1);

		int next = vec[curr];
		vec.erase(vec.begin() + curr % vSize);
		vSize--;
		if (i == N - 1) break;

		// 그 다음에 다음 갈 곳을 찾는다.
		// arr[next]의 부호에 따라 나뉘게 된다.
		// 이는 벡터에서 erase 연산을 한 순간, 그 원소가 사라짐에 따라
		// 인덱스들이 하나 앞으로 밀리기 때문임.
		if (arr[next] > 0)
			curr = (curr + (arr[next] - 1) + vSize*1000) % vSize;
		else
			curr = (curr + arr[next] + vSize*1000) % vSize;
	}


}