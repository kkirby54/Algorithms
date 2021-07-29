#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int C, len;
string image;
string::iterator itr;

string reverse() {
	char head = *itr;
	// Base case
	if (head != 'x') return string(1, head);

	itr++; string upperLeft = reverse();
	itr++; string upperRight = reverse();
	itr++; string lowerLeft = reverse();
	itr++; string lowerRight = reverse();

	return 'x' + lowerLeft + lowerRight + upperLeft + upperRight;
}


int main() {
	cin >> C;
	for (int t = 0; t < C; t++) {
		cin >> image;
		itr = image.begin();

		string ret = reverse();
		cout << ret << "\n";
	}

}