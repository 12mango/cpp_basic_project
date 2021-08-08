#include<bits/stdc++.h>
#define maxn 100010
#define eps 1e-1
using namespace std;
struct problem{
	double x,y;
	int symbol;
	double ans;
}p[maxn];

int limit=100;
bool multi=false;
int problem_num=10;
double get_num(){
	return rand()%limit;
}
int get_symbol(){
	if(multi){
		return rand()%4;
	}
	return rand()%2;
}
void generate(){
	for(int i=1;i<=problem_num;++i){
		while(1){
			p[i].x=get_num();
			p[i].y=get_num();
			p[i].symbol=get_symbol();
			switch(p[i].symbol){
				case 0:p[i].ans=p[i].x+p[i].y;break;
				case 1:p[i].ans=p[i].x-p[i].y;break;
				case 2:p[i].ans=p[i].x*p[i].y;break;
				case 3:
					if(fabs(p[i].y)<eps){
						continue;  // ³ý0 
					}
					p[i].ans=p[i].x/p[i].y;break;
			}
			if(fabs(p[i].ans)<=limit){
				break;
			}
		}
	}
}
void answer(){
	double correct=0;
	double full_score=100;
	double user_answer;
	long min_time=1<<29;
	long tot_time=0;
	for(int i=1;i<=problem_num;++i){
		cout<<"Problem "<<i<<": "<<endl;
		cout<<p[i].x<<" ";
		switch(p[i].symbol){
			case 0:cout<<"+";break;
			case 1:cout<<"-";break;
			case 2:cout<<"*";break;
			case 3:cout<<"/";break;
		}
		cout<<" "<<p[i].y<<" = ";
		
		std::chrono::time_point<std::chrono::system_clock> server_create_time_ = std::chrono::system_clock::now();
		cin>>user_answer;
		auto current_time = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> duration_mili = current_time - server_create_time_;
		long ms = (long)duration_mili.count();
		tot_time += ms;
		if(min_time>ms){
			min_time=ms;
		}
		//std::cout << "PrintDuration : duration_mili duration = " << (long)duration_mili.count() << " ms";
		
		if(fabs(user_answer-p[i].ans)<eps){
			puts("Correct!");
			correct++;
		}
		else{
			puts("Wrong");
			cout<<"Correct Answer :"<<p[i].ans<<endl;
		}
		cout<<endl;
	}
	
	cout<<"Score : "<<correct/problem_num*full_score<<endl;
	cout<<"Average Time : "<<tot_time/problem_num<<" ms"<<endl;
	cout<<"Minimum Time : "<<min_time<<" ms"<<endl;
}
int main(int argc,char *argv[])
{
	if(argc>1){
		limit=atoi(argv[1]);
	}
	if(argc>2){
		multi=atoi(argv[2]);
	}
	if(argc>3){
		problem_num=atoi(argv[3]);
	}
	srand(time(0));
	generate();
	answer();
	return 0;
}
