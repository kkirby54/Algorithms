#include <cstdio>

int N;
int cnt1, cnt2;

int fibo(int n){
    if (n <= 2){
        cnt1++;
        return 1;
    }
    return fibo(n-1) + fibo(n-2);
}

int dp[41];
int fiboDP(int n){
    if (n <= 2) return 1;
    if (dp[n]) return dp[n];

    cnt2++;
    return dp[n] = fiboDP(n-1) + fiboDP(n-2);
}

int main(){
    scanf("%d", &N);

    fibo(N);
    fiboDP(N);

    printf("%d %d", cnt1, cnt2);

}