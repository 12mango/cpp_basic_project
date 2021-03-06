#include<bits/stdc++.h>
typedef long long ll;
const int base=1e8;
using namespace std;

char a[100010],b[100010],c[100010];
int inBase=10;

struct Bigint
{
	vector<ll>val;
	int sign;
	
	//去除前导0 
	void clear(){while(!val.back()&&val.size()>1) val.pop_back();}
	
	//构造函数 
	Bigint(){
		sign=0;
		val.clear();
		val.resize(1,0);
	}
	
	Bigint(char *str){
		sign=0;
		if(str[0]=='-'){
			sign=1;
			str[0]='0';
		}
		if(str[0]=='+'){
			str[0]='0';
		}
		int len=strlen(str);
		int ret=0,b=1;
		for(int i=len-1;i>=0;i--){
			ret+=(str[i]-'0')*b;
			if((len-i)%8==0){
				val.push_back(ret);
				b=1;ret=0; continue;
			}
			b*=inBase;
		} 
		val.push_back(ret);
		(*this).clear();
		return;
	}
	
	Bigint(const ll a){
		char str[10010];
		sprintf(str,"%d",a);
		*this=Bigint(str);
	}
	
	//真正的加减法运算 
	Bigint plus(Bigint a,Bigint b){
		Bigint c;
		int len1=a.val.size();
		int len2=b.val.size();
		int len3=max(len1,len2) + 1;
		c.val.resize(len3,0);
		for(int i=0;i<len3;i++){
			if(i<len1) c.val[i]+=a.val[i];
			if(i<len2) c.val[i]+=b.val[i];
		}
		for(int i=0;i<len3-1;i++){
			c.val[i+1]+=c.val[i]/base;
			c.val[i]%=base;
		}
		c.clear();
		return c;
	}
	
	Bigint minus(Bigint a,Bigint b){
		Bigint c;
		int len1=a.val.size();
		int len2=b.val.size();
		int len3=len1;
		c.val.resize(len3,0);
		for(int i=0;i<len3;i++){c.val[i]=a.val[i]-(i<len2?b.val[i]:0);}
		for(int i=0;i<len3-1;i++)
			if(c.val[i]<0){
				c.val[i]+=base;
				c.val[i+1]--;
			}
		c.clear();
		return c;
	}
	
	//重载运算符 
	Bigint operator=(char*str){return Bigint(str);}
	
	Bigint operator=(const ll a){return Bigint(a);}
	
	Bigint operator+(Bigint b){
		Bigint a=*this,c;
		
		//分类讨论 
		if(a.sign==b.sign){
			plus(a,b);
			c=plus(a,b);
			c.sign=a.sign;
		}
		else{
			//异号 
			if(a>b){
				c=minus(a,b);
				c.sign=a.sign;
			}
			else{
				c=minus(b,a);
				c.sign=b.sign;
			}
		}
		return c;
	}
	
	Bigint operator-(Bigint b){
		Bigint a=*this;
		b.sign^=1;
		return a+b;
	}
	
	Bigint operator*(Bigint b){
		Bigint a=*this,c;
		int len1=a.val.size();
		int len2=b.val.size();
		int len3=len1+len2;
		c.val.resize(len3,0);
		for(int i=0;i<len1;i++)
			for(int j=0;j<len2;j++)
				c.val[i+j]+=a.val[i]*b.val[j];
		for(int i= 0;i<len3-1;i++){
			c.val[i+1]+=c.val[i]/base;
			c.val[i]%=base;
		}
		c.clear();
		return c;
	}
	
	//重载比较大小 
	int cmp(Bigint b)
	{
		Bigint a=*this;
		int len1=a.val.size();
		int len2=b.val.size();
		if(len1<len2) return -1;
		else if(len1>len2) return 1;
		else{
			for(int i=len1-1;i>=0;i--){
				if(a.val[i]<b.val[i]) return -1;
				else if(a.val[i]>b.val[i]) return 1;
			}
		}
		return 0;
	}
	
	bool operator>(Bigint b){
		Bigint a=*this;
		return a.cmp(b)>0;
	}
	
	void output(){
		if(sign){
			cout<<"-";
		}
		int len=val.size();
		printf("%d",val[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%08d",val[i]);
		puts(""); 
	}
};
int main()
{
	scanf("%s",a);
	scanf("%s",b);

	Bigint A=Bigint(a),B=Bigint(b),C,D;
	C=A+B;
	C.output();

	return 0;
}
