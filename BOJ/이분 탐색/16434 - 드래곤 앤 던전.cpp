#include <cstdio>
#include <algorithm>

int N, A;
int t[123456], a[123456], h[123456];
// t:
// 1이면 공 a, 체 h인 몬스터,
// 0이면 a만큼 증가, h만큼 회복 포션.

int main() {
	scanf("%d %d", &N, &A);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", t + i, a + i, h + i);
	}

	// N번째 방까지 도달해서 용을 무찔러야 한다.
	// 전투 순서
	// 1. A만큼 몬스터 생명력 깎아, 0이하면 OK
	// 2. 몬스터 공격력 a만큼 currhp깎아, 0이하면 사망.
	// 3. 반복

	// MaxHP
	long long lo = 0, hi = (long long)1e18;

	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		// 최대 mid의 체력을 갖고 있다.
		// 이제 N개의 방을 돌면서,
		// 체력을 깎아본다.
		
		long long currHP = mid;
		long long currAtt = A;
		bool isPossible = true;
		//printf("%lld로 시작!=====\n", currHP);

		for (int i = 0; i < N; i++) {
			// 몬스터가 있는 방
			if (t[i] == 1) {
				// 용사의 공격
				// 몬스터 체력: h[i]
				// 몬스터 공격력: a[i].
				int mH = h[i];
				int mA = a[i];

				// 내가 몬스터 때리는 횟수
				// 몬스터 체력이 내 공격력 보다 낮으면 1임
				long long myAttack, monsterAttack;
				if (mH <= currAtt) myAttack = 1;
				else {
					// 그게 아니면 일단 나눠봐
					myAttack = mH% currAtt == 0 ? mH / currAtt : mH / currAtt + 1;
				}
	
				if (currHP <= mA) monsterAttack = 1;
				else {
					monsterAttack = currHP % mA == 0 ? currHP / mA : currHP / mA + 1;
				}

				// 내가 더 먼저 때리니까,
				// 내 횟수 = 몬스터 + 1까지 허용.
				if (myAttack <= monsterAttack + 1) {
					// 그럼 깎기.
					currHP -= (myAttack - 1) * mA;
					if (currHP <= 0) {
						isPossible = false;
						break;
					}
				}
				else {
					isPossible = false;
					break;
				}
			}
			// 포션
			else {
				currAtt += a[i];
				currHP = std::min(currHP + h[i], mid);
			}
		}

		// 가능하다면 체력을 더 줄여
		if (isPossible) hi = mid;
		else lo = mid;
	}

	printf("%lld\n", hi);
}