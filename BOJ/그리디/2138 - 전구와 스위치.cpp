#include <cstdio>
#include <algorithm>
const int INF = 987654321;

int N, tmp;
int A[100000], C[100005], D[100005];

void reverseArr(int idx){
    C[idx] = !C[idx];
    if (idx != N-1){
        C[idx + 1] = !C[idx + 1];
    }
    if (idx != 0){
        C[idx - 1] = !C[idx - 1];
    }
}
void reverseArr2(int idx){
    D[idx] = !D[idx];
    if (idx != N-1){
        D[idx + 1] = !D[idx + 1];
    }
    if (idx != 0){
        D[idx - 1] = !D[idx - 1];
    }
}

int cnt;
int cnt2;

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%1d", A + i);
    }
    for (int i = 0; i < N; i++){
        scanf("%1d", &tmp);
        if (A[i] != tmp){
            C[i] = 1;
            D[i] = 1;
        }
    }

    reverseArr(0);
    cnt = 1;
    for (int i = 1; i < N; i++){
        // i-1을 본다.
        if (C[i-1] == 1){
            reverseArr(i);
            cnt++;
        }
    }
    for (int i = 0; i < N; i++){
        if (C[i] == 1){
            cnt = INF;
            break;
        }
    }

    // 0번째 누르지 않음.
    for (int i = 1; i < N; i++){
        if (D[i-1] == 1){
            reverseArr2(i);
            cnt2++;
        }
    }
    for (int i = 0; i < N; i++) {
        if (D[i] == 1) {
            cnt2 = INF;
            break;
        }
    }

    if (cnt == INF && cnt2 == INF){
        printf("-1");
    }
    else{
        printf("%d\n", std::min(cnt, cnt2));
    }

}