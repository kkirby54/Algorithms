#include <cstdio>

int N, K;

int main(){
    scanf("%d %d", &N, &K);

    int p = N / 2;
    int totalCnt = 0;

    // 절대 안되는 경우는 K가 AAAA...BBBBB... 보다도 더 넘을 떄
    if (p * (N - p) < K){
        printf("-1");
    }
    else {
        // Greedy로 풀기
        int aCnt = (K / p);
        for (int i = 0; i < aCnt; i++) printf("A");

        int bCnt = p - (K % p);
        for (int i = 0; i < bCnt; i++) printf("B");

        totalCnt += aCnt + bCnt;
        if (totalCnt == N) return 0;

        printf("A");

        for (int i = 0; i < (p - bCnt); i++)
            printf("B");

        totalCnt += (p - bCnt + 1);

        for (int i = 0; i < (N - totalCnt) ; i++) printf("A");
    }


}