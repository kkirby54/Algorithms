#include <vector>
#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator& itr) {
	char head = *itr;
	++itr;

	if (head == 'x') {
		// 이러면 이제 바꿔야 하는데...
		
		string upperLeft = reverse(itr);
		string upperRight = reverse(itr);
		string lowerLeft = reverse(itr);
		string lowerRight = reverse(itr);

		return string("x") + lowerLeft + lowerRight +
			upperLeft + upperRight;
	}
	else {
		// 그냥 리턴함. 'b'든 'w'든
		return string(1, head);
	}

}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		string S;
		cin >> S;

		auto itr = S.begin();

		string ans = reverse(itr);
		cout << ans << "\n";

	}
}