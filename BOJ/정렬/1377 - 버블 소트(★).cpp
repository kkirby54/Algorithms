#include <cstdio>
#include <algorithm>

int N, A[500001], valIdx[1000001];

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%d", A + i);
        valIdx[A[i]] = i;
    }

    std::stable_sort(A, A + N);

    // valIdx[ A[i] ]
    // A[i]가 많이 나온다면?
    // val: 5 8 4 2 4 2 2 3
    // idx: 0 1 2 3 4 5 6 7
    // => 가장 마지막만 취하면 됨, 즉 valIdx[2] = 6.

    int ret = 0;
    for (int i = 0; i < N; i++){
        if (i != N-1){
            // 중복 값이 존재한다면, 건너뛴다.
            if (A[i] == A[i + 1]) continue;
        }

        ret = std::max(ret, valIdx[A[i]] - i);
    }
    printf("%d", ret + 1);

}