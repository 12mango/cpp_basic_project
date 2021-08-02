#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<chrono>
using namespace std;

/*
	存储空格子的信息
	x,y：位置
	tot：初始有多少个数字可以填
	list：存储tot个可以填的数字
*/
struct Cell {
	int x, y, tot, list[10];
}a[90];


int ans, cnt, row[10], column[10], block[10], vis[90], mp[10][10];

/*
	每个数字属于哪个宫格
*/
int belong[10][10] = { {},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,1,1,1,2,2,2,3,3,3},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,4,4,4,5,5,5,6,6,6},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9},{0,7,7,7,8,8,8,9,9,9} };

/*
	判断对应位置是否有数字
*/
int F(int x, int k) { return x & (1 << k); }

/*
	判断三个位置是否已经填了数字k
*/
bool exist(int i, int j, int k) { return F(row[i], k) || F(column[j], k) || F(block[belong[i][j]], k); }


/*
	尝试在(i,j)填数字k
*/
bool Fill(int i, int j, int k) {
	/*
		不能填就不填了
	*/
	if (exist(i, j, k)) {
		return false;
	}
	
	/*
		位运算 在行列和宫格填数字
	*/
	row[i] |= 1 << k, column[j] |= 1 << k, block[belong[i][j]] |= 1 << k;
	mp[i][j] = k;
	return true;
}

/*
	可能性少的格子排前面
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
	DFS查找答案
	id：空格子的编号
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
		从可能填入的数字中选取
	*/
	for (int i = 1;i <= a[id].tot;++i) {
		int k = a[id].list[i];
		/*
			如果当前可以填入k，寻找下一个可能性最少的格子继续搜索
		*/
		if (Fill(x, y, k)) {
			/*
				flag:找到了下一个格子
			*/
			int flag = 1, min_plan = 10, next_id = 0;

			/*
				遍历初始的所有空格子
				（TODO:这里如果用双向链表来维护 把填好的格子去掉 会不会更快）
			*/
			for (int j = 1;j <= cnt;++j) {
				/*
					已经填好的就跳过
				*/
				if (vis[j]) {
					continue;
				}

				/*
					plan 初始有多少可能填的数字
				*/
				int plan = a[j].tot, X = a[j].x, Y = a[j].y;
				for (int l = 1;l <= a[j].tot;++l) {
					/*
						如果这个数字已经不能填了 plan--
					*/
					int num = a[j].list[l];
					if (exist(X, Y, num)) {
						plan--;
					}
				}

				/*
					一个都填不了 说明之前填的有问题 可以回溯了
				*/
				if (!plan) {
					flag = 0;
					break;
				}

				/*
					可能性更少 更新下一个要填的格子的编号
				*/
				if (plan < min_plan) {
					min_plan = plan;
					next_id = j;
				}

				/*
					只能填一个数字 不用继续找了 下一个格子就这样填
				*/
				if (plan == 1) {
					break;
				}
			}

			/*
				找到下一个要填的格子 继续搜索
			*/
			if (flag) {
				vis[next_id] = 1;
				dfs(next_id, sum + 1);
			}

			/*
				回溯
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
		对所有空格进行预处理
	*/
	for (int i = 1;i <= 9;++i)
		for (int j = 1;j <= 9;++j) {
			if (mp[i][j]) {
				continue;
			}
			a[++cnt].x = i;
			a[cnt].y = j;
			
			/*
				检查每个数字能否填进去
			*/
			for (int k = 1;k <= 9;++k) {
				if (!exist(i, j, k)) {
					a[cnt].list[++a[cnt].tot] = k;
				}
			}

		}

	/*
		可能性少的格子排前面
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
