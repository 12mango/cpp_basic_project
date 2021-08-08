#include<bits/stdc++.h>

#define maxn 100010
#define IllegalBaseError 0
#define IllegalInputNumber 1
#define UnknownNumber 2

int checkValue(int val);
int getValue(char ch);
char outputValue(int val);
void raiseError(int err);

char charA[maxn], charB[maxn];
int numA[maxn], numB[maxn], numC[maxn];
int lengthA, lengthB, lengthC, carry;
int inBase = 10, outBase = 10;

int main(int argc, char* argv[]){
	
	freopen(argv[1],"r",stdin);
	
	inBase = atoi(argv[2]);
	//outBase = atoi(argv[3]);
	outBase = inBase;
	
	if((inBase < 2) || (inBase > 36) || (outBase < 2) || (outBase > 36)){
		raiseError(IllegalBaseError);
	}
	
	std::cin.getline(charA, maxn);
	std::cin.getline(charB, maxn);
	lengthA = strlen(charA);
	lengthB = strlen(charB);
	
	//逆序存，字符转整数 
	for(int i = 0; i < lengthA; ++i){
		numA[lengthA - i] = getValue(charA[i]); 
	}
	for(int i = 0; i < lengthB; ++i){
		numB[lengthB - i] = getValue(charB[i]);
	}
	
	lengthC = 1;
	while((lengthC <= lengthA) || (lengthC <= lengthB)){
		numC[lengthC] = numA[lengthC] + numB[lengthC] + carry;
		carry = numC[lengthC] / inBase;
		numC[lengthC] %= inBase;
		lengthC++;
	}
	
	numC[lengthC] = carry;
	
	//处理前导0，输出 
	while((numC[lengthC] == 0) && (lengthC > 1)){
		lengthC--;
	}
	
	for(int i = lengthC; i >= 1; --i){
		std::cout << outputValue(numC[i]);
	}
	
	return 0;
}

int checkValue(int val){
	if(val >= inBase){
		raiseError(IllegalInputNumber);
	}
	return val;
}

//字符转数字 
int getValue(char ch){
	//处理加号
	if(ch == '+'){
		return checkValue(0);
	}
	if((ch >= '0') && (ch <= '9')){
		return checkValue(ch - '0');
	}
	if((ch >= 'a') && (ch <= 'z')){
		return checkValue(ch - 'a' + 10);
	}
	if((ch >= 'A') && (ch <= 'Z')){
		return checkValue(ch - 'A' + 10);
	}
	raiseError(UnknownNumber);
}

//数字转字符 
char outputValue(int val){
	if(val > 9){
		return val + 'A' - 10;
	}
	return val + '0';
}

void raiseError(int err){
	switch(err){
		case IllegalBaseError: puts("IllegalBaseError!"); break;
		case IllegalInputNumber: puts("IllegalInputNumber!"); break;
		case UnknownNumber: puts("UnknownNumber!"); break;
		default: puts("Error!"); break;
	}
	exit(0);
}
