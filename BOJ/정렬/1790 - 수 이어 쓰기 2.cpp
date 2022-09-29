#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int N, K;

int main(){
    scanf("%d %d", &N, &K);
    K--;

    int m = N;
    int digits = 0;
    while (m){
        m /= 10;
        digits++;
    }

    // digits-1까지를 다 구한다.
    // 그러지 말고,
    int ansDigits;
    long long prevCnt = 0;
    long long currCnt = 0;
    for (ansDigits = 1; ansDigits < digits; ansDigits++){
        currCnt += 1LL * (9 * ((long long) pow(10, ansDigits-1)) * ansDigits );

        if (currCnt >= K){
            break;
        }
        prevCnt = currCnt;
    }
    // 현재 digits의 1000..00 에서,
    // N까지의 개수를 구한다.
    currCnt += 1LL * (digits * (N - ((long long) pow(10, digits - 1)) + 1) );

    if (currCnt <= K){
        printf("-1");
    }
    else{
        long long standard = (long long) pow(10, ansDigits - 1);

        // 현재 digits에서, K - prevCnt번째 숫자를 알아내면 된다.

        // 그럼 digits만큼 가니까,
        // (K - prevCnt) / digits를 구한다.
        long long jump = (K - prevCnt) / ansDigits;
        int pos = (K - prevCnt) % ansDigits;

        string val = to_string(standard + jump);
        printf("%d", val[pos] - '0');


    }


}