#include <iostream>
#include <unordered_set>
#include <algorithm>
using namespace std;

int N, M;
unordered_set<int> S;

int main(){
    cin >> N >> M;

    int cnt = 0;
    int tmp;
    for (int i =0; i < N; i++){
        cin >> tmp;
        S.insert(tmp);
    }
    for (int i = 0; i < M; i++){
        cin >> tmp;
        if (S.find(tmp) != S.end()){
            cnt++;
        }
    }
    printf("%d\n", N + M - cnt*2);
}