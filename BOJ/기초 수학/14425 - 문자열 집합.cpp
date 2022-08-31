#include <iostream>
#include <algorithm>
#include <unordered_set>
int N, M;
std::string word;
std::unordered_set<std::string> S;

int main()
{
    std::cin >> N >> M;
    for (int i = 0; i < N; i++){
        std::cin >> word;
        S.insert(word);
    }

    int cnt = 0;
    for (int i = 0; i < M; i++){
        std::cin >> word;

        if (S.find(word) != S.end()){
            cnt++;
        }

    }

    printf("%d", cnt);

}