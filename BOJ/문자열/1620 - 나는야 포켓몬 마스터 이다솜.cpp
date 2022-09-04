#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

unordered_map<string, int> mm;
vector<string> word2idx;
string word;

int N, M;

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;
    word2idx.resize(N);

    for (int i = 0; i < N; i++){
        cin >> word;
        word2idx[i] = word;
        mm[word] = i;
    }

    for (int i = 0; i < M; i++){
        cin >> word;

        bool isDigit = false;
        for (int j = 0; j < word.size(); j++){
            if (isdigit(word[j])){
                isDigit = true;
                break;
            }

        }

        if (isDigit){
            cout << word2idx[stoi(word) - 1] << "\n";
        }
        else cout << mm[word] + 1<< "\n";
  }

}