#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<chrono>
using namespace std;

#define maxn 300010

int n=729,m=324; // 这两个参数的解释在下面读入数据那里 
int cnt,ans;
int column_tot_point[maxn],rec[maxn];

struct point{
	int R,C;
	point *l,*r,*u,*d;
}*p[maxn],*head[maxn];

void link(int R,int C){
	/*
		R行C列插入点 
	*/
	column_tot_point[C]++;
	cnt++;
 	point *x=p[cnt]=new point;
	
	/*
		头插法 在第0行第C列的链表插入结点 
	*/
	x->R=R;
	x->C=C;
	x->u=p[C];
	x->d=p[C]->d;
	p[C]->d->u=x;
	p[C]->d=x;
	
	/*
		在第R行插入点 
	*/
	if(head[R]==NULL){
		head[R]=x->r=x->l=x;
	}
	else{
		x->r=head[R];
		x->l=head[R]->l;
		head[R]->l->r=x;
		head[R]->l=x;
	}
}
void init(){
	
	int x;
	/*
		初始化第0行 
	*/
	for(int i=0;i<=m;++i){
		p[i]=new point; 
	}
	for(int i=0;i<=m;++i){
		if(i){
			p[i]->l=p[i-1];
		}
		else{
			p[i]->l=p[m];
		}
		if(i==m){
			p[i]->r=p[0];
		}
		else{
			p[i]->r=p[i+1];
		}
		p[i]->u=p[i]->d=p[i];
		p[i]->C=i;
	}
	cnt=m;
	
	/*
		读入数据 
	*/
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			cin>>x;
			for(int k=1;k<=9;++k){
				/*
					如果x=0 k=1~9都有可能填入 
					否则只填入x=k
				*/
				if(x&&x!=k){
					continue;
				}
				/*
					dlx矩阵 729*324
					729: 第i行第j列填数字k 共9*9*9种情况 
					324: 在第i行第j列填 有4种限制情况 9*9*4 
				
					对于第m列：
    				每个格子只能填一次 -> 若m在[1,81]表示在(m/9，m%9)填数 
    				每行只能填一次 -> 若m在[81*1,81*2]在第1+（m-81）/9行填1+（m-81）%9 
    				每列只能填一次 -> 若m在[81*2,81*3]在第1+（m-81*2）/9列填1+（m-81*2）%9 
    				每个宫格只能填一次 -> 若m在[81*3,81*4]在第1+（m-81*3）/9宫填1+（m-81*3）%9
				*/
				int o=i*9*9+j*9+k;
            	link(o,i*9+j+1);
            	link(o,i*9+81+k);
            	link(o,j*9+81*2+k);
            	link(o,81*3+(i/3*3+j/3)*9+k);
			}
		}
	}
}
void remove(int C){
	/*
		删除涉及C列的集合 
	*/ 
	
	point *x=p[C];
	
	x->l->r=x->r;
	x->r->l=x->l;
	
	point *i=x->d;
	while(i!=x){	
		point *j=i->r;
		while(j!=i){
			j->d->u=j->u;
			j->u->d=j->d;
			column_tot_point[j->C]--;
			j=j->r;
		}
		i=i->d;
	};
}
void resume(int C){
	/*
		恢复涉及C列的集合 
	*/
	point *x=p[C];
	point *i=x->u;
	while(i!=x){
		point *j=i->l;
		while(j!=i){
			j->d->u=j;
			j->u->d=j;
			column_tot_point[j->C]++;
			j=j->l;
		}
		i=i->u;
	}
	x->l->r=x;
	x->r->l=x;
}
bool dfs(int deep){

	/*
		DFS搜索 
	*/
	
	/*
		找到答案 
	*/
	if(p[0]->r==p[0]){
		/*
		for(int i=0;i<deep;++i){
			cout<<rec[i]<<" ";
		}
		*/
		ans++;
	}
	
	/*
		找点最少的列 优先操作 
	*/
	point *i=p[0]->r;
	
	int C=i->C;
	while(i!=p[0]){
		if(column_tot_point[i->C]<column_tot_point[C]){
			C=i->C;
		}
		i=i->r;
	}
	/*
		递归/回溯 
	*/ 
	remove(C);
	i=p[C]->d;
	while(i!=p[C]){
		
		rec[deep]=i->R;
		point *j=i->r;
		while(j!=i){
			remove(j->C);
			j=j->r;
		}
		
		dfs(deep+1);
		
		j=i->l;
		while(j!=i){
			resume(j->C);
			j=j->l;
		}
		i=i->d;
	}
	resume(C);
	return false;
}
int main()
{
	freopen("../data/hard++.txt", "r", stdin);

	std::chrono::time_point<std::chrono::system_clock> server_create_time_ = std::chrono::system_clock::now();
	init();
	dfs(0);
	std::cout<<"solution_count = "<<ans<<std::endl;
	auto current_time = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> duration_mili = current_time - server_create_time_;
	std::cout<<"PrintDuration : duration_mili duration = "<< (long)duration_mili.count()<<" ms";
	return 0;
}
