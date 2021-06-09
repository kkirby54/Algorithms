#include <iostream>
#include <stack>
#include <string>

using namespace std;

int C;
string str;

const string opening("({["), closing(")}]");

int main() {
	cin >> C;
	
	for (int t = 0; t < C; t++) {
		cin >> str;
		stack<char> Stack;
		bool isPossible = true;

		for (int i = 0; i < str.size(); i++) {
			if (opening.find(str[i]) != -1) {
				Stack.push(str[i]);
			}
			else {
				if (Stack.empty()) {
					isPossible = false; break;
				}
				if (opening.find(Stack.top()) != closing.find(str[i])) {
					isPossible = false; break;
				}
				Stack.pop();
			}
		}
		if (isPossible && Stack.empty()) puts("YES");
		else puts("NO");

	}

}