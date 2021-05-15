#include <cstdio>
#include <cmath>
#include <algorithm>

bool visited[300000];
int index[300000];
int A, P, cnt;

int dfs(int curr) {
	visited[curr] = true;
	index[curr] = cnt++;
	int ret = 0;

	while (curr) {
		ret += (int) pow(curr % 10, P);
		curr /= 10;
	}

	if (!visited[ret]) {
		return dfs(ret);
	}
	else return index[ret];
}

int main() {
	int ret = 0;
	scanf("%d %d", &A, &P);

	printf("%d", dfs(A));

}