#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
int C;

string quad;

string divAc(string str) {
	if (str[0] != 'x') {
		string ret;
		ret.push_back(str[0]);
		return ret;
	}

	string p1, p2, p3, p4;
	int idx = 1;

	p1 = divAc(str.substr(idx));
	idx += p1.size();

	p2 = divAc(str.substr(idx));
	idx += p2.size();

	p3 = divAc(str.substr(idx));
	idx += p3.size();

	p4 = divAc(str.substr(idx));

	//cout << "p1 : " << p1 << "\n";
	//cout << "p2 : " << p2 << "\n";
	//cout << "p3 : " << p3 << "\n";
	//cout << "p4 : " << p4 << "\n";

	return "x" + p3 + p4 + p1 + p2;
}

int main() {
	cin >> C;
	while (C--) {
		cin >> quad;

		cout << divAc(quad) << "\n";
	}

}