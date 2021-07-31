#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N;
long long B;

// 행렬 A * B를 리턴한다.
vector<vector<int>> MatrixMul(vector<vector<int>> A,
	vector<vector<int>> B) {

	vector<vector<int>> C(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// C[i][j]
			C[i][j] = 0;
			for (int cnt = 0; cnt < N; cnt++) {
				C[i][j] += (A[i][cnt] * B[cnt][j]);
				C[i][j] %= 1000;
			}

		}
	}
	return C;
}

// 분할 정복으로 A의 B제곱
vector<vector<int>> MatrixSquare(vector<vector<int>> A, long long B) {
	if (B == 1) return A;

	// 짝수라면 그냥
	if (B % 2 == 0) {
		auto HalfMul = MatrixSquare(A, B / 2);
		return MatrixMul(HalfMul, HalfMul);
	}
	// 짝수라면
	else {
		return MatrixMul(A, MatrixSquare(A, B - 1));
	}

}

int main() {
	scanf("%d %lld", &N, &B);

	vector<vector<int>> A(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &A[i][j]);
			A[i][j] %= 1000;
		}
	}

	// A의 B제곱을 구해야 한다.
	auto ret = MatrixSquare(A, B);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", ret[i][j]);
		}
		puts("");
	}

}