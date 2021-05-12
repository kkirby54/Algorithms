#include <iostream>
#include <algorithm>
#include <string>

int main() {
	std::string str[1000];
	std::cin >> str[0];

	int length = str[0].size();

	for (int i = 1; i < length; i++) {
		str[i] = str[0].substr(i);
	}

	std::sort(str, str + length);

	for (int i = 0; i < length; i++) std::cout << str[i] << "\n";

}