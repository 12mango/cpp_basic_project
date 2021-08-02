#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<chrono>
using namespace std;

/*
	�洢�ո��ӵ���Ϣ
	x,y��λ��
	tot����ʼ�ж��ٸ����ֿ�����
	list���洢tot�������������
*/
struct Cell {
	int x, y, tot, list[10];
}a[90];


int ans, cnt, row[10], column[10], block[10], vis[90], mp[10][10];

/*
	ÿ�����������ĸ�����
*/
int belong[10][10] = { {},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9} };

/*
	�ж϶�Ӧλ���Ƿ�������
*/
int F(int x, int k) { return x & (1 << k); }

/*
	�ж�����λ���Ƿ��Ѿ���������k
*/
bool exist(int i, int j, int k) { return F(row[i], k) || F(column[j], k) || F(block[belong[i][j]], k); }


/*
	������(i,j)������k
*/
bool Fill(int i, int j, int k) {
	/*
		������Ͳ�����
	*/
	if (exist(i, j, k)) {
		return false;
	}
	
	/*
		λ���� �����к͹���������
	*/
	row[i] |= 1 << k, column[j] |= 1 << k, block[belong[i][j]] |= 1 << k;
	mp[i][j] = k;
	return true;
}

/*
	�������ٵĸ�����ǰ��
*/
bool cmp(Cell X, Cell Y) {
	if (X.tot != Y.tot) {
		return X.tot < Y.tot;
	}
	if (X.x != Y.x) {
		return X.x > Y.x;
	}
	return X.y > Y.y;
}

/*
	DFS���Ҵ�
	id���ո��ӵı��
*/
void dfs(int id, int sum) {
	if (sum > cnt) {
		/*
		for(int i=1;i<=9;++i){
			for(int j=1;j<=9;++j)
				cout<<mp[i][j]<<" ";
			puts("");
		}
		*/
		ans++;
	}

	
	int x = a[id].x, y = a[id].y;

	/*
		�ӿ��������������ѡȡ
	*/
	for (int i = 1;i <= a[id].tot;++i) {
		int k = a[id].list[i];
		/*
			�����ǰ��������k��Ѱ����һ�����������ٵĸ��Ӽ�������
		*/
		if (Fill(x, y, k)) {
			/*
				flag:�ҵ�����һ������
			*/
			int flag = 1, min_plan = 10, next_id = 0;

			/*
				������ʼ�����пո���
				��TODO:���������˫��������ά�� ����õĸ���ȥ�� �᲻����죩
			*/
			for (int j = 1;j <= cnt;++j) {
				/*
					�Ѿ���õľ�����
				*/
				if (vis[j]) {
					continue;
				}

				/*
					plan ��ʼ�ж��ٿ����������
				*/
				int plan = a[j].tot, X = a[j].x, Y = a[j].y;
				for (int l = 1;l <= a[j].tot;++l) {
					/*
						�����������Ѿ��������� plan--
					*/
					int num = a[j].list[l];
					if (exist(X, Y, num)) {
						plan--;
					}
				}

				/*
					һ������� ˵��֮ǰ��������� ���Ի�����
				*/
				if (!plan) {
					flag = 0;
					break;
				}

				/*
					�����Ը��� ������һ��Ҫ��ĸ��ӵı��
				*/
				if (plan < min_plan) {
					min_plan = plan;
					next_id = j;
				}

				/*
					ֻ����һ������ ���ü������� ��һ�����Ӿ�������
				*/
				if (plan == 1) {
					break;
				}
			}

			/*
				�ҵ���һ��Ҫ��ĸ��� ��������
			*/
			if (flag) {
				vis[next_id] = 1;
				dfs(next_id, sum + 1);
			}

			/*
				����
			*/
			vis[next_id] = 0;
			mp[x][y] = 0;
			row[x] ^= 1 << k;
			column[y] ^= 1 << k;
			block[belong[x][y]] ^= 1 << k;
		}
	}
}
int main() {
	/* read file */
	freopen("../data/hard++.txt", "r", stdin);

	/* start */
	std::chrono::time_point<std::chrono::system_clock> server_create_time_ = std::chrono::system_clock::now();

	/* solve problem */
	int x;
	for (int i = 1;i <= 9;++i)
		for (int j = 1;j <= 9;++j) {

			cin >> x;
			if (x) {
				Fill(i, j, x);
			}
			mp[i][j] = x;
		}

	/*
		�����пո����Ԥ����
	*/
	for (int i = 1;i <= 9;++i)
		for (int j = 1;j <= 9;++j) {
			if (mp[i][j]) {
				continue;
			}
			a[++cnt].x = i;
			a[cnt].y = j;
			
			/*
				���ÿ�������ܷ����ȥ
			*/
			for (int k = 1;k <= 9;++k) {
				if (!exist(i, j, k)) {
					a[cnt].list[++a[cnt].tot] = k;
				}
			}

		}

	/*
		�������ٵĸ�����ǰ��
	*/
	sort(a + 1, a + cnt + 1, cmp);

	vis[1] = 1;
	dfs(1, 1);

	/* end */
	std::cout << "solution_count = " << ans << std::endl;
	auto current_time = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> duration_mili = current_time - server_create_time_;
	std::cout << "PrintDuration : duration_mili duration = " << (long)duration_mili.count() << " ms";
}
