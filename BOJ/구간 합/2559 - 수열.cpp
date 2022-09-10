#include <cstdio>
#include <algorithm>
int N, K, tmp;
int pSum[100001];

int main(){
    scanf("%d %d", &N, &K);

    int ret = -10000000;

    for (int i = 0; i < N; i++){
        scanf("%d", &tmp);
        pSum[i+1] = pSum[i] + tmp;
    }

    // K개 범위 구간 확인.
    for (int i = 0; i + K <= N; i++){
        ret = std::max(ret, pSum[i+K] - pSum[i]);
    }

    printf("%d", ret);

}