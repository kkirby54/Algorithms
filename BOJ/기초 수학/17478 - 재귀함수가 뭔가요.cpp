#include <cstdio>
int N;

void printLine(int n) {
	for (int i = 0; i < n; i++) {
		printf("____");
	}
}

void func(int n) {
	printLine(n);
	printf("\"����Լ��� ������?\"\n");

	if (n == N) {
		printLine(n);
		printf("\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n");
	}
	else {
		printLine(n);
		printf("\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n");

		printLine(n);
		printf("���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n");
		printLine(n);
		printf("���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n");
	
		func(n + 1);
	}

	printLine(n);
	printf("��� �亯�Ͽ���.\n");

}

int main() {
	scanf("%d", &N);

	printf("��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n");
	func(0);
}

