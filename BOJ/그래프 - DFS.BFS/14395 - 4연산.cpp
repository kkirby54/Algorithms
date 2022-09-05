#include <cstdio>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
using namespace std;

int s, t;
queue<int> Q;
unordered_set<int> visited;
unordered_map<int, int> prevMap;
stack<char> S;

int main(){
    scanf("%d %d", &s, &t);

    if (s == t){
        printf("0");
        return 0;
    }

    Q.push(s);
    visited.insert(s);

    int level = 0;
    while (!Q.empty()){
        int qSize = Q.size();
        while (qSize--){
            int curr = Q.front();
            Q.pop();

            if (curr == t){
                while (t != s){
                    int prevValue = prevMap[t];
                    char ret = '0';

                    if (prevValue * prevValue == t)
                        ret = '*';
                    else if (prevValue + prevValue == t)
                        ret = '+';
                    else if (prevValue == 0)
                        ret = '-';
                    else ret = '/';

                    S.push(ret);
                    t = prevValue;
                }

                while (!S.empty()){
                    printf("%c", S.top());
                    S.pop();
                }

                return 0;
            }

            // *
            if (curr <= 31622){
                if (visited.find(curr * curr) == visited.end()){
                    visited.insert(curr*curr);
                    prevMap[curr*curr] = curr;
                    Q.push(curr * curr);
                }
            }

            // +
            if (curr <= 500000000){
                if (visited.find(curr + curr) == visited.end()){
                    visited.insert(curr + curr);
                    prevMap[curr+curr] = curr;
                    Q.push(curr + curr);
                }
            }

            // -
            if (visited.find(0) == visited.end()){
                visited.insert(0);
                prevMap[0] = curr;
                Q.push(0);
            }

            // /
            if (curr != 0){
                if (visited.find(1) == visited.end()){
                    visited.insert(1);
                    prevMap[1] = curr;
                    Q.push(1);
                }
            }
        }

        level++;
    }

    printf("-1");

}
