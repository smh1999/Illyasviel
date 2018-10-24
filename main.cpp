#include <string>
#include <iostream>
using namespace std;
const int k = 9;
const int a = 5;
const int b = 37;
const int p = 127;
const int r =7;

//ŷ������㷨��˷���Ԫ
int getX_1(int x,int mod){
	int Q,X1,X2,X3,Y1,Y2,Y3,T1,T2,T3;
	X1 = 1;
	X2 = 0;
	X3 = mod;
	Y1 = 0;
	Y2 = 1;
	Y3 = (x%mod + mod) %mod;//���������
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
point A,B;//��Կ

typedef pair<point,point> twopoint;

bool operator == (point pa,point pb){
	return pa.x == pb.x && pa.y == pb.y;
}

point operator + (point pa , point pb){
	int k;
	if(pa == pb)
		k = ((3 * pa.x * pa.x + a) * getX_1(2* pa.y ,p)) % p ;//����ʹ��������������pa.y��ֵ����ȡ0.
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
	//���Ŀ϶���4�ı������������˵������
	if(input.length()%4 != 0)
		return "��������";
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
	//������������Ļ�ʹ�ý��ܳ����������ֻ֧�ֶ�֮ǰ���ܵĽ�����н��ܡ�
	cout<<"ʹ���������ϵ����� y^2 = x^3 + 5*x +37��ʹ��Menezes-Vanstone���㷨��"<<endl;
	cout<<"������p=127�ϣ�˽ԿΪk=9,��ԿA(11,4),B(120,41),�������ַ���ֱ��ת��Ϊint���м���"<<endl;
	cout<<"������Ҫ���ܵ����ݣ�"<<endl;
	cin>>s;
	cout<<"�������£�"<<"\r\n";
	s = ECode(s);
	cout<<s<<endl;
	cout<<"��֮ǰ���Ľ��ܣ��õ��������£�"<<"\r\n";
	s = DCode(s);
	cout<<s<<"\r\n"<<"���"<<endl;
	cin>>s;
	return 0;
}
