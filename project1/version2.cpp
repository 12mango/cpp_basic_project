#include<bits/stdc++.h>

#define maxn 100010
#define IllegalBaseError 0
#define IllegalInputNumber 1
#define UnknownNumber 2

int checkValue(int val);
int getValue(char ch);
char outputValue(int val);
void raiseError(int err);

std::string charA, charB;
std::vector<int> numA, numB, numC, numD;
int lengthA, lengthB, lengthC, carry;
int inBase = 10, outBase = 10;

int main(int argc, char* argv[]){
	
	inBase = atoi(argv[1]);
	outBase = atoi(argv[2]);
	
	if((inBase < 2) || (inBase > 36) || (outBase < 2) || (outBase > 36)){
		raiseError(IllegalBaseError);
	}
	
	std::cin >> charA >> charB;
	
	//�ַ�ת���� 
	for(auto ch : charA){
		numA.push_back(getValue(ch));
	}
	for(auto ch : charB){
		numB.push_back(getValue(ch));
	}
	
	//��λ��ǰ
	reverse(numA.begin(), numA.end());
	reverse(numB.begin(), numB.end());
	
	//���϶̵����ֲ�0 �������ӷ� 
	while(numA.size() < numB.size()){
		numA.push_back(0);
	}
	while(numB.size() < numA.size()){
		numB.push_back(0);
	}
	
	for(int i = 0; i < numA.size(); ++i){
		numC.push_back(numA[i] + numB[i] + carry);
		carry = numC[i] / inBase;
		numC[i] %= inBase;
	}
	
	//����ǰ��0����� 
	numC.push_back(carry);
	while((numC.size() > 1) && (numC.back() == 0)){
		numC.pop_back();
	}
	
	//ת������ ģ��̳��� 
	while(numC.size()){
		carry = 0;
		for(int i = numC.size() - 1; i >= 0 ; --i){
			numC[i] += carry * inBase;
			carry = numC[i] % outBase;
			numC[i] /= outBase;
		} 
		numD.push_back(carry); 
		
		//���һ��0ҲҪ���� 
		while((numC.size() > 0) && (numC.back() == 0)){
			numC.pop_back();
		}
	}
	
	//��λ��ǰ
	reverse(numD.begin(), numD.end());
	
	for(auto val : numD){
		std::cout << outputValue(val);
	}
	
	return 0;
}

int checkValue(int val){
	if(val >= inBase){
		raiseError(IllegalInputNumber);
	}
	return val;
}

//�ַ�ת���� 
int getValue(char ch){
	//����Ӻ�
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

//����ת�ַ� 
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

//reference  https://zhuanlan.zhihu.com/p/364936191
