#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;

P weightAndValue[300000];
int N, K;
int C[300000];

int main(){
    scanf("%d %d", &N, &K);
    int a, b;
    for (int i = 0; i < N; i++){
        scanf("%d %d", &a, &b);
        weightAndValue[i].first = a;
        weightAndValue[i].second = b;
    }
    for (int i = 0; i < K; i++){
        scanf("%d", C + i);
    }
    std::sort(C, C + K);
    std::sort(weightAndValue, weightAndValue + N);

    long long ret = 0;

    std::priority_queue<int> PQ;
    int idx = 0;
    for (int i = 0; i < K; i++){
        // 이 가방보다, 더 가벼운 보석들을 넣는다.
        while (idx < N && C[i] >= weightAndValue[idx].first){
            PQ.push(weightAndValue[idx].second);
            idx++;
        }
        if (!PQ.empty()){
            ret += 1LL * PQ.top();
            PQ.pop();
        }

    }



    printf("%lld\n", ret);

}
