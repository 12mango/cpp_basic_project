#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<chrono>
using namespace std;

#define maxn 300010

int n=729,m=324; // �����������Ľ�������������������� 
int cnt,ans;
int column_tot_point[maxn],rec[maxn];

struct point{
	int R,C;
	point *l,*r,*u,*d;
}*p[maxn],*head[maxn];

void link(int R,int C){
	/*
		R��C�в���� 
	*/
	column_tot_point[C]++;
	cnt++;
 	point *x=p[cnt]=new point;
	
	/*
		ͷ�巨 �ڵ�0�е�C�е���������� 
	*/
	x->R=R;
	x->C=C;
	x->u=p[C];
	x->d=p[C]->d;
	p[C]->d->u=x;
	p[C]->d=x;
	
	/*
		�ڵ�R�в���� 
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
		��ʼ����0�� 
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
		�������� 
	*/
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			cin>>x;
			for(int k=1;k<=9;++k){
				/*
					���x=0 k=1~9���п������� 
					����ֻ����x=k
				*/
				if(x&&x!=k){
					continue;
				}
				/*
					dlx���� 729*324
					729: ��i�е�j��������k ��9*9*9����� 
					324: �ڵ�i�е�j���� ��4��������� 9*9*4 
				
					���ڵ�m�У�
    				ÿ������ֻ����һ�� -> ��m��[1,81]��ʾ��(m/9��m%9)���� 
    				ÿ��ֻ����һ�� -> ��m��[81*1,81*2]�ڵ�1+��m-81��/9����1+��m-81��%9 
    				ÿ��ֻ����һ�� -> ��m��[81*2,81*3]�ڵ�1+��m-81*2��/9����1+��m-81*2��%9 
    				ÿ������ֻ����һ�� -> ��m��[81*3,81*4]�ڵ�1+��m-81*3��/9����1+��m-81*3��%9
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
		ɾ���漰C�еļ��� 
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
		�ָ��漰C�еļ��� 
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
		DFS���� 
	*/
	
	/*
		�ҵ��� 
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
		�ҵ����ٵ��� ���Ȳ��� 
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
		�ݹ�/���� 
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
