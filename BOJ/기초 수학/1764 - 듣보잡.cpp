#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int N, M;
vector<string> ret;
unordered_set<string> S;
string word;

int main(){
    cin >> N >> M;
    for (int i =0 ; i < N; i++){
        cin >> word;
        S.insert(word);
    }

    for (int i = 0; i < M; i++){
        cin >> word;
        if (S.find(word) != S.end()){
            ret.push_back(word);
        }
    }

    sort(ret.begin(), ret.end());

    cout << ret.size() << "\n";
    for (string& e : ret){
        cout << e << "\n";
    }

}