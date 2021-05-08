#include <cstdio>
#include <algorithm>

class P {
public:
	int age;
	int order;
	char name[101];
};

P people[100000];

bool comp(const P& a, const P& b) {
	if (a.age == b.age) {
		return a.order < b.order;
	}
	return a.age < b.age;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %s", &people[i].age, people[i].name);
		people[i].order = i;
	}

	std::sort(people, people + N, comp);

	for (int i = 0; i < N; i++) {
		printf("%d %s\n", people[i].age, people[i].name);
	}
}