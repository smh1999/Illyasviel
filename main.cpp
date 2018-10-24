#include <string>
#include <iostream>
using namespace std;
const int k = 9;
const int a = 5;
const int b = 37;
const int p = 127;
const int r =7;

//欧几里得算法求乘法逆元
int getX_1(int x,int mod){
	int Q,X1,X2,X3,Y1,Y2,Y3,T1,T2,T3;
	X1 = 1;
	X2 = 0;
	X3 = mod;
	Y1 = 0;
	Y2 = 1;
	Y3 = (x%mod + mod) %mod;//获得正整数
	while(Y3 != 1){
		Q = X3 / Y3;
		T1 = X1 - Q * Y1;
		T2 = X2 - Q * Y2;
		T3 = X3 - Q * Y3;
		X1 = Y1;
		X2 = Y2;
		X3 = Y3;
		Y1 = T1;
		Y2 = T2;
		Y3 = T3;
	}
	return Y2;
}

struct point{
	int x;
	int y;
};
point A,B;//公钥

typedef pair<point,point> twopoint;

bool operator == (point pa,point pb){
	return pa.x == pb.x && pa.y == pb.y;
}

point operator + (point pa , point pb){
	int k;
	if(pa == pb)
		k = ((3 * pa.x * pa.x + a) * getX_1(2* pa.y ,p)) % p ;//必须使用正整数。这里pa.y的值不能取0.
	else
		k = (pb.y - pa.y) * getX_1(pb.x - pa.x , p) %p;
		point c;
		c.x = (k*k - pa.x -pb.x) %p;
		c.y = (k * (pa.x - c.x) - pa.y)%p ;
		c.x = (c.x + p) %p;
		c.y = (c.y + p) %p;

		return c;
}

point operator * (point &b,int n){
		point q = b;
		n = n -1;
		for(int i = 1 ; i < n;i++){
			q = q + b ;
		}
		return q;
}

twopoint ECodePoint(point m){
	point c1,c2;
	c1 = A * r ;
	point Y = B * r ;
	c2.x = Y.x * m.x % p ;
	c2.y = Y.y * m.y % p ;
	return twopoint(c1,c2);
}

point DCodePoint(twopoint t){
	point Z = t.first * k;
	point m;
	m.x = t.second.x * getX_1(Z.x,p) % p ;
	m.y = t.second.y * getX_1(Z.y,p) % p ;
	return m;
}

string ECode(string input){
	string output = "";
	point M;
	twopoint C;
	for(int i =0; i < input.length();i++){
		M.x = i;
		M.y = input[i];
		C = ECodePoint(M);
		output += (char)C.first.x ;
		output += (char)C.first.y ;
		output += (char)C.second.x ;
		output += (char)C.second.y ;
	}
	return output;
}

string DCode(string input){
	string output = "";
	point M;
	twopoint C;
	//密文肯定是4的倍数，如果不是说明出错
	if(input.length()%4 != 0)
		return "错误输入";
	for(int i = 0;i < input.length();){
		C.first.x = input[i++];
		C.first.y = input[i++];
		C.second.x = input[i++];
		C.second.y = input[i++];
		M = DCodePoint(C);
		output += (char)M.y;
	}
	return output;
}

int main()
{
	A.x = 11;
	A.y = 4;
	B = A*k;
	string s = "";
	//随意输入的密文会使得解密程序出错，所以只支持对之前加密的结果进行解密。
	cout<<"使用在素域上的曲线 y^2 = x^3 + 5*x +37，使用Menezes-Vanstone的算法："<<endl;
	cout<<"在素域p=127上，私钥为k=9,公钥A(11,4),B(120,41),对明文字符串直接转换为int进行加密"<<endl;
	cout<<"请输入要加密的内容："<<endl;
	cin>>s;
	cout<<"密文如下："<<"\r\n";
	s = ECode(s);
	cout<<s<<endl;
	cout<<"对之前密文解密，得到明文如下："<<"\r\n";
	s = DCode(s);
	cout<<s<<"\r\n"<<"完成"<<endl;
	cin>>s;
	return 0;
}
