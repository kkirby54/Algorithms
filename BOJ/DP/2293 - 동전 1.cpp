#include <cstdio>
#include <algorithm>
#include <cstring>
int N, K;
int coins[100];
int dp[10001];

int main(){
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++){
        scanf("%d", coins + i);
    }
    std::sort(coins, coins + N);
    // memset(dp, -1, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < N; i++){

        for (int j = coins[i]; j <= K; j++){
            dp[j] += dp[j - coins[i]];
        }
    }
    printf("%d", dp[K]);
}