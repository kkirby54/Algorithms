#include <cstdio>
#include <stack>
#include <algorithm>

char str[101];
int getRank(char ch) {
	if (ch == '+' || ch == '-') return 1;
	if (ch == '*' || ch == '/') return 2;
	else return 0; // 괄호의 경우
}

int main() {
	scanf("%s", str);
	std::stack<char> S;

	for (int i = 0; str[i]; i++) {
		// 피연산자면 출력
		if ('A' <= str[i] && str[i] <= 'Z') printf("%c", str[i]);
		else {
			if (str[i] == '(') S.push(str[i]);
			else if (str[i] == ')') {
				// '('를 만날 때까지 다 빼낸다.
				while (!S.empty() && S.top() != '(') {
					printf("%c", S.top());
					S.pop();
				}
				S.pop(); // '('을 빼낸다.
			}
			else {
				// 연산자들의 우선순위를 비교한다.
				// 스택 상의 연산자 vs 이번 연산자(str[i])
				// 이번 연산자의 우선순위가 더 클 때까지 pop하면서 출력한다.
				// char prevOpr = S.top();
				while (!S.empty() &&
					getRank(S.top()) >= getRank(str[i])) { // S.top()은 스택에 존재하는 연산자, str[i]는 이번 연산자.
					printf("%c", S.top());
					S.pop();
				}
				S.push(str[i]);
			}
		}
	}
	while (!S.empty()) {
		printf("%c", S.top());
		S.pop();
	}

}