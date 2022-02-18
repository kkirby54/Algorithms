#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

// 2022.02.18 첫 풀이 -> Boundary에 있는 값은 처리가 애매해서
// 0~9가 아니라 사실상 0~10을 쓰게 됐다. 이걸 처리하기 위해서는
// 그냥 10이 되면 9를 쓰는 걸로 바꾸면 된다. min(9, ~) 이런 식으로.

int L, R;

struct Particle {
	int x, y, z;
	int vx, vy, vz;
};

Particle particles[50001];
int mCnt;
bool isActive[50001];
vector<int> boundary[10][10][10]; // 구획을 나눈다.
int bL;

void init(int l, int r)
{
	L = l, R = r;
	mCnt = 0;

	memset(particles, 0, sizeof(particles));
	memset(isActive, 0, sizeof(isActive));

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				boundary[i][j][k].clear();

	bL = L / 5; // bL x bL x bL인 정육면체를 10x10x10으로 가득 채운다.
	
}

void insertParticle(int mID, int mPx, int mPy, int mPz, int mVx, int mVy, int mVz)
{
	isActive[mID] = true;

	particles[mID] = { mPx, mPy, mPz, mVx, mVy, mVz };

	// 해당하는 Boundary에 넣어야 한다.
	boundary[(mPx + L) / bL][(mPy + L) / bL][(mPz + L) / bL].push_back(mID);

	mCnt++;
}

void removeParticle(int mID)
{
	isActive[mID] = false;
}

int getDistance(int a, int b) {
	Particle& A = particles[a];
	Particle& B = particles[b];

	return (A.x - B.x) * (A.x - B.x) +
		(A.y - B.y) * (A.y - B.y) +
		(A.z - B.z) * (A.z - B.z);
}

int findNearParticle(int mID)
{
	Particle& a = particles[mID];

	int ret = 0;
	// 바운더리에 있는 녀석들만 본다.
	int bX = (a.x + L) / bL;
	int bY = (a.y + L) / bL;
	int bZ = (a.z + L) / bL;

	for (int i = bX - 1; i <= bX + 1; i++) {
		for (int j = bY - 1; j <= bY + 1; j++) {
			for (int k = bZ - 1; k <= bZ + 1; k++) {
				if (i < 0 || i >= 10 ||  j < 0 || j >= 10 || k < 0 || k >= 10) continue;

				for (int id : boundary[i][j][k]) {
					if (!isActive[id]) continue;
					if (mID == id) continue;

					int dist = getDistance(mID, id);
					if (dist <= R * R) {
						ret += id;
					}

				}

			}
		}

	}


	return ret;
}

// 모든 입자들을 다 움직여야 한다.
void go(int mTick)
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				boundary[i][j][k].clear();
			}
		}
	}
	for (int t = 1; t <= mTick; t++) {
		for (int id = 1; id <= mCnt; id++) {
			if (!isActive[id]) continue;

			Particle& curr = particles[id];

			curr.x += curr.vx;
			curr.y += curr.vy;
			curr.z += curr.vz;

			if (curr.x > L) {
				curr.x = (2 * L - curr.x);
				curr.vx *= -1;
			}
			if (curr.y > L) {
				curr.y = (2 * L - curr.y);
				curr.vy *= -1;
			}
			if (curr.z > L) {
				curr.z = (2 * L - curr.z);
				curr.vz *= -1;
			}

			if (curr.x < -L) {
				curr.x = (-2 * L - curr.x);
				curr.vx *= -1;
			}
			if (curr.y < -L) {
				curr.y = (-2 * L - curr.y);
				curr.vy *= -1;
			}
			if (curr.z < -L) {
				curr.z = (-2 * L - curr.z);
				curr.vz *= -1;
			}

		}
	}

	for (int id = 1; id <= mCnt; id++) {
		if (!isActive[id]) continue;
		Particle& curr = particles[id];

		int bx = min(9, (curr.x + L) / bL);
		int by = min(9, (curr.y + L) / bL);
		int bz = min(9, (curr.z + L) / bL);

		boundary[bx][by][bz].push_back(id);
	}

}
