#include<bits/stdc++.h>

#define maxn 100010
#define IllegalBaseError 0
#define IllegalInputNumber 1
#define UnknownNumber 2

bool A_gt_B();
void A_plus_B();
void A_minus_B();
int checkValue(int val);
int getValue(char ch);
char outputValue(int val);
void raiseError(int err);

std::string charA, charB;
std::vector<int> numA, numB, numC, numD, tmp;
int lengthA, lengthB, lengthC, carry;
int signA, signB, signC, signD;
int inBase = 10, outBase = 10;

int main(int argc, char* argv[]){
	
	freopen(argv[1],"r",stdin);
	
	inBase = atoi(argv[2]);
	outBase = atoi(argv[3]);
	
	if((inBase < 2) || (inBase > 36) || (outBase < 2) || (outBase > 36)){
		raiseError(IllegalBaseError);
	}
	
	std::cin >> charA >> charB;
	
	if(charA[0] == '-'){
		signA = 1;
	}
	if(charB[0] == '-'){
		signB = 1;
	}
	
	//字符转整数 
	for(auto ch : charA){
		numA.push_back(getValue(ch));
	}
	for(auto ch : charB){
		numB.push_back(getValue(ch));
	}
	
	//低位在前
	reverse(numA.begin(), numA.end());
	reverse(numB.begin(), numB.end());
	
	//给较短的数字补0 方便运算 
	while(numA.size() < numB.size()){
		numA.push_back(0);
	}
	while(numB.size() < numA.size()){
		numB.push_back(0);
	}
	
	//分类讨论 
	
	//A和B只有一个为负 
	if(signA + signB < 2){
			
		//B为负 交换保证负数在前 
		if(signB){
			numA.swap(numB);
			std::swap(signA,signB);	
		}

		//一负一正 做减法
		if(signA){
			
			//负数大 结果为负 
			if(A_gt_B()){
				signC = 1;
				A_minus_B();
			}
			else{
				numA.swap(numB);
				A_minus_B();
			}
		}
		else{
			A_plus_B();
		}
	}
	//A B均为负 
	else{
		signC = 1;
		A_plus_B();
	}
	
	//处理前导0
	numC.push_back(carry);
	while((numC.size() > 1) && (numC.back() == 0)){
		numC.pop_back();
	}
	
	//转换进制 模拟短除法 
	while(numC.size()){
		carry = 0;
		for(int i = numC.size() - 1; i >= 0 ; --i){
			numC[i] += carry * inBase;
			carry = numC[i] % outBase;
			numC[i] /= outBase;
		} 
		numD.push_back(carry); 
		
		//最后一个0也要弹出 
		while((numC.size() > 0) && (numC.back() == 0)){
			numC.pop_back();
		}
	}
	signD = signC;
		
	//高位在前
	reverse(numD.begin(), numD.end());
	
	if(signD){
		std::cout << "-";
	}
	
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

bool A_gt_B(){
	 for(int i = numA.size() - 1; i >= 0; ++i){
	 	if(numA[i] > numB[i]){
	 		return true;
	 	}
	 	else if(numA[i] < numB[i]){
	 		return false;
	 	}
	 }
	 return false;
}

void A_plus_B(){
	for(int i = 0; i < numA.size(); ++i){
		numC.push_back(numA[i] + numB[i] + carry);
		carry = numC[i] / inBase;
		numC[i] %= inBase;
	}
}

void A_minus_B(){
	for(int i = 0; i < numA.size(); ++i){
		if(numA[i] < numB[i]){
			numA[i] += inBase;
			numA[i+1]--;
		}
		numC.push_back(numA[i] - numB[i]);
	}
}

//字符转数字 
int getValue(char ch){
	//处理加号
	if((ch == '+') || (ch == '-')){
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

//reference  https://zhuanlan.zhihu.com/p/364936191
