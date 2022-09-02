#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

unordered_set<string> S;
string word;
int cnt;

int main(){
    cin >> word;

    for (int i = 0; i < word.size(); i++){

        string tmp = "";
        tmp.reserve(i + 1);
        for (int j = i; j < word.size(); j++){
            tmp += word[j];

            if (S.find(tmp) == S.end()){
                S.insert(tmp);
                cnt++;
            }
        }

    }

    printf("%d\n", cnt);

}