#include <cstdio>
#include <algorithm>
#include <stack>

int N;
char equ[100];
int ans = -987654321;

int precedence(char ch) {
	switch (ch)
	{
	case '(': return 0;
	case '+': case '-': return 1;
	case '*': return 2;
	}
}

// 중위 -> 후위로 변환하고, 계산한다.
void compute(char str[]) {
	std::stack<char> S;

	char ret[100] = { 0 };
	int idx = 0;

	for (int i = 0; str[i]; i++) {
		char curr = str[i];

		if ('0' <= curr && curr <= '9')
			ret[idx++] = curr;
		else if (curr == ' ')
			continue;
		else if (curr == '(') {
			S.push(curr);
		}
		// (을 만날 때 까지 쭉 뽑는다.
		else if (curr == ')') {
			while (!S.empty()) {
				char op = S.top();
				S.pop();
				if (op == '(') break;
				ret[idx++] = op;
			}

		}
		else {
			// 우선순위를 일단 본다.
			int priority = precedence(curr);

			// 스택에 있는거.
			// + *이면 진행. 즉 top의 pre < curr의 priorty면 괜찮
			while (!S.empty() && precedence(S.top()) >= priority) {
				if (S.top() != '(')
					ret[idx++] = S.top();
				S.pop();
			}
			if (curr != ')')
				S.push(curr);
		}
	}

	while (!S.empty()) {
		if (S.top() != '(')
			ret[idx++] = S.top();
		S.pop();
	}

	//printf("후위로 변환 후 %s\n", ret);

	std::stack<int> S2;
	for (int i = 0; ret[i]; i++) {
		char curr = ret[i];

		if ('0' <= curr && curr <= '9')
			S2.push(curr - '0');
		else if (curr == ' ') {
			continue;
		} 
		else {
			int arg2 = S2.top();
			S2.pop();
			int arg1 = S2.top();
			S2.pop();

			if (curr == '+') {
				S2.push(arg1 + arg2);
			}
			else if (curr == '-')
				S2.push(arg1 - arg2);
			else
				S2.push(arg1 * arg2);
		}
	}

	//printf("총 결과: %d\n", S2.top());
	ans = std::max(ans, S2.top());
}

void backtrack(int curr, bool prev) {
	// 마지막까지 왔다면, 종료
	if (curr == 2 * N) {
		if (prev == 1) equ[curr] = ')';

		compute(equ);

		equ[curr] = ' ';
		return;
	}
	if (curr > 2 * N) {

		compute(equ);
		return;
	}

	// prev가 1이었다면, 이번엔 무조건 )로 닫는다.
	if (prev == 1) {
		equ[curr] = ')';

		backtrack(curr + 2, 0);

		equ[curr] = ' ';
	}
	else {
		// 0이었다면, 그냥 두고 넘어가도 되고,
		// (를 씌울 수도 있다.
		backtrack(curr + 4, 0);

		if (curr != 2 * (N - 1)) {
			equ[curr] = '(';
			backtrack(curr + 6, 1);
			equ[curr] = ' ';
		}
	}

}

int main() {
	scanf("%d", &N);

	char ch;
	getchar();
	for (int i = 0; i < N; i++) {
		ch = getchar();
		equ[2 * i] = ' ';
		equ[2 * i + 1] = ch;
	}

	backtrack(0, 0);

	printf("%d\n", ans);
}
